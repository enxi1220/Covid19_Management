/*By Alvin Chan Ee Aun*/
#include "Header.h"

//Structure for the company details and staff incharge.
typedef struct
{
	char name[40];
	char phoneNum[11];
	char staffName[40];

}Company;

//Nested structure for the overall things.
typedef struct
{
	char venue[40];
	char sazId[10];
	Company company;
	Time date;
	Time startTime;
	Time endTime;

}Sanitization;

Sanitization saz[100];
int sazcount = 0;

void sanitization()
{
	int choice = 1;

	readFile();

	while (choice != 0)
	{
		choice = subSaznitizationMenu();
		switch (choice)
		{
		case 1:
			getLogAct("Add Sanitization Record");
			addRecords();
			break;
		case 2:
			getLogAct("Search Sanitization Record");
			searchRecords();
			break;
		case 3:
			getLogAct("Edit Sanitization Record");
			modifyRecords();
			break;
		case 4:
			getLogAct("View Sanitization Record");
			displayRecords();
			break;
		case 5:
			getLogAct("Delete Sanitization Record");
			deleteRecords();
			break;
		case 6:
			getLogAct("View Sanitization Report");
			report();
			break;
		case 0:
			writeFile();
			endModule();
			break;
		default: printf("\n\tInvalid choice.\n\n");
		}
		rewind(stdin);

		system("pause");
		system("cls");
	}
}

int subSaznitizationMenu()
{
	int choice;

	printf("\n\n");
	printf("\t===================================================================================\n");
	printf("\t=                                                                                 =\n");
	printf("\t=                           Sanitization Records                                  =\n");
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

void readFile()
{
	FILE* fp1;
	fp1 = fopen("SanitizationRecords.txt", "r");

	if (fp1 == NULL)
	{
		printf("File cannot open.\n");
		exit(-1);
	}

	while (fscanf(fp1, "%[^\|]|%d/%d/%d|%d:%d|%d:%d|%[^\|]|%[^\|]|%[^\|]|%[^\n]\n", saz[sazcount].sazId, &saz[sazcount].date.day, &saz[sazcount].date.month, &saz[sazcount].date.year,
		&saz[sazcount].startTime.hrs, &saz[sazcount].startTime.mins, &saz[sazcount].endTime.hrs, &saz[sazcount].endTime.mins,
		saz[sazcount].venue, saz[sazcount].company.name, saz[sazcount].company.phoneNum, saz[sazcount].company.staffName) != EOF) {
		sazcount++;
	}

	fclose(fp1);
}

void writeFile()
{
	FILE* fp2;
	int i = 0;

	fp2 = fopen("SanitizationRecords.txt", "w");

	if (fp2 == NULL)
	{
		printf("File cannot open.\n");
		exit(-1);
	}

	for (i = 0; i < sazcount; i++) {
		fprintf(fp2, "%s|%d/%d/%d|%d:%d|%d:%d|%s|%s|%s|%s\n", saz[i].sazId, saz[i].date.day, saz[i].date.month, saz[i].date.year,
			saz[i].startTime.hrs, saz[i].startTime.mins, saz[i].endTime.hrs, saz[i].endTime.mins,
			saz[i].venue, saz[i].company.name, saz[i].company.phoneNum, saz[i].company.staffName);
		rewind(stdin);
	}

	fclose(fp2);
}

void addRecords()
{
	char option;
	int validateDate = 0, validateTime = 0, validatePhoneNum = 0;
	int i = 0, search;
	GetLocalTime(&autoTime);

	printf("\t\t  ============== Today ==============\n");
	printf("\t\t\t    Date:%d-%d-%d\n", autoTime.wDay, autoTime.wMonth, autoTime.wYear);
	printf("\t\t\t    Time: %02d:%02d:%02d\n\n", autoTime.wHour, autoTime.wMinute, autoTime.wSecond);

	do
	{
		printf("\t=============== Add Sanitization Records ===============\n\n");
		do
		{
			search = 0;

			printf("\tEnter sanitization ID: ");
			scanf("%s", saz[sazcount].sazId);
			rewind(stdin);

			for (i = 0; i < sazcount; i++)
			{
				if (strcmp(saz[sazcount].sazId, saz[i].sazId) == 0) {
					search = 1;
					printf("\n\tThis Sanitization ID already exist.\n\n");
				}
			}

		} while (search == 1);

		do
		{
			printf("\tDate (dd/mm/yyyy): ");
			scanf("%d/%d/%d", &saz[sazcount].date.day, &saz[sazcount].date.month, &saz[sazcount].date.year);
			rewind(stdin);

			//Function call to validate the Date.
			validateDate = validDate(saz[sazcount].date.day, saz[sazcount].date.month, saz[sazcount].date.year);

		} while (validateDate == 1);

		do
		{
			printf("\tEnter the start time of sanitization(HH:MM in 24 hours form): ");
			scanf("%d:%d", &saz[sazcount].startTime.hrs, &saz[sazcount].startTime.mins);
			rewind(stdin);

			//Function call to validate the Start Time.
			validateTime = validTime(saz[sazcount].startTime.hrs, saz[sazcount].startTime.mins);

		} while (validateTime == 1);

		do
		{
			printf("\tEnter the end time of sanitization(HH:MM in 24 hours form): ");
			scanf("%d:%d", &saz[sazcount].endTime.hrs, &saz[sazcount].endTime.mins);
			rewind(stdin);

			//Function call to validate the End Time.
			validateTime = validTime(saz[sazcount].endTime.hrs, saz[sazcount].endTime.mins);

		} while (validateTime == 1);

		do
		{
			printf("\n\tCategories of Venue : LAB801, LAB802, LAB803, LAB804, LAB805\n");
			printf("\tEnter sanitization venue: ");
			scanf("%[^\n]", &saz[sazcount].venue);
			rewind(stdin);

			strcpy(saz[sazcount].venue, strupr(saz[sazcount].venue));

			if (strcmp(saz[sazcount].venue, "LAB801") != 0 && strcmp(saz[sazcount].venue, "LAB802") != 0 && strcmp(saz[sazcount].venue, "LAB803") != 0
				&& strcmp(saz[sazcount].venue, "LAB804") != 0 && strcmp(saz[sazcount].venue, "LAB805") != 0)
			{
				printf("\n\tInvalid venue. PLease re-enter!!!\n");
			}

		} while (strcmp(saz[sazcount].venue, "LAB801") != 0 && strcmp(saz[sazcount].venue, "LAB802") != 0 && strcmp(saz[sazcount].venue, "LAB803") != 0
			&& strcmp(saz[sazcount].venue, "LAB804") != 0 && strcmp(saz[sazcount].venue, "LAB805") != 0);

		printf("\n\tCompany Details\n");
		printf("\t=================\n");
		printf("\tEnter company name: ");
		scanf("%[^\n]", saz[sazcount].company.name);
		rewind(stdin);

		do
		{
			printf("\tEnter company phone number(only 10 digits xxxxxxxxxx): ");
			scanf("%[^\n]", saz[sazcount].company.phoneNum);
			rewind(stdin);

			//Function call to validate Phone Number.
			validatePhoneNum = validPhoneNum(saz[sazcount].company.phoneNum);

		} while (validatePhoneNum == 1);

		printf("\n\tStaff Incharge\n");
		printf("\t==============\n");
		printf("\tEnter staff incharge name: ");
		scanf("%[^\n]", saz[sazcount].company.staffName);
		rewind(stdin);

		printf("\n\tDo you wish to add more record ( Y = Yes / Press any key to quit):");
		scanf("%c", &option);
		rewind(stdin);
		printf("\n\n");

		sazcount++;

	} while (toupper(option) == 'Y');
}

void searchRecords()
{
	int i = 0;
	char sazID[10] = "";
	char option;

	do
	{
		int search = 0;

		printf("\n\t=============== Search for Sanitization Records ===============\n\n");
		printf("\tEnter sanitization ID to search :");
		scanf("%s", sazID);
		rewind(stdin);

		for (i = 0; i < sazcount; i++)
		{
			if (strcmp(sazID, saz[i].sazId) == 0) {
				search = 1;
				printf("\n\tRecord Found\n");
				printf("\t============\n");
				printf("\tSanitization ID      : %s\n", saz[i].sazId);
				printf("\tDate                 : %02d/%02d/%4d\n", saz[i].date.day, saz[i].date.month, saz[i].date.year);
				printf("\tStart Time           : %02d:%02d\n", saz[i].startTime.hrs, saz[i].startTime.mins);
				printf("\tEnd Time             : %02d:%02d\n", saz[i].endTime.hrs, saz[i].endTime.mins);
				printf("\tSanitization Venue   : %s\n", saz[i].venue);
				printf("\tCompany Name         : %s\n", saz[i].company.name);
				printf("\tCompany Phone Number : %s\n", saz[i].company.phoneNum);
				printf("\tStaff Incharge Name  : %s\n", saz[i].company.staffName);
			}
		}

		if (search == 0) {
			printf("\n\t----------No record found----------\n");
		}

		printf("\n\tDo you wish to continue search record ( Y = Yes / Press any key to quit):");
		scanf("%c", &option);
		rewind(stdin);
		printf("\n\n");

	} while (toupper(option) == 'Y');
}

void modifyRecords()
{
	char option, choice;
	char sazID[10] = "";
	int i = 0, choose = 0;
	int validateDate = 0, validateTime = 0, validatePhoneNum = 0;

	do
	{
		int search = 0;

		printf("\n\t=============== Modify Records ===============\n\n");
		printf("\tEnter sanitization ID to be modified: ");
		scanf("%s", sazID);
		rewind(stdin);
		printf("\n");

		for (i = 0; i < sazcount; i++) {

			if (strcmp(sazID, saz[i].sazId) == 0) {
				search = 1;

				printf("\tRecord Found\n");
				printf("\t============\n");
				printf("\tSanitization ID      : %s\n", saz[i].sazId);
				printf("\tDate                 : %02d/%02d/%4d\n", saz[i].date.day, saz[i].date.month, saz[i].date.year);
				printf("\tStart Time           : %02d:%02d\n", saz[i].startTime.hrs, saz[i].startTime.mins);
				printf("\tEnd Time             : %02d:%02d\n", saz[i].endTime.hrs, saz[i].endTime.mins);
				printf("\tSanitization Venue   : %s\n", saz[i].venue);
				printf("\tCompany Name         : %s\n", saz[i].company.name);
				printf("\tCompany Phone Number : %s\n", saz[i].company.phoneNum);
				printf("\tStaff Incharge Name  : %s\n", saz[i].company.staffName);
				printf("\n");

				do
				{
					do
					{
						printf("\tSelection for data to modify\n");
						printf("\t============================\n");
						printf("\t1. Date               2. Start Time and End Time    3. Sanitization Venue\n");
						printf("\t4. Company Details    5. Staff Incharge Name\n\n");
						printf("\tChoose which data to modify :");
						scanf("%d", &choose);
						rewind(stdin);

						if (choose == 1) {
							do
							{
								printf("\n\tDate (dd/mm/yyyy): ");
								scanf("%d/%d/%d", &saz[i].date.day, &saz[i].date.month, &saz[i].date.year);
								rewind(stdin);

								//Function call to validate the Date.
								validateDate = validDate(saz[i].date.day, saz[i].date.month, saz[i].date.year);

							} while (validateDate == 1);
						}
						else if (choose == 2) {
							do
							{
								printf("\n\tEnter the start time of sanitization(HH:MM in 24 hours form): ");
								scanf("%d:%d", &saz[i].startTime.hrs, &saz[i].startTime.mins);
								rewind(stdin);

								//Function call to validate the Start Time.
								validateTime = validTime(saz[i].startTime.hrs, saz[i].startTime.mins);

							} while (validateTime == 1);

							do
							{
								printf("\tEnter the end time of sanitization(HH:MM in 24 hours form): ");
								scanf("%d:%d", &saz[i].endTime.hrs, &saz[i].endTime.mins);
								rewind(stdin);

								//Function call to validate the End Time.
								validateTime = validTime(saz[i].endTime.hrs, saz[i].endTime.mins);

							} while (validateTime == 1);
						}
						else if (choose == 3) {
							do
							{
								printf("\n\tCategories of Venue : LAB801, LAB802, LAB803, LAB804, LAB805\n");
								printf("\tEnter sanitization venue: ");
								scanf("%[^\n]", &saz[i].venue);
								rewind(stdin);

								strcpy(saz[i].venue, strupr(saz[i].venue));

								if (strcmp(saz[i].venue, "LAB801") != 0 && strcmp(saz[i].venue, "LAB802") != 0 && strcmp(saz[i].venue, "LAB803") != 0
									&& strcmp(saz[i].venue, "LAB804") != 0 && strcmp(saz[i].venue, "LAB805") != 0)
								{
									printf("\n\tInvalid venue. PLease re-enter!!!\n");
								}

							} while (strcmp(saz[i].venue, "LAB801") != 0 && strcmp(saz[i].venue, "LAB802") != 0 && strcmp(saz[i].venue, "LAB803") != 0
								&& strcmp(saz[i].venue, "LAB804") != 0 && strcmp(saz[i].venue, "LAB805") != 0);
						}
						else if (choose == 4) {
							printf("\n\tCompany Details\n");
							printf("\t=================\n");
							printf("\tEnter company name: ");
							scanf("%[^\n]", saz[i].company.name);
							rewind(stdin);

							do
							{
								printf("\tEnter company phone number(only 10 digits xxxxxxxxxx): ");
								scanf("%[^\n]", saz[i].company.phoneNum);
								rewind(stdin);

								//Function call to validate Phone Number.
								validatePhoneNum = validPhoneNum(saz[i].company.phoneNum);

							} while (validatePhoneNum == 1);
						}
						else if (choose == 5) {
							printf("\t==============\n");
							printf("\tEnter staff incharge name: ");
							scanf("%[^\n]", saz[i].company.staffName);
							rewind(stdin);
						}
						else
						{
							printf("\n\tInvalid choice. Please re-enter!!!\n\n");
						}

					} while (choose != 1 && choose != 2 && choose != 3 && choose != 4 && choose != 5);

					printf("\n\tDo you wish to continue modify THIS record ( Y = Yes / Press any key to quit):");
					scanf("%c", &choice);
					rewind(stdin);
					printf("\n");

				} while (toupper(choice) == 'Y');
			}
		}

		if (search == 0) {
			printf("\t----------No record found----------\n");
		}

		printf("\n\tDo you wish to continue modify record ( Y = Yes / Press any key to quit):");
		scanf("%c", &option);
		rewind(stdin);
		printf("\n");

	} while (toupper(option) == 'Y');
}

void displayRecords()
{
	int i = 0;

	printf("\n\n");
	printf("\t========================================================================= Sanitization Records =============================================================================\n");
	printf("\t|  Sanitization ID   |    Date    |  Start Time  |  End Time |         Venue        |        Company Name       |  Company Phone Number  |       Staff Incharge Name       |\n");
	printf("\t============================================================================================================================================================================\n");

	for (i = 0; i < sazcount; i++) {

		printf("\t|        %s        | %02d/%02d/%4d |    %02d:%02d     |   %02d:%02d   |  %-20s|  %-25s|     %12s       |   %-30s|\n", saz[i].sazId, saz[i].date.day, saz[i].date.month, saz[i].date.year,
			saz[i].startTime.hrs, saz[i].startTime.mins, saz[i].endTime.hrs, saz[i].endTime.mins,
			saz[i].venue, saz[i].company.name, saz[i].company.phoneNum, saz[i].company.staffName);
		printf("\t============================================================================================================================================================================\n");
	}
	printf("\n\tTotal of records : %d\n\n", sazcount);
}

void deleteRecords()
{
	int i = 0, record = 0;
	char option, choice;
	char sazID[10] = "";

	do
	{
		int search = 0;

		printf("\n\t================== Delete Records ==================\n\n");
		printf("\tEnter the sanitization ID to delete the record: ");
		scanf("%s", sazID);
		rewind(stdin);

		for (i = 0; i < sazcount; i++)
		{
			if (strcmp(sazID, saz[i].sazId) == 0) {
				search = 1;
				record = i;

				printf("\n\tRecord Found\n");
				printf("\t============\n");
				printf("\tSanitization ID      : %s\n", saz[i].sazId);
				printf("\tDate                 : %02d/%02d/%4d\n", saz[i].date.day, saz[i].date.month, saz[i].date.year);
				printf("\tStart Time           : %02d:%02d\n", saz[i].startTime.hrs, saz[i].startTime.mins);
				printf("\tEnd Time             : %02d:%02d\n", saz[i].endTime.hrs, saz[i].endTime.mins);
				printf("\tSanitization Venue   : %s\n", saz[i].venue);
				printf("\tCompany Name         : %s\n", saz[i].company.name);
				printf("\tCompany Phone Number : %s\n", saz[i].company.phoneNum);
				printf("\tStaff Incharge Name  : %s\n", saz[i].company.staffName);
				printf("\n");

				printf("\n\tAre you sure to delete this record ( Y = Yes or Any key = No):");
				scanf("%c", &choice);
				rewind(stdin);

				if (toupper(choice) == 'Y')
				{
					sazcount -= 1;

					for (i = record; i < sazcount; i++)
					{
						saz[i] = saz[i + 1];
					}
					printf("\n\tRecord is successfully deleted.\n");
				}
				else
				{
					printf("\n\tThe record has not been deleted.\n");
				}
			}
		}

		if (search == 0) {
			printf("\n\t----------No record found----------\n");
		}

		printf("\n\tDo you wish to continue delete record ( Y = Yes or / Press any key to quit):");
		scanf("%c", &option);
		rewind(stdin);
		printf("\n");

	} while (toupper(option) == 'Y');
}

void report()
{
	int i = 0;
	int lab1 = 0, lab2 = 0, lab3 = 0, lab4 = 0, lab5 = 0, total = 0;

	for (i = 0; i < sazcount; i++) {
		if (strcmp(saz[i].venue, "LAB801") == 0)
		{
			lab1++;
		}
	}
	for (i = 0; i < sazcount; i++) {
		if (strcmp(saz[i].venue, "LAB802") == 0)
		{
			lab2++;
		}
	}
	for (i = 0; i < sazcount; i++) {
		if (strcmp(saz[i].venue, "LAB803") == 0)
		{
			lab3++;
		}
	}
	for (i = 0; i < sazcount; i++) {
		if (strcmp(saz[i].venue, "LAB804") == 0)
		{
			lab4++;
		}
	}
	for (i = 0; i < sazcount; i++) {
		if (strcmp(saz[i].venue, "LAB805") == 0)
		{
			lab5++;
		}
	}
	printf("\t-------------------------------------------------------\n");
	printf("\t|            Venue Saznitization Report               |\n");
	printf("\t|-----------------------------------------------------|\n");
	printf("\t|        Venue       | Number of sanitization records |\n");
	printf("\t|-----------------------------------------------------|\n");
	printf("\t|        LAB801      |               %2d               |\n", lab1);
	printf("\t|        LAB802      |               %2d               |\n", lab2);
	printf("\t|        LAB803      |               %2d               |\n", lab3);
	printf("\t|        LAB804      |               %2d               |\n", lab4);
	printf("\t|        LAB805      |               %2d               |\n", lab5);
	printf("\t-------------------------------------------------------\n");

	total = lab1 + lab2 + lab3 + lab4 + lab5;

	printf("\n\tTotal number of sanitization records for the venue: %d\n\n", total);
}

int validDate(int day, int month, int year)
{
	int validateDate = 0;

	if (year >= 2018 && year <= 2025)
	{
		//check the Month
		if (month >= 1 && month <= 12)
		{
			//check the Month that have 31 Days.
			if ((day >= 1 && day <= 31) && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12))
			{
				validateDate = 0;
			}
			//check the Month that have 30 Days.
			else if ((day >= 1 && day <= 30) && (month == 4 || month == 6 || month == 9 || month == 11))
			{
				validateDate = 0;
			}
			//check the February for the Non-Leap Year.
			else if ((day >= 1 && day <= 28) && (month == 2))
			{
				validateDate = 0;
			}
			//check the February for the Leap Year.
			else if (day == 29 && month == 2 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)))
			{
				validateDate = 0;
			}
			else
			{
				validateDate = 1;
				printf("\n\tDay is invalid. Please re-enter!!!\n\n");
			}
		}
		else
		{
			validateDate = 1;
			printf("\n\tMonth is invalid. Please re-enter!!!\n\n");
		}
	}
	else
	{
		validateDate = 1;
		printf("\n\tYear is invalid. Please re-enter!!!\n\n");
	}
	return validateDate;
}

int validTime(int hour, int min)
{
	int validateTime = 0;

	//check the Time
	if (hour >= 0 && hour < 24 && min >= 0 && min < 60)
	{
		validateTime = 0;
	}
	else
	{
		validateTime = 1;
		printf("\n\tInvalid Time. Please Re-enter again!!!\n\n");
	}

	return validateTime;
}

int validPhoneNum(char num[11])
{
	int i = 0, a;
	a = strlen(num);

	for (i = 0; i < a; i++)
	{
		if (isdigit(num[i]) == 0)
		{
			printf("\n\tInvalid Phone Number. Please Re-enter again!!!\n\n");
			return 1;
		}
		if (a != 10) {
			printf("\n\tMust 10 digits number. Please Re-enter again!!!\n\n");
			return 1;
		}
	}
	return 0;
}