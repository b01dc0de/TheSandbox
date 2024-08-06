#include "TheSandbox_Common.h"
#include "TheSandbox_Win32.h"

LRESULT CALLBACK TheSandbox_WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT Result = 0;

	switch (msg)
	{
		case WM_CLOSE:
		case WM_DESTROY:
		case WM_QUIT:
		{
			bGlobalRunning = false;
		} break;
		case WM_KEYDOWN:
		case WM_KEYUP:
		{
			if (wparam == VK_ESCAPE)
			{
				bGlobalRunning = false;
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
	printf("TheSandbox -- INIT\n");

	int Result = 0;

	const WCHAR* TSB_AppName = L"TheSandbox";
	constexpr UINT TSB_AppWidth = 1600u;
	constexpr UINT TSB_AppHeight = 900u;

	WNDCLASSEX WndClass = {};
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WndClass.lpfnWndProc = TheSandbox_WndProc;
	WndClass.hInstance = inst;
	WndClass.lpszClassName = TSB_AppName;

	RegisterClassEx(&WndClass);

	HWND WindowHandle = CreateWindowEx
	(
		WS_EX_OVERLAPPEDWINDOW,
		TSB_AppName,
		TSB_AppName,
		WS_VISIBLE|WS_OVERLAPPEDWINDOW|WS_CAPTION,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		TSB_AppWidth,
		TSB_AppHeight,
		nullptr,
		nullptr,
		inst,
		nullptr
	);

	// Initialize OpenGL
	PIXELFORMATDESCRIPTOR PxFmtDesc{};
	PxFmtDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	PxFmtDesc.nVersion = 1;
	PxFmtDesc.dwFlags = PFD_DRAW_TO_WINDOW|PFD_DRAW_TO_BITMAP|PFD_SUPPORT_OPENGL|PFD_GENERIC_ACCELERATED|PFD_DOUBLEBUFFER;
	PxFmtDesc.iPixelType = PFD_TYPE_RGBA;
	PxFmtDesc.cColorBits = 32;
	PxFmtDesc.cDepthBits = 24;
	PxFmtDesc.cStencilBits = 8;
	PxFmtDesc.iLayerType = PFD_MAIN_PLANE;

	HDC opengl_dc;
	HGLRC opengl_rc;


	if (WindowHandle)
	{
		opengl_dc = GetDC(WindowHandle);
		opengl_rc = wglCreateContext(opengl_dc);

		int iPxFmt = ChoosePixelFormat(opengl_dc, &PxFmtDesc);
		SetPixelFormat(opengl_dc, iPxFmt, &PxFmtDesc);

		wglMakeCurrent(opengl_dc, opengl_rc);

		bGlobalRunning = true;

		ShowWindow(WindowHandle, wndshow);

		while (bGlobalRunning)
		{
			MSG msg;
			BOOL Result;
			while (Result = PeekMessage(&msg, WindowHandle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				// ...
			}
		}

		// Terminate OpenGL
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(opengl_rc);
	}
	else
	{
		Result = 1;
	}

	printf("TheSandbox -- TERM\n");

	return Result;
}
