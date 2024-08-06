#include "TheSandbox_Win32.h"

bool bGlobalRunning = true;

int WINAPI WinMain
(
	HINSTANCE inst,
	HINSTANCE prev,
	PSTR cmdline,
	int showwnd
)
{
	int ExitCode = TheSandbox_WinMain(inst, prev, cmdline, showwnd);

	return ExitCode;
}
