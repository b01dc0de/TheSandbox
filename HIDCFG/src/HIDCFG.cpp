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

int HIDCFG_WinMain(HINSTANCE HInst, HINSTANCE HPrevInst, PSTR CmdLine, int AppWin)
{
	int ExitCode = 0;

	WNDCLASSEX WindClass = {};
	WindClass.cbSize = sizeof(WNDCLASSEX);
	WindClass.style = CS_GLOBALCLASS|CS_HREDRAW|CS_VREDRAW;
	WindClass.lpfnWndProc = HIDCFG_WinProc;
	WindClass.hInstance = HInst;
	WindClass.lpszClassName = GAppNameW;
	//WindClass.cbClsExtra = 0;
	//WindClass.cbWndExtra = 0;
	//WindClass.hIcon;
	//WindClass.hCursor;
	//WindClass.hbrBackground;
	//WindClass.lpszMenuName;
	//WindClass.hIconSm;

	RegisterClassEx(&WindClass);

	HWND WindowHandle = CreateWindowEx
	(
		0,
		GAppNameW,
		GAppNameW,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nullptr,
		nullptr,
		HInst,
		nullptr
	);

	if (WindowHandle)
	{
		GbRunning = true;

		ShowWindow(WindowHandle, AppWin);

		while (GbRunning)
		{
			// ...
		}
	}
	else
	{
		DWORD Error = GetLastError();
		ExitCode = 1;
		DebugBreak();
	}

	return ExitCode;
}

LRESULT CALLBACK HIDCFG_WinProc(HWND WinHandle, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// CKA_TODO: Implement

	LRESULT Result = 0;

	switch (msg)
	{
		default:
		{
		} break;
	}

	return Result;
}
