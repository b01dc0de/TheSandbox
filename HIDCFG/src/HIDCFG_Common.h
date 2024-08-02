#ifndef HIDCFG_COMMON_H
#define HIDCFG_COMMON_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

constexpr int GWindowWidth = 1600;
constexpr int GWindowHeight = 900;
constexpr LPCSTR GAppNameA = "HIDCFG";
constexpr LPCWSTR GAppNameW = L"HIDCFG";
extern bool GbRunning;

#define Assert(exp) \
	if (!(exp)) \
	{ \
		OutputDebugStringA("FAILED ASSERT: " #exp "\n"); \
		DebugBreak(); \
	}

#endif // HIDCFG_COMMON_H
