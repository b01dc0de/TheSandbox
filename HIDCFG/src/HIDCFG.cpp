#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

int HIDCFG_WinMain(HINSTANCE Hinst, HINSTANCE HPrevInst, PSTR CmdLine, int AppWin);
LRESULT CALLBACK HIDCFG_WinProc(HWND WinHandle, UINT msg, WPARAM wparam, LPARAM lparam);

constexpr int GWindowWidth = 1600;
constexpr int GWindowHeight = 900;
LPCSTR GAppNameA = "HIDCFG";
LPCWSTR GAppNameW = L"HIDCFG";
bool GbRunning = false;

int WINAPI WinMain
(
	HINSTANCE HInst,
	HINSTANCE HPrevInst,
	LPSTR CmdLine,
	int ShowWin
)
{
	OutputDebugStringA("HIDCFG -- Init\n\t");

	OutputDebugStringA(CmdLine);

	int ExitCode = HIDCFG_WinMain(HInst, HPrevInst, CmdLine, ShowWin);

	OutputDebugStringA("\nHIDCFG -- TERM\n");

	return ExitCode;
}

#define Assert(exp) \
	if (!(exp)) \
	{ \
		OutputDebugStringA("FAILED ASSERT: " #exp "\n"); \
		DebugBreak(); \
	}

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

	while (GbRunning)
	{
		// ...
		break;
	}

	return ExitCode;
}

LRESULT CALLBACK HIDCFG_WinProc(HWND WinHandle, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// CKA_TODO: Implement

	LRESULT Result = DefWindowProc(WinHandle, msg, wparam, lparam);

	return Result;
}
