#include "HIDCFG_Common.h"
#include "HIDCFG_Win32.h"

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

