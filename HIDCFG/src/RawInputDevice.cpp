#include "RawInputDevice.h"

#include <hidusage.h>

#define ENABLE_MOUSE_INPUT 0
#define ENABLE_GAMEPAD_INPUT 0
#define ENABLE_KEYBOARD_INPUT 1
static_assert(ENABLE_MOUSE_INPUT || ENABLE_GAMEPAD_INPUT || ENABLE_KEYBOARD_INPUT);

enum struct RIDType
{
	Dev_Keyboard,
	Dev_Mouse,
	Dev_HID
};

struct RawInputDevice
{
	HANDLE DevHndl = nullptr;
	char* DevName = nullptr;
	RID_DEVICE_INFO DevInfo{};
};

struct RIDList
{
	static constexpr int InitCapacity = 16;
	static constexpr int IncFactor = 2;
	int ListCapacity = InitCapacity;
	int NumEntries = 0;
	RawInputDevice* DevList = new RawInputDevice[InitCapacity];

	void AddRID(RAWINPUTDEVICELIST& InRID);
	~RIDList();
};

void RIDList::AddRID(RAWINPUTDEVICELIST& InRID)
{
}

RIDList::~RIDList()
{
}

int EnumerateHIDs(HWND InWnd)
{
	// Covers Keyboard, Mouse, Gamepad
	constexpr USHORT GenericUsagePage = 0x0001;

	//CKA_TODO: the call to Register...() fails if KbdFlags includes -> RIDEV_NOLEGACY|RIDEV_APPKEYS
	const DWORD KbdFlags = RIDEV_EXINPUTSINK|RIDEV_DEVNOTIFY;

	const RAWINPUTDEVICE RIDList[] =
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

	UINT NumRIDs = ARRAYSIZE(RIDList);

	Assert(RegisterRawInputDevices(RIDList, NumRIDs, sizeof(RAWINPUTDEVICE)));

	UINT NumDevs = 0;
	RAWINPUTDEVICELIST* RDeviceList = nullptr;
	UINT Result = GetRawInputDeviceList(nullptr, &NumDevs, sizeof(RAWINPUTDEVICE));

	UINT NumHIDs = 0;
	UINT NumKbds = 0;
	UINT NumMice = 0;
	if (NumDevs > 0)
	{
		RDeviceList = new RAWINPUTDEVICELIST[NumDevs];
		GetRawInputDeviceList(RDeviceList, &NumDevs, sizeof(RAWINPUTDEVICE));
	}
	for (int DevIdx = 0; DevIdx < NumDevs; DevIdx++)
	{
		switch (RDeviceList[DevIdx].dwType)
		{
			case RIM_TYPEHID: { NumHIDs++; } break;
			case RIM_TYPEKEYBOARD: { NumKbds++; } break;
			case RIM_TYPEMOUSE: { NumMice++; } break;
		}
	}
	for (int DevIdx = 0, KbdIdx = 0; DevIdx < NumDevs; DevIdx++)
	{
		RAWINPUTDEVICELIST& CurrDev = RDeviceList[DevIdx];
		if (CurrDev.dwType == RIM_TYPEKEYBOARD)
		{
			// ...
			//GetRawInputDeviceInfo(CurrDev.hDevice, RIDI_DEVICENAME, )
			//GetRawInputDeviceInfo(CurrDev.hDevice, RIDI_DEVICEINFO, )
		}
	}

	return NumRIDs;
}
