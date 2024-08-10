#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// CKA_TODO: Platform detection
#define PLATFORM_WINDOWS() (1)
#define PLATFORM_LINUX() (0)

#if PLATFORM_LINUX()
int main(int argc, const char* argv[])
{

}
#elif PLATFORM_WINDOWS()
int WinMain(HINSTANCE Inst, HINSTANCE Prev, PSTR CmdLine, int WndShow)
{
	OutputDebugString(L"\nTest print\n");
}
#else
#error "Platform must be defined"
#endif // PLATFORM