#include "HIDCFG_Win32.h"
#include "Input.h"

int HIDCFG_WinMain(HINSTANCE HInst, HINSTANCE HPrevInst, PSTR CmdLine, int AppWin)
{
	int ExitCode = 0;

	WNDCLASSEX WndClass = {};
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_GLOBALCLASS|CS_HREDRAW|CS_VREDRAW;
	WndClass.lpfnWndProc = HIDCFG_WinProc;
	WndClass.hInstance = HInst;
	WndClass.lpszClassName = GAppNameW;

	RegisterClassEx(&WndClass);

	RECT WndRect = { 0, 0, GWindowWidth, GWindowHeight };
	DWORD WndStyle = WS_CAPTION;
	DWORD WndExStyle = WS_EX_OVERLAPPEDWINDOW;
	AdjustWindowRectEx(&WndRect, WndStyle, FALSE, WndExStyle);

	HWND WindowHandle = CreateWindowEx
	(
		WndExStyle,
		GAppNameW,
		GAppNameW,
		WndStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WndRect.right - WndRect.left,
		WndRect.bottom - WndRect.top,
		nullptr,
		nullptr,
		HInst,
		nullptr
	);

	Assert(WindowHandle);

	GbRunning = true;
	ShowWindow(WindowHandle, AppWin);

	EnumerateHIDs(WindowHandle);

	while (GbRunning)
	{
		MSG msg;
		BOOL Result;
		while (Result = PeekMessage(&msg, WindowHandle, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// ...
	}

	return ExitCode;
}

LRESULT HIDCFG_HandleKeyMsg(UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT Result = 0;

	if (msg == WM_KEYDOWN)
	{
		switch (wparam)
		{
			case VK_ESCAPE:
			{
				GbRunning = false;
			} break;
			default:
			{
				// ...
			} break;
		}
	}
	else if (msg == WM_KEYDOWN)
	{
		// ...
	}

	return Result;
}

LRESULT CALLBACK HIDCFG_WinProc(HWND WinHandle, UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT Result = 0;

	switch (msg)
	{
		case WM_CLOSE:
		case WM_DESTROY:
		case WM_QUIT:
		{
			GbRunning = false;
		} break;
		case WM_KEYDOWN:
		case WM_KEYUP:
		{
			Result = HIDCFG_HandleKeyMsg(msg, wparam, lparam);
		} break;
		default:
		{
			Result = DefWindowProc(WinHandle, msg, wparam, lparam);
		} break;
	}

	return Result;
}
