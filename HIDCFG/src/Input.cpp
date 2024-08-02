#include "Input.h"

#include <hidusage.h>

int EnumerateHIDs(HWND InWnd)
{
	// Covers Keyboard, Mouse, Gamepad
	constexpr USHORT GenericUsagePage = 0x0001;

	//USHORT MouseUsageRange[] = { 0x0001, 0x0002 };
	//USHORT GamepadUsageRange[] = { 0x0004, 0x0005 };
	//USHORT KeyboardUsageRange[] = { 0x0006, 0x0007 };

	// CKA_NOTE: RIDEV_NOLEGACY disables legacy WM_... messages

	const RAWINPUTDEVICE ridlist[] =
	{
		// { USHORT usUsagePage, USHORT usUsage, DWORD dwFlags, HWND hwndTarget }
		{ GenericUsagePage, HID_USAGE_GENERIC_POINTER, 0, InWnd },
		{ GenericUsagePage, HID_USAGE_GENERIC_MOUSE, 0, InWnd },
		{ GenericUsagePage, HID_USAGE_GENERIC_JOYSTICK, 0, InWnd },
		{ GenericUsagePage, HID_USAGE_GENERIC_GAMEPAD, 0, InWnd },
		{ GenericUsagePage, HID_USAGE_GENERIC_KEYBOARD, 0, InWnd },
		{ GenericUsagePage, HID_USAGE_GENERIC_KEYPAD, 0, InWnd },
		//{ GenericUsagePage, HID_USAGE_GENERIC_MULTI_AXIS_CONTROLLER, 0, InWnd },
	};

	return ARRAYSIZE(ridlist);
}
