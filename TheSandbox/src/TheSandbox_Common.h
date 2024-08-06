#ifndef THESANDBOX_COMMON_H
#define THESANDBOX_COMMON_H

// Windows headers
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <wingdi.h>
// OpenGL headers
#include <gl\GL.h>
#include <gl\GLU.h>
// C/C++ std lib headers
#include <cstdio>

namespace TheSandbox
{
	extern bool bRunning;
}

#endif // THESANDBOX_COMMON_H