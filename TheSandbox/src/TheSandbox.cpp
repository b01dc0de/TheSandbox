#include <cstdio>

int main(int argc, const char* argv[])
{
	printf("TheSandbox -- INIT\n");

	for (int i = 0; i < argc; i++)
	{
		printf("\t%s\n", argv[i]);
	}

	printf("TheSandbox -- TERM\n");
}