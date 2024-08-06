#include "TheSandbox_Common.h"
#include "TheSandbox_Win32.h"
#include "TheSandbox.h"

LRESULT CALLBACK TheSandbox_WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT Result = 0;

	switch (msg)
	{
		case WM_CLOSE:
		case WM_DESTROY:
		case WM_QUIT:
		{
			TheSandbox::bRunning = false;
		} break;
		case WM_KEYDOWN:
		case WM_KEYUP:
		{
			if (wparam == VK_ESCAPE)
			{
				TheSandbox::bRunning = false;
			}
		} break;
		default:
		{
			Result = DefWindowProc(hwnd, msg, wparam, lparam);
		} break;
	}

	return Result;
}

int TheSandbox_WinMain
(
	HINSTANCE inst,
	HINSTANCE prev,
	PSTR cmdline,
	int wndshow
)
{
	int Result = 0;

	Result += TheSandbox::Init(inst, prev, cmdline, wndshow);
	Result += TheSandbox::MainLoop();
	Result += TheSandbox::Term();

	return Result;
}
