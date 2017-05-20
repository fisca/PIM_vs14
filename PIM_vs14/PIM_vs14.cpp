// PIM_vs14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define MAXPATH 100

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
void OpenFileMenu(char*, char*);
void AddPerson(char*);
void PrintPerson(char*);
int IsPersonExist(FILE*, char*, char *);
void LowerString(char*);

int main()
{
	char path[] = "c:\\data\\", 
		filePath[MAXPATH], 
		wrong[] = "\n Wrong value. Please enter N, O, A, E, P or X\n\n";

	printf("*** Presonal Information Management ***\n\n");
	while (1)
	{
		fseek(stdin, 0, SEEK_END);

		char op, buf[50];			

		printf("| (N)ew | (O)pen | (A)dd | (E)dit | (P)rint | e(X)it |: ");
		gets_s(buf, 50); fflush(stdin);

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
			OpenFileMenu(path, filePath);
			break;
		case 'A':
			AddPerson(filePath);
			break;
		case 'E':
			// EditPersion
			break;
		case 'P':
			PrintPerson(filePath);
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

	printf("*** Create New File ***\n");
	printf("Enter file name to create: "); fflush(stdin);
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
		printf("Create file fail, file already exist\n\n");

	fclose(fp);
}

void OpenFileMenu(char *path, char *filePath)
{
	FILE *fp;
	char fName[30];	
	
	printf("Enter file name to open: ");
	scanf_s("%s", fName, 30); fflush(stdin);

	strcpy_s(filePath, 100, path);
	strcat_s(filePath, 100, fName);

	if(fopen_s(&fp, filePath, "rb") != 0)
		printf("Cannot find or open file %s\n", filePath);
	else
	{
		printf("Open file successful\n");
		fclose(fp);
	}
	printf("\n");
}

void AddPerson(char *filePath) 
{	
	FILE *fp;
	Personal person;

	if (fopen_s(&fp, filePath, "rb+") != 0)
		printf("Please open file before add person\n");
	else
	{
		printf("*** Add Person ***\n");
		printf("To stop with first name = 0\n");
		fseek(fp, 0, SEEK_END);
		while (1)
		{
			char fName[20], lName[20];
			printf("First name: ");
			scanf_s("%s", fName, 20); fflush(stdin);

			if (fName[0] == '0')
				break;
			strcpy_s(person.firstName, 20, fName);

			printf("Last name: "); 
			scanf_s("%s", lName, 20); fflush(stdin);
			strcpy_s(person.lastName, 20, lName);

			if(IsPersonExist(fp, fName, lName) == 0)
			{
				printf("Fail, person already exists\n");
				break;
			}

			printf("House number: ");
			scanf_s("%s", person.address.houseNo, 10); fflush(stdin);
			printf("Road: ");
			scanf_s("%s", person.address.road, 20); fflush(stdin);
			printf("Amphoe: ");
			scanf_s("%s", person.address.amphoe, 20); fflush(stdin);
			printf("City: ");
			scanf_s("%s", person.address.city, 20); fflush(stdin);
			printf("Zipe code: ");
			scanf_s("%d", &person.address.zipCode); fflush(stdin);
			printf("\n");

			if(fwrite(&person, sizeof(person), 1, fp) == 1)	
				printf("Add person: %s %s successful\n", person.firstName, person.lastName);
			else
				printf("Add person: %s %s successful\n", person.firstName, person.lastName);
		}
		fclose(fp);
	}
	printf("\n");	
}

//void EditPerson(char*);

void PrintPerson(char *filePath)
{
	FILE *fp;
	Personal person;

	if (fopen_s(&fp, filePath, "rb") != 0)
		printf("Please open file before print person\n");
	else
	{
		fseek(fp, 0, SEEK_SET);
		printf("Rec# First_Name Last_name, Address\n");
		int i = 0;
		while (fread(&person, sizeof(person), 1, fp));
		{
			printf("%s %s %s\n", person.firstName, person.lastName, person.address.houseNo);
			i++;
		}

		if(i == 0)
			printf("No Data\n");

		fclose(fp);
	}
	printf("\n");
}

void LowerString(char *str)
{
	for (int i = 0; i < (int)strlen(str); i++) 
		str[i] = tolower(str[i]);
}

int IsPersonExist(FILE *fp, char *firstName, char *lastName)
{
	Personal person;
	char fname[20], lname[20];	
	strcpy_s(fname, 20, firstName);
	strcpy_s(lname, 20, lastName);
	LowerString(fname);
	LowerString(lname);

	fseek(fp, 0, SEEK_SET);
	while (fread(&person, sizeof(person), 1, fp))
	{
		char fN[20], lN[20];
		strcpy_s(fN, 20, person.firstName);
		strcpy_s(lN, 20, person.lastName);
		LowerString(fN);
		LowerString(lN);

		if (strcmp(fname, fN) == 0 && strcmp(lname, lN) == 0)
			return 0;
	}

	return 1;
}



