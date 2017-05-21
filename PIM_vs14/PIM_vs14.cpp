// PIM_vs14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "pim.h"

int main()
{
	char filePath[MAXPATH],
		command[100];

	printf("Presonal Information Management (PIM)\n");
	printf("(C) 2017 Suttipong. All right reserved.\n\n");

	while(1)
	{
		fseek(stdin, 0, SEEK_END);

		printf("PIM>");
		gets_s(command, 100); fflush(stdin);
		if (Process(command, filePath) == Exit())
			return 0;
	}

    return 0;
}

