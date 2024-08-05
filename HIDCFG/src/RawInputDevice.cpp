#include "RawInputDevice.h"

#include <hidusage.h>
void RIDList::AddRID(RAWINPUTDEVICELIST& InRID, RIDType InType)
{
	if (NumEntries + 1 >= ListCapacity)
	{
		IncList();
		Assert(NumEntries + 1 < ListCapacity);
	}

	RawInputDevice NewRID {};
	NewRID.DevType = InType;
	NewRID.DevHndl = InRID.hDevice;

	NewRID.DevInfo.cbSize = sizeof(RID_DEVICE_INFO);
	UINT WriteSize = 0;
	GetRawInputDeviceInfoA(InRID.hDevice, RIDI_DEVICEINFO, nullptr, &WriteSize);
	GetRawInputDeviceInfoA(InRID.hDevice, RIDI_DEVICEINFO, &NewRID.DevInfo, &WriteSize);

	Assert(0 == GetRawInputDeviceInfoA(InRID.hDevice, RIDI_DEVICENAME, nullptr, &WriteSize));
	if (WriteSize > 0)
	{
		NewRID.DevName = new char[WriteSize + 1];
		Assert(-1 != GetRawInputDeviceInfoA(InRID.hDevice, RIDI_DEVICENAME, NewRID.DevName, &WriteSize));
		NewRID.DevName[WriteSize + 1] = L'\0';
	}

	DevList[NumEntries++] = NewRID;
}

void RIDList::IncList()
{
	int NewCapacity = ListCapacity * IncFactor;
	RawInputDevice* NewList = new RawInputDevice[NewCapacity];
	for (int DevIdx = 0; DevIdx < NumEntries; DevIdx++)
	{
		NewList[DevIdx] = DevList[DevIdx];
	}

	delete[] DevList;
	ListCapacity = NewCapacity;
	DevList = NewList;
}

void RIDList::Delete()
{
	for (int DevIdx = 0; DevIdx < NumEntries; DevIdx++)
	{
		delete[] DevList[DevIdx].DevName;
		DevList[DevIdx].DevName = nullptr;
	}
	delete[] DevList;
	DevList = nullptr;
}

RIDList EnumerateHIDs(HWND InWnd)
{
	// Covers Keyboard, Mouse, Gamepad
	constexpr USHORT GenericUsagePage = 0x0001;

	//CKA_TODO: the call to Register...() fails if KbdFlags includes -> RIDEV_NOLEGACY|RIDEV_APPKEYS
	const DWORD KbdFlags = RIDEV_EXINPUTSINK|RIDEV_DEVNOTIFY;

	const RAWINPUTDEVICE RIDRegistrationList[] =
	{
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-rawinputdevice
		// { USHORT usUsagePage, USHORT usUsage, DWORD dwFlags, HWND hwndTarget }
	#if ENABLE_MOUSE_INPUT
		{ GenericUsagePage, HID_USAGE_GENERIC_POINTER, 0, InWnd },
		{ GenericUsagePage, HID_USAGE_GENERIC_MOUSE, 0, InWnd },
	#endif // ENABLE_MOUSE_INPUT
	#if ENABLE_GAMEPAD_INPUT
		{ GenericUsagePage, HID_USAGE_GENERIC_JOYSTICK, 0, InWnd },
		{ GenericUsagePage, HID_USAGE_GENERIC_GAMEPAD, 0, InWnd },
	#endif // ENABLE_GAMEPAD_INPUT
	#if ENABLE_KEYBOARD_INPUT
		{ GenericUsagePage, HID_USAGE_GENERIC_KEYBOARD, KbdFlags, InWnd },
		{ GenericUsagePage, HID_USAGE_GENERIC_KEYPAD, KbdFlags, InWnd },
	#endif // ENABLE_KEYBOARD_INPUT
		//{ GenericUsagePage, HID_USAGE_GENERIC_MULTI_AXIS_CONTROLLER, 0, InWnd },
	};

	UINT NumRIDs = ARRAYSIZE(RIDRegistrationList);
	Assert(RegisterRawInputDevices(RIDRegistrationList, NumRIDs, sizeof(RAWINPUTDEVICE)));

	UINT NumDevs = 0;
	RAWINPUTDEVICELIST* SysRIDevList = nullptr;
	GetRawInputDeviceList(nullptr, &NumDevs, sizeof(RAWINPUTDEVICE));
	if (NumDevs > 0)
	{
		SysRIDevList = new RAWINPUTDEVICELIST[NumDevs];
		GetRawInputDeviceList(SysRIDevList, &NumDevs, sizeof(RAWINPUTDEVICE));
	}
	RIDList DeviceList{};
	for (int DevIdx = 0; DevIdx < NumDevs; DevIdx++)
	{
		RAWINPUTDEVICELIST& CurrRID = SysRIDevList[DevIdx];
		switch (CurrRID.dwType)
		{
#if ENABLE_MOUSE_INPUT
			case RIM_TYPEMOUSE: { DeviceList.AddRID(SysRIDevList[DevIdx], RIDType::Mouse); } break;
#endif // ENABLE_MOUSE_INPUT 
#if ENABLE_KEYBOARD_INPUT
			case RIM_TYPEKEYBOARD: { DeviceList.AddRID(SysRIDevList[DevIdx], RIDType::Keyboard); } break;
#endif // ENABLE_KEYBOARD_INPUT
#if ENABLE_GAMEPAD_INPUT
			case RIM_TYPEHID: { DeviceList.AddRID(SysRIDevList[DevIdx], RIDType::HID); } break;
#endif // ENABLE_GAMEPAD_INPUT
		}
	}

	return DeviceList;
}
