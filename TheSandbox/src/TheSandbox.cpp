#include "TheSandbox.h"
#include "TheSandbox_Common.h"
#include "TheSandbox_Win32.h"

const WCHAR* TSB_AppName = L"TheSandbox";
constexpr UINT TSB_AppWidth = 1600u;
constexpr UINT TSB_AppHeight = 900u;

// CKA_NOTE: See https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions#Windows_2
void* GetAnyGLFuncAddress(const char* name)
{
	void* p = (void*)wglGetProcAddress(name);
	if (p == 0 || (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) || (p == (void*)-1))
	{
		HMODULE module = LoadLibraryA("opengl32.dll");
		if (module) { p = (void*)GetProcAddress(module, name); }
	}

	return p;
}

namespace TheSandbox
{
	bool bRunning = false;

	HWND WindowHandle;
	HINSTANCE Inst;
	PSTR CmdLine;
	int WndShow;

	HDC opengl_dc;
	HGLRC opengl_rc;

	int MainLoop()
	{
		int Result = 0;

		bRunning = true;

		ShowWindow(WindowHandle, WndShow);

		while (bRunning)
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

		return Result;
	}

	int Init(HINSTANCE Inst, HINSTANCE PrevInst, PSTR CmdLine, int WndShow)
	{
		int Result = 0;

		printf("TheSandbox -- INIT\n");

		WNDCLASSEX WndClass = {};
		WndClass.cbSize = sizeof(WNDCLASSEX);
		WndClass.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		WndClass.lpfnWndProc = TheSandbox_WndProc;
		WndClass.hInstance = Inst;
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
			Inst,
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

		if (WindowHandle)
		{ // Create Dummy GL context
			PIXELFORMATDESCRIPTOR DummyPxFmtDesc = PxFmtDesc;

			HDC dummy_hdc = GetDC(WindowHandle);
			HGLRC dummy_glrc = wglCreateContext(dummy_hdc);

			int iDummyPxFmt = ChoosePixelFormat(TheSandbox::opengl_dc, &PxFmtDesc);
			SetPixelFormat(TheSandbox::opengl_dc, iDummyPxFmt, &PxFmtDesc);

			wglMakeCurrent(dummy_hdc, dummy_glrc);

			wglMakeCurrent(nullptr, nullptr);
			wglDeleteContext(dummy_glrc);
		}

		if (WindowHandle)
		{
			TheSandbox::opengl_dc = GetDC(WindowHandle);
			TheSandbox::opengl_rc = wglCreateContext(TheSandbox::opengl_dc);

			int iPxFmt = ChoosePixelFormat(TheSandbox::opengl_dc, &PxFmtDesc);
			SetPixelFormat(TheSandbox::opengl_dc, iPxFmt, &PxFmtDesc);

			wglMakeCurrent(TheSandbox::opengl_dc, TheSandbox::opengl_rc);

			WindowHandle = WindowHandle;
			HINSTANCE GlobalInst = Inst;
			PSTR GlobalCmdLine = CmdLine;
			int GlobalWindowShow = WndShow;
		}
		else
		{
			Result = 1;
		}

		return Result;
	}

	int Term()
	{
		int Result = 0;

		printf("TheSandbox -- TERM\n");

		// Terminate OpenGL
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(opengl_rc);

		return Result;
	}
}

