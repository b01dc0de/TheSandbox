#ifndef HIDCFG_WIN32_H
#define HIDCFG_WIN32_H

#include "HIDCFG_Common.h"

int HIDCFG_WinMain(HINSTANCE Hinst, HINSTANCE HPrevInst, PSTR CmdLine, int AppWin);
LRESULT CALLBACK HIDCFG_WinProc(HWND WinHandle, UINT msg, WPARAM wparam, LPARAM lparam);

#endif // HIDCFG_WIN32_H