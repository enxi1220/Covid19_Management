/*By Tham Jun Yuan*/
#include "Header.h"
#define FILE_NAME "VisitorInfo.bin"

int vstChoice = -1;
int* c;
*c = &vstChoice;
int no = 1;

typedef struct {
	char ic[SPACE];
	char name[SPACE];
	char phoneNo[SPACE];
	char category[SPACE];
	char visitedPlace[SPACE];
	char riskLvl[SPACE];
	Time date;
	float temp;
}visitor;

visitor visit[200];

/* *********************************Validation**********************************/
int visitor_validateName(char name[SPACE]) {
	int lenN = strlen(name);

	if (lenN == 0)
	{
		printf("\n\t\tBLANK is not allowed!\n\n");
		return 1;
	}

	for (int i = 0; i < lenN; i++)
	{
		if (isalpha(name[i]) == 0)
		{
			printf("\n\t\tDigit is not allowed!\n\n");
			return 1;
		}
	}
	return 0;
}

int visitor_validateIC(char ic[SPACE]) {
	int lenIC = strlen(ic);

	if (lenIC == 0)
	{
		printf("\n\t\tBLANK is not allowed!\n\n");
		return 1;
	}

	if (lenIC > 14)
	{
		printf("\n\t\tYour IC Number is overlength!\n\n");
		return 1;
	}

	for (int i = 0; i < lenIC; i++)
	{
		if (isdigit(ic[i]) == 0)
		{
			printf("\n\t\tAlphabet is not allowed!\n");
			return 1;
		}
	}
	return 0;
}

int visitor_validateOccup(char occu[SPACE]) {
	int lenO = strlen(occu);

	for (int i = 0; i < lenO; i++)
	{
		if (isalpha(occu[i]) == 0)
		{
			printf("\n\t\tDigit / blank is not allowed!\n\n");
			return 1;
		}
	}
	return 0;
}

int visitor_validatePhoneNo(char phone[SPACE]) {
	int lenPN = strlen(phone);

	if (lenPN == 0)
	{
		printf("\n\t\tBLANK is not allowed!\n\n");
		return 1;
	}

	if (lenPN > 11)
	{
		printf("\n\t\tMaximum is only 11 digits!\n\n");
		return 1;
	}

	for (int i = 0; i < lenPN; i++)
	{
		if (isdigit(phone[i]) == 0)
		{
			printf("\n\t\tAlphabets is not accepted.\n");
			return 1;
		}
	}
	return 0;
}

int visitor_validateVisited(char place[SPACE]) {
	int lenP = strlen(place);

	if (lenP == 0)
	{
		printf("\n\t\tBLANK is not allowed!\n\n");
		return 1;
	}

	for (int i = 0; i < lenP; i++)
	{
		if (isalpha(place[i]) == 0)
		{
			printf("\n\t\tNo digit !\n\n");
			return 1;
		}
	}
	return 0;
}

int visitor_validateTemp(float temp) {
	int validateTemp = 0;

	if (temp > 34 && temp < 39)
	{
		validateTemp = 0;
	}
	else
	{
		printf("\n\t\tInvalid.Please Re-enter.\n\n");
		validateTemp = 1;
	}
	return validateTemp;
}

/* *********************************Get Current Time**********************************/
void visitor_getTime() {
	GetLocalTime(&autoTime);
	visit[no].date.day = autoTime.wDay;
	visit[no].date.month = autoTime.wMonth;
	visit[no].date.year = autoTime.wYear;
	visit[no].date.hrs = autoTime.wHour;
	visit[no].date.mins = autoTime.wMinute;
	visit[no].date.sec = autoTime.wSecond;

}

/* *********************************Add Record**********************************/
void visitor_add() {
	FILE* fptr = fopen(FILE_NAME, "ab");
	if (fptr == NULL)
	{
		printf("File cant be opened.\n");
		exit(-1);
	}

	char opT = 'Y';
	char conF = 'Y';
	int count = 0;
	int validateOccup = 0, validatePlace = 0, validateName = 0, validateIC = 0, validatePhoneNo = 0;
	int validateTemp = 0;


	printf("%44s\n", "Visitor Info Add Record");
	printf("+---------------------------------------------------------------+\n");

	do
	{
		visitor_getTime();
		printf("\t>>Date Visited        : %d/%d/%d\n", visit[no].date.day, visit[no].date.month, visit[no].date.year);
		printf("\t>>Time Visited        : %02d:%02d:%02d\n", visit[no].date.hrs, visit[no].date.mins, visit[no].date.sec);
		rewind(stdin);
		printf("\n");
		do
		{
			strcpy(visit[no].name, "");
			printf("\t>>Enter name           : ");
			scanf("%[^\n]", visit[no].name); // no = 1 
			rewind(stdin);

			validateName = visitor_validateName(visit[no].name);

		} while (validateName == 1);

		do
		{
			strcpy(visit[no].ic, "");
			printf("\t>>IC Number            : ");
			scanf("%[^\n]", visit[no].ic);
			rewind(stdin);

			validateIC = visitor_validateIC(visit[no].ic);

		} while (validateIC == 1);

		do
		{
			printf("\t>>Occupation           : ");
			scanf("%[^\n]", visit[no].category);
			rewind(stdin);

			validateOccup = visitor_validateOccup(visit[no].category);

		} while (validateOccup == 1);

		do
		{
			strcpy(visit[no].phoneNo, "");
			printf("\t>>Phone Number         : ");
			scanf("%[^\n]", visit[no].phoneNo);
			rewind(stdin);

			validatePhoneNo = visitor_validatePhoneNo(visit[no].phoneNo);

		} while (validatePhoneNo == 1);

		do
		{
			strcpy(visit[no].visitedPlace, "");
			printf("\t>>Latest venue visited : ");
			scanf("%[^\n]", visit[no].visitedPlace);
			rewind(stdin);

			validatePlace = visitor_validateVisited(visit[no].visitedPlace);

		} while (validatePlace == 1);

		do
		{

			printf("\t>>Temperature          : ");
			scanf("%f", &visit[no].temp);
			rewind(stdin);

			validateTemp = visitor_validateTemp(visit[no].temp);

		} while (validateTemp == 1);

		strcpy(visit[no].name, strupr(visit[no].name));

		printf("\nConfirm to add (Y / N)? > ");
		scanf("%c", &conF);
		if (toupper(conF) == 'Y')
		{
			fwrite(&visit[no], sizeof(visitor), 1, fptr);
			printf("\nAdded successfully.");
			count++;
		}
		else
		{
			printf("Record not added.\n");
		}

		printf("\nEnter another record? \n ");
		printf("Y - Yes     N - No > ");
		rewind(stdin);
		scanf("%c", &opT);
		no++; //2

	} while (toupper(opT) == 'Y');

	printf("\n%d records added.\n", count);

	fclose(fptr);
}

/* *********************************Display Record**********************************/
void visitor_display() {
	visitor v1;
	FILE* fptr = fopen(FILE_NAME, "rb");
	if (fptr == NULL)
	{
		printf("File cant be opened.\n");
		exit(-1);
	}

	int counter = 0;

	printf("%110s\n", "Visitor Information Records");
	printf("\t+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
	printf("\t|         Name            |          IC            |       Phone Number    |       Category        |    Visited Place      |  Temperature    |    Date Visited   |  Time Visited  |\n");
	printf("\t+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");

	while (fread(&v1, sizeof(visitor), 1, fptr))
	{

		printf("\t|%4s%-21s|%4s%-20s|%4s%-19s|%4s%-19s|%4s%-19s|%4s%7.1fC%5s|%4s%2d/%2d/%4d%5s|%4s%02d:%02d:%02d%4s|\n", " ", v1.name, " ", v1.ic, " ", v1.phoneNo, " ", v1.category, " ", v1.visitedPlace, " ", v1.temp, " ", " ", v1.date.day, v1.date.month, v1.date.year, " ", " ", v1.date.hrs, v1.date.mins, v1.date.sec, " ");
		printf("\t-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		counter++;
	}
	printf("\nTotal : %d records\n\n", counter);
	fclose(fptr);
}

/* *********************************Search Record**********************************/
void visitor_search() {

	FILE* fptr = fopen(FILE_NAME, "rb");
	if (fptr == NULL)
	{
		printf("File cant be opened.\n");
		exit(-1);
	}

	int found = 0;
	int n = 0;
	char name[SPACE];
	char ch = 'Y';

	printf("%26s\n", "Search Record");
	printf("+-------------------------------------------+\n");

	do
	{
		printf("Enter the visitor NAME to search > ");
		scanf("%[^\n]", name);
		rewind(stdin);

		while (fread(&visit[n], sizeof(visitor), 1, fptr) != 0)
		{
			n++;
		}
		for (int i = 0; i < n; i++)
		{
			if (strcmp(strupr(name), visit[i].name) == 0)
			{
				found = 1;
				printf("-------------------------------\n");
				printf("Name          :%s\n", visit[i].name);
				printf("IC            :%s\n", visit[i].ic);
				printf("Phone Number  :%s\n", visit[i].phoneNo);
				printf("Occupation    :%s\n", visit[i].category);
				printf("Visited Place :%s\n", visit[i].visitedPlace);
				printf("Temperature   :%.1fC\n\n", visit[i].temp);
				printf("Date Visited  :%d/%d/%d\n", visit[i].date.day, visit[i].date.month, visit[i].date.year);
				printf("Time Visited  :%d:%d:%d\n\n", visit[i].date.hrs, visit[i].date.mins, visit[i].date.sec);
			}
		}
		if (found == 0)
		{
			printf("\nRecord not founded.\n\n");
		}
		printf("\nSearch again? > ");
		scanf("%c", &ch);
		rewind(stdin);

	} while (toupper(ch) == 'Y');
	fclose(fptr);
}

/* *********************************Modify Record**********************************/
void visitor_modify() {
	visitor v1;

	FILE* fptr = fopen(FILE_NAME, "rb");
	FILE* fp1 = fopen("temp.bin", "wb");
	if (fptr == NULL || fp1 == NULL)
	{
		printf("File cant be opened.\n");
		exit(-1);
	}

	int found = 0;
	int validateOccup = 0, validatePlace = 0, validateName = 0, validateIC = 0, validatePhoneNo = 0;
	int validateTemp = 0;
	char name[SPACE];

	printf("%26s\n", "Modify Record");
	printf("+-------------------------------------------+\n");
	printf("Enter the visitor NAME to modify > ");
	rewind(stdin);
	scanf("%[^\n]", name);

	while (fread(&visit[no], sizeof(visitor), 1, fptr))
	{
		if (strcmp(visit[no].name, strupr(name)) == 0)
		{
			found = 1;
			printf("-------------------------------\n");
			printf("Name          :%s\n", visit[no].name);
			printf("IC            :%s\n", visit[no].ic);
			printf("Phone Number  :%s\n", visit[no].phoneNo);
			printf("Occupation    :%s\n", visit[no].category);
			printf("Visited Place :%s\n", visit[no].visitedPlace);
			printf("Temperature   :%.1fC\n\n", visit[no].temp);
			printf("-------------------------------\n");
			rewind(stdin);
			do
			{
				strcpy(visit[no].name, "");
				printf("\t>>Enter your name      : ");
				scanf("%[^\n]", visit[no].name); // no = 1 
				rewind(stdin);

				validateName = visitor_validateName(visit[no].name);

			} while (validateName == 1);

			do
			{
				strcpy(visit[no].ic, "");
				printf("\t>>IC Number            : ");
				scanf("%[^\n]", visit[no].ic);
				rewind(stdin);

				validateIC = visitor_validateIC(visit[no].ic);

			} while (validateIC == 1);

			do
			{
				strcpy(visit[no].category, "");
				printf("\t>>Occupation           : ");
				scanf("%[^\n]", visit[no].category);
				rewind(stdin);

				validateOccup = visitor_validateOccup(visit[no].category);

			} while (validateOccup == 1);

			do
			{
				strcpy(visit[no].phoneNo, "");
				printf("\t>>Phone Number         : ");
				scanf("%[^\n]", visit[no].phoneNo);
				rewind(stdin);

				validatePhoneNo = visitor_validatePhoneNo(visit[no].phoneNo);

			} while (validatePhoneNo == 1);

			do
			{
				strcpy(visit[no].visitedPlace, "");
				printf("\t>>Latest venue visited : ");
				scanf("%[^\n]", visit[no].visitedPlace);
				rewind(stdin);

				validatePlace = visitor_validateVisited(visit[no].visitedPlace);

			} while (validatePlace == 1);

			do
			{

				printf("\t>>Temperature          : ");
				scanf("%f", &visit[no].temp);
				rewind(stdin);

				validateTemp = visitor_validateTemp(visit[no].temp);

			} while (validateTemp == 1);

			strcpy(visit[no].name, strupr(visit[no].name));
		}
		fwrite(&visit[no], sizeof(visitor), 1, fp1);
	}
	fclose(fptr);
	fclose(fp1);

	if (found)
	{
		fptr = fopen(FILE_NAME, "wb");
		fp1 = fopen("temp.bin", "rb");

		while (fread(&visit[no], sizeof(visitor), 1, fp1))
		{
			fwrite(&visit[no], sizeof(visitor), 1, fptr);
		}
		printf("\nModified successfully.\n\n");
		fclose(fptr);
		fclose(fp1);
	}
	else
	{
		printf("\nRecord not founded.\n");
	}
	fclose(fptr);

}

/* *********************************Delete Record**********************************/
void visitor_delete() {
	visitor v1;
	int found = 0;
	char name[SPACE];
	FILE* fptr = fopen(FILE_NAME, "rb");
	FILE* fp1 = fopen("temp.bin", "wb");
	if (fptr == NULL || fp1 == NULL)
	{
		printf("File cant be opened.\n");
		exit(-1);
	}

	printf("%26s\n", "Delete Record");
	printf("+-------------------------------------------+\n");
	printf("Enter the visitor >>NAME<< to delete > ");
	rewind(stdin);
	scanf("%[^\n]", name);

	while (fread(&v1, sizeof(visitor), 1, fptr))
	{
		if (strcmp(v1.name, strupr(name)) == 0)
		{
			found = 1;
			printf("-------------------------------\n");
			printf("Name          :%s\n", v1.name);
			printf("IC            :%s\n", v1.ic);
			printf("Phone Number  :%s\n", v1.phoneNo);
			printf("Occupation    :%s\n", v1.category);
			printf("Visited Place :%s\n", v1.visitedPlace);
			printf("Temperature   :%.1fC\n\n", v1.temp);
		}
		else
			fwrite(&v1, sizeof(visitor), 1, fp1);
	}
	fclose(fptr);
	fclose(fp1);

	if (found)
	{
		fptr = fopen(FILE_NAME, "wb");
		fp1 = fopen("temp.bin", "rb");

		while (fread(&v1, sizeof(visitor), 1, fp1))
		{
			fwrite(&v1, sizeof(visitor), 1, fptr);
		}
		printf("\nDelete successfully.\n");
		fclose(fptr);
		fclose(fp1);
	}
	else
	{
		printf("\nRecord not founded.\n");
	}
	fclose(fptr);
}

/* *********************************Report**********************************/
void visitor_report() {
	visitor v1[SPACE];
	int numV = 0;
	int i = 0;
	int counter = 0;
	FILE* fptr = fopen(FILE_NAME, "rb");
	if (fptr == NULL)
	{
		printf("File cant be opened.\n");
		exit(-1);
	}

	printf("\n");
	printf("\t+------------------------------------------------------------------------+\n");
	printf("\t|                     Visitor Information Report                         |\n");
	printf("\t|------------------------------------------------------------------------|\n");
	printf("\t|       Name           |      Temperature    |      Risk Level           |\n");
	printf("\t|------------------------------------------------------------------------|\n");

	while (fread(&v1, sizeof(visitor), 1, fptr) != 0)
	{
		numV++;
		if (v1[i].temp > 37)
		{
			strcpy(v1[i].riskLvl, "High");
			counter++;
		}
		else
		{
			strcpy(v1[i].riskLvl, "Low");
		}
		printf("\t|%-18s%4s|       %.1fC\t%5s|\t%-6s\t\t%9s|\n", v1[i].name, " ", v1[i].temp, " ", v1[i].riskLvl, " ");
		printf("\t|------------------------------------------------------------------------|\n");
	}

	printf("\nTotal : %d High risk visitors.\n", counter);

	fclose(fptr);
}

/* *********************************Menu**********************************/
int subVisitorMenu() {
	int choice;
	printf("\n\n");
	printf("\t===================================================================================\n");
	printf("\t=                                                                                 =\n");
	printf("\t=                        Visitor Information Selection                            =\n");
	printf("\t=                                                                                 =\n");
	printf("\t===================================================================================\n");
	printf("\t=                                                                                 =\n");
	printf("\t=                          1. Add Records                                         =\n");
	printf("\t=                          2. Search Records                                      =\n");
	printf("\t=                          3. Modify Records                                      =\n");
	printf("\t=                          4. Display Records                                     =\n");
	printf("\t=                          5. Delete Records                                      =\n");
	printf("\t=                          6. Reports                                             =\n");
	printf("\t=                          0. Exit                                                =\n");
	printf("\t=                                                                                 =\n");
	printf("\t===================================================================================\n");
	printf("\t=                                                                                 =\n");
	printf("\t=                          Enter your choice from menu                            =\n");
	printf("\t=                                                                                 =\n");
	printf("\t===================================================================================\n");
	printf("\n\t\t\t\t\t   Here > ");
	scanf("%d", &choice);
	rewind(stdin);
	system("cls");
	return choice;
}

void visitorInformation() {
	int vstChoice = 1;
	while (vstChoice != 0)
	{
		vstChoice = subVisitorMenu();
		switch (vstChoice)
		{
		case 1:
			getLogAct("Add Visitor Information Record");
			visitor_add();
			break;
		case 2:
			getLogAct("Search Visitor Information Record");
			visitor_search();
			break;
		case 3:
			getLogAct("Modify Visitor Information Record");
			visitor_modify();
			break;
		case 4:
			getLogAct("View Visitor Information Record");
			visitor_display();
			break;
		case 5:
			getLogAct("Delete Visitor Information Record");
			visitor_delete();
			break;
		case 6:
			getLogAct("View Visitor Information Report");
			visitor_report();
			break;
		case 0:
			endModule();
			break;
		default:
			printf("Invalid selection. Please TRY again.\n");
			break;
		}
		rewind(stdin);
		system("pause");
		system("cls");
	}
}