#pragma once

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

void LowerString(char*);
void Trim(char*);

//-------------------------------------------------------------------------------------

int IsPersonExist(FILE *fp, char *firstName, char *lastName)
{
	Personal person;
	char fname[20], lname[20];
	strcpy_s(fname, 20, firstName);
	strcpy_s(lname, 20, lastName);
	Trim(fname);
	Trim(lname);
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

void LowerString(char *str)
{
	for (int i = 0; i < (int)strlen(str); i++)
		str[i] = tolower(str[i]);
}

int StopCmd(char *cmd)
{
	Trim(cmd);
	LowerString(cmd);
	return strlen(cmd) == 2 && strncmp("-b", cmd, 2) == 0 ? 0 : 1;
}

// Trim() -- credit: http://stackoverflow.com/questions/2450704/writing-string-trim-in-c
void Trim(char *str)
{
	char *start, *end;

	/* Find first non-whitespace */
	for (start = str; *start; start++)
	{
		if (!isspace((unsigned char)start[0]))
			break;
	}

	/* Find start of last all-whitespace */
	for (end = start + strlen(start); end > start + 1; end--)
	{
		if (!isspace((unsigned char)end[-1]))
			break;
	}

	*end = 0; /* Truncate last whitespace */

			  /* Shift from "start" to the beginning of the string */
	if (start > str)
		memmove(str, start, (end - start) + 1);
}

//--------------------------------------------------------------------------------------

//--- Commands
void AddPerson(char *filePath)
{
	FILE *fp;

	if (fopen_s(&fp, filePath, "rb+") != 0)
		printf("Please open file before add person\n");
	else
	{
		printf("Add Person\n");
		fseek(fp, 0, SEEK_END);
		while (1)
		{
			fseek(stdin, 0, SEEK_END);		

			Personal person;
			char fName[20], lName[20],
				fN[20], lN[20], hNo[10], rd[20], amp[20], cty[20], tZip[10];

			printf("Type person informatin or type '-b' to stop command.\n");	

			printf("  First name: ");
			scanf_s("%s", fName, 20); fflush(stdin);
			strcpy_s(fN, 20, fName);
			if (StopCmd(fN) == 0)
				break;

			printf("   Last name: ");
			scanf_s("%s", lName, 20); fflush(stdin);
			strcpy_s(lN, 20, lName);
			if (StopCmd(fN) == 0)
				break;

			if (IsPersonExist(fp, fName, lName) == 0)
			{
				printf("Person already exists.\n");
				break;
			}

			Trim(fName);
			Trim(lName);
			strcpy_s(person.firstName, 20, fName);
			strcpy_s(person.lastName, 20, lName);

			printf("House number: ");
			scanf_s("%s", person.address.houseNo, 10); fflush(stdin);
			strcpy_s(hNo, 10, person.address.houseNo);
			if (StopCmd(hNo) == 0)
				break;
			
			printf("        Road: ");
			scanf_s("%s", person.address.road, 20); fflush(stdin);
			strcpy_s(rd, 20, person.address.road);
			if (StopCmd(rd) == 0)
				break;

			printf("      Amphoe: ");
			scanf_s("%s", person.address.amphoe, 20); fflush(stdin);
			strcpy_s(amp, 20, person.address.amphoe);
			if (StopCmd(amp) == 0)
				break;

			printf("        City: ");
			scanf_s("%s", person.address.city, 20); fflush(stdin);
			strcpy_s(cty, 20, person.address.city);
			if (StopCmd(cty) == 0)
				break;
			
			printf("    Zip code: ");
			scanf_s("%s", tZip, 10); fflush(stdin);
			if (StopCmd(tZip) == 0)
				break;
			else
				person.address.zipCode = atoi(tZip);				

			printf("\n");

			if (fwrite(&person, sizeof(person), 1, fp) == 1)
				printf("Add person: %s %s successful\n\n", person.firstName, person.lastName);
			else
				printf("Add person: %s %s fail\n\n", person.firstName, person.lastName);
		}
		fclose(fp);
	}
	printf("\n");
}

void EditPerson(char *filePath)
{
	FILE *fp;	

	if (fopen_s(&fp, filePath, "rb+") != 0)
		printf("Please open file before edit person\n");
	else
	{
		printf("Edit Person\n");
		while(1)
		{
			fseek(stdin, 0, SEEK_END);

			/*
			printf("Type information to fine person brfore edit or type '-b' to stop command.\n");
			printf("First name: ");
			scanf_s("%s", fName, 20); fflush(stdin);
			strcpy_s(fN, 20, fName);
			if (StopCmd(fN) == 0)
				break;

			printf(" Last name: ");
			scanf_s("%s", lName, 20); fflush(stdin);
			strcpy_s(lN, 20, lName);
			if (StopCmd(fN) == 0)
				break;		

			if (IsPersonExist(fp, fName, lName) != 0)
			{
				printf("Person not exists.\n\n");
				break;
			}
			*/

			Personal person;
			unsigned long findRec;
			char tRec[10];

			printf("Type information to edit or type '-b' to stop command.\n");
			printf("Rec#: ");
			//scanf_s("%lu", &findRec, sizeof(findRec));
			scanf_s("%s", tRec, 10); fflush(stdin);
			if (StopCmd(tRec) == 0)
				break;
			else
			{
				Trim(tRec);
				findRec = atoi(tRec);
			}				

			fseek(fp, 0, SEEK_END);
			if((findRec > 0) && (findRec <= (ftell(fp)/sizeof(person))))
			{
				fseek(fp, sizeof(person) * (findRec - 1), SEEK_SET);
				fread(&person, sizeof(person), 1, fp);
				printf(" Rec# First_Name      Last_name       Address\n");
				printf(" ------------------------------------------------------------------------------\n");
				printf(" %-4d %-15s %-15s %s %s %s %s %d\n\n", findRec, person.firstName, person.lastName, person.address.houseNo,
					person.address.road, person.address.amphoe, person.address.city, person.address.zipCode);

				char fName[20], lName[20],
					fN[20], lN[20], hNo[10], rd[20], amp[20], cty[20], tZip[10];

				printf("Type new informatin for Rec# %d.\n", findRec);

				printf("  First name: ");
				scanf_s("%s", fName, 20); fflush(stdin);
				strcpy_s(fN, 20, fName);
				if (StopCmd(fN) == 0)
					break;

				printf("   Last name: ");
				scanf_s("%s", lName, 20); fflush(stdin);
				strcpy_s(lN, 20, lName);
				if (StopCmd(fN) == 0)
					break;

				Trim(fName);
				Trim(lName);
				strcpy_s(person.firstName, 20, fName);
				strcpy_s(person.lastName, 20, lName);

				printf("House number: ");
				scanf_s("%s", person.address.houseNo, 10); fflush(stdin);
				strcpy_s(hNo, 10, person.address.houseNo);
				if (StopCmd(hNo) == 0)
					break;

				printf("        Road: ");
				scanf_s("%s", person.address.road, 20); fflush(stdin);
				strcpy_s(rd, 20, person.address.road);
				if (StopCmd(rd) == 0)
					break;

				printf("      Amphoe: ");
				scanf_s("%s", person.address.amphoe, 20); fflush(stdin);
				strcpy_s(amp, 20, person.address.amphoe);
				if (StopCmd(amp) == 0)
					break;

				printf("        City: ");
				scanf_s("%s", person.address.city, 20); fflush(stdin);
				strcpy_s(cty, 20, person.address.city);
				if (StopCmd(cty) == 0)
					break;

				printf("    Zip code: ");
				scanf_s("%s", tZip, 10); fflush(stdin);
				if (StopCmd(tZip) == 0)
					break;
				else
					person.address.zipCode = atoi(tZip);

				fseek(fp, -(long)sizeof(person), SEEK_CUR);
				fwrite(&person, sizeof(person), 1, fp);
				printf("Edit personal information successful.\n");

				break;
			}
			else
				printf("Rec# %d dose not exist.\n\n", findRec);
		}
		fclose(fp);
	}
	printf("\n");
}

int Exit()
{
	//printf("\nThank you. Good Bye. Stop program in ... ");
	//for (int i = 3; i > 0; i--) { printf("%d ", i); Sleep(1000); }
	return 99;
}

void Help()
{
	printf("Command List for PIM\n");
	printf("ADD            Add new person.\n");
	printf("EDIT           Edit person information.\n");
	printf("EXIT           Quits program.\n");
	printf("HELP           Provides Help information for commands.\n");
	printf("NEW            Create new file.\n");
	printf("OPEN           Open file.\n");
	printf("PRINT          Display all information in file.\n");
	printf("\n");
}

void NewFile(char *filePath)
{
	FILE *fp;
	char fName[30];

	printf("Create New File\n");
	while(1)
	{
		fseek(stdin, 0, SEEK_END);

		char fN[30];
		printf("Type file name to create or type '-b' to stop command\n"); 
		printf("File name: ");
		scanf_s("%s", fName, 20); fflush(stdin);

		strcpy_s(fN, 30, fName);
		if (StopCmd(fN) == 0)
			break;

		strcpy_s(filePath, 100, fName);

		if (fopen_s(&fp, filePath, "rb") != 0)
		{
			if (fopen_s(&fp, filePath, "wb") != 0)
				printf("Cannot create new file %s\n", filePath);
			else 
			{
				printf("Create new file successful\n");
				fclose(fp);
				break;
			}
		}
		else
			printf("Create file fail, file already exist\n\n");

		fclose(fp);
	}
	printf("\n");
}

void OpenPersonFile(char *filePath)
{
	FILE *fp;
	char fName[30];

	printf("Open File\n");
	while (1)
	{
		fseek(stdin, 0, SEEK_END);

		char fN[30];
		printf("Type file name to open or type '-b' to stop command.\n");
		printf("File name: ");
		scanf_s("%s", fName, 30); fflush(stdin);

		strcpy_s(fN, 30, fName);
		if (StopCmd(fN) == 0)
			break;

		strcpy_s(filePath, 100, fName);

		if (fopen_s(&fp, filePath, "rb") != 0)
		{
			printf("Cannot find or open file '%s'\n\n", fName);
		}
		else
		{
			printf("Open file successful\n");
			fclose(fp);
			break;
		}
	}
	printf("\n");
}

void PrintPerson(char *filePath)
{
	FILE *fp;
	Personal person;// = { '\0', '\0' };
	//person.address = { '\0', '\0', '\0', '\0', 0 };

	if (fopen_s(&fp, filePath, "rb") != 0)
		printf("Please open file before print person\n");
	else
	{
		printf("Print Personal Information in %s\n", filePath);
		printf(" Rec# First_Name      Last_name       Address\n");
		printf(" ------------------------------------------------------------------------------\n");
		fseek(fp, 0, SEEK_SET);
		int i = 0;
		while (fread(&person, sizeof(person), 1, fp))
		{
			if (person.firstName[0] == '\0')
			{
				printf("No Data\n\n");
				fclose(fp);
				return;
			}
			printf(" %-4d %-15s %-15s %s %s %s %s %d\n", i + 1, person.firstName, person.lastName, person.address.houseNo,
				person.address.road, person.address.amphoe, person.address.city, person.address.zipCode);
			i++;
		}
		fclose(fp);
	}
	printf("\n");
}

//--- Process Command
int Process(char *command, char *filePath)
{
	// command: add, edit, exit, help, new, open, print
	Trim(command);
	LowerString(command);

	if (strlen(command) == 3 && strncmp("add", command, 3) == 0)
	{
		AddPerson(filePath);
		return 1;
	}
	else if (strlen(command) == 4 && strncmp("edit", command, 4) == 0)
	{
		EditPerson(filePath);
		return 1;
	}
	else if (strlen(command) == 4 && strncmp("exit", command, 4) == 0)
	{		
		return Exit();
	}
	else if (strlen(command) == 4 && strncmp("help", command, 4) == 0)
	{
		Help();
		return 1;
	}
	else if (strlen(command) == 3 && strncmp("new", command, 3) == 0)
	{
		NewFile(filePath);
		return 1;
	}
	else if (strlen(command) == 4 && strncmp("open", command, 4) == 0)
	{
		OpenPersonFile(filePath);
		return 0;
	}
	else if (strlen(command) == 5 && strncmp("print", command, 5) == 0)
	{
		PrintPerson(filePath);
		return 1;
	}
	else
	{
		printf("'%s' is not command.\nType 'help' to see list of commands.\n\n", command);
		return -1;
	}
}

