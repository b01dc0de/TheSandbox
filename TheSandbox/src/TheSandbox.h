#ifndef THESANDBOX_H
#define THESANDBOX_H

#include "TheSandbox_Common.h"

namespace TheSandbox
{
	int MainLoop();
	int Init(HINSTANCE Inst, HINSTANCE PrevInst, PSTR CmdLine, int WndShow);
	int Term();
}

#endif // THESANDBOX_H