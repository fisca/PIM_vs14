// PIM_vs14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct Address {
	char houseNo[10];
	char road[20];
	char amphoe[20];
	char city[20];
	int zipCode;
};

struct Personal {
	char firstName[20];
	char lastName[20];
	struct Address address;
};

void CreateNewFile(char*);
void OpenFileMenu(char*);

int main()
{	
	printf("*** Presonal Information Management ***\n\n");

	while (1)
	{
		fseek(stdin, 0, SEEK_END);

		char op, buf[50],
			path[] = "c:\\data\\", 
			wrong[] = "\n Wrong value. Please enter N, O, A, E, P or X\n\n";

		printf("| (N)ew | (O)pen | (A)dd | (E)dit | (P)rint | e(X)it |: "); fflush(stdin);
		gets_s(buf, 50);

		if (strlen(buf) == 1)
		{
			op = toupper(buf[0]);
			if (op != 'N' && op != 'O' && op != 'A' && op != 'E' && op != 'P' && op != 'X')
			{
				printf("%s", wrong); 
				continue;
			}						
		}
		else 
		{
			printf("%s", wrong);
			continue;
		}						

		switch (op)
		{
		case 'N':
			CreateNewFile(path);
			break;
		case 'O':
			OpenFileMenu(path);
			break;
		case 'A':
			// AddPersonal
			break;
		case 'E':
			// EditPersional
			break;
		case 'P':
			// PrintPersonal
			break;
		case 'X':
			printf("\nThank you. Good Bye. Stop program in "); 
			for (int i = 3; i > 0; i--) { printf("%d ", i); Sleep(1000); } 
			return 0;
		default:
			break;
		}
	}	

    return 0;
}

void CreateNewFile(char *path)
{
	FILE *fp;
	char fileName[100], fName[30];

	printf("Enter file name to create new file: "); fflush(stdin);
	scanf_s("%s", fName, 20);

	fileName[0] = '\0';
	strcat_s(fileName, 100, path);
	strcat_s(fileName, 100, fName);

	if (fopen_s(&fp, fileName, "rb") != 0)
	{
		if (fopen_s(&fp, fileName, "wb") != 0)
			printf("Cannot create new file %s\n\n", fileName);
		else
			printf("Create new file successful\n\n");
	}
	else
		printf("Cannot crete new file because file already exist\n\n");

	fclose(fp);
}

void OpenFileMenu(char *path)
{
	FILE *fp;
	char fileName[100], fName[30];	
	
	printf("Enter file name to open: "); fflush(stdin);
	scanf_s("%s", fName, 30);

	fileName[0] = '\0';
	strcat_s(fileName, 100, path);
	strcat_s(fileName, 100, fName);	

	if(fopen_s(&fp, fileName, "rb") != 0)
		printf("Cannot find or open file %s\n\n", fileName);
	else
	{
		printf("Open file successful\n\n");
		fclose(fp);
	}	
}



