#ifndef RAWINPUTDEVICE_H
#define RAWINPUTDEVICE_H

#include "HIDCFG_Common.h"

#define ENABLE_MOUSE_INPUT 0
#define ENABLE_KEYBOARD_INPUT 1
#define ENABLE_GAMEPAD_INPUT 0
static_assert(ENABLE_MOUSE_INPUT || ENABLE_KEYBOARD_INPUT || ENABLE_GAMEPAD_INPUT );

enum struct RIDType
{
	Mouse,
	Keyboard,
	HID,
	MAX
};

struct RawInputDevice
{
	RIDType DevType = RIDType::MAX;
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

	void AddRID(RAWINPUTDEVICELIST& InRID, RIDType InType);
	void IncList();
	void Delete();
};

RIDList EnumerateHIDs(HWND InWnd);

#endif // RAWINPUTDEVICE_H