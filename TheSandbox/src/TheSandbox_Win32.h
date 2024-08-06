#ifndef THESANDBOX_WIN32_H
#define THESANDBOX_WIN32_H

#include "TheSandbox_Common.h"

LRESULT CALLBACK TheSandbox_WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
int TheSandbox_WinMain(HINSTANCE inst, HINSTANCE prev, PSTR cmdline, int wndshow);

#endif // THESANDBOX_WIN32_H