/*By Tan Lin Yi*/
#include "Header.h"

typedef struct
{
	Private visitor;
	char venueId[51];
	double temperature;
	Time date;
	Time exitTime;
	Time enterTime;
}VenueVisited;

int vencount = 0;
VenueVisited venue[100] = { "" };

void venueVisited()
{
	int choice = 1;

	venueVisitedReadFile();

	while (choice != 0)
	{
		choice = subVenueVisitedMenu();
		switch (choice)
		{
		case 1:
			getLogAct("Add Venue Visited Record");
			venueVisitedAddRecords();
			break;
		case 2:
			getLogAct("Search Venue Visited Record");
			venueVisitedSearchRecords();
			break;
		case 3:
			getLogAct("Modify Venue Visited Record");
			venueVisitedModifyRecords();
			break;
		case 4:
			getLogAct("View Venue Visited Record");
			venueVisitedDisplayRecords();
			break;
		case 5:
			getLogAct("Delete Venue Visited Record");
			venueVisitedDeleteRecords();
			break;
		case 6:
			getLogAct("View Venue Visited Report");
			venueVistedReports();
			break;
		case 0:
			endModule();
			break;
		default: printf("Invalid choice.\n\n");
		}
		rewind(stdin);

		venueVisitedWriteFile();

		system("pause");
		system("cls");
	}
}

int subVenueVisitedMenu()
{
	int choice;
	printf("\n\n");
	printf("\t===================================================================================\n");
	printf("\t=                                                                                 =\n");
	printf("\t=                            Venue  Visited  Selection                            =\n");
	printf("\t=                                                                                 =\n");
	printf("\t===================================================================================\n");
	printf("\t=                                                                                 =\n");
	printf("\t=                          1. Add Records                                         =\n");
	printf("\t=                          2. Search Records                                      =\n");
	printf("\t=                          3. Modify Records                                      =\n");
	printf("\t=                          4. Display Records                                     =\n");
	printf("\t=                          5. Delete  Records                                     =\n");
	printf("\t=                          6. Report                                              =\n");
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

void venueVisitedReadFile() {
	FILE* fp1;
	int i = 0;

	fp1 = fopen("VenueVisitedRecords.txt", "r");

	if (fp1 == NULL)
	{
		printf("File cannot open.\n");
		exit(-1);
	}

	while (fscanf(fp1, "%[^\|]|%[^\|]|%[^\|]|%lf|%d/%d/%d|%d:%d|%d:%d|%[^\n]\n", &venue[i].visitor.name, &venue[i].visitor.icNo, &venue[i].visitor.phoneNum,
		&venue[i].temperature, &venue[i].date.day, &venue[i].date.month, &venue[i].date.year,
		&venue[i].enterTime.hrs, &venue[i].enterTime.mins, &venue[i].exitTime.hrs, &venue[i].exitTime.mins, &venue[i].venueId) != EOF) {
		i++;
		vencount++;
	}

	fclose(fp1);
}

void venueVisitedWriteFile() {

	FILE* fp2;

	fp2 = fopen("VenueVisitedRecords.txt", "w");

	if (fp2 == NULL)
	{
		printf("File cannot open.\n");
		exit(-1);
	}

	for (int i = 0; i < vencount; i++) {
		fprintf(fp2, "%s|%s|%s|%.1f|%d/%d/%d|%d:%d|%d:%d|%s\n", venue[i].visitor.name, venue[i].visitor.icNo, venue[i].visitor.phoneNum,
			venue[i].temperature, venue[i].date.day, venue[i].date.month, venue[i].date.year,
			venue[i].enterTime.hrs, venue[i].enterTime.mins, venue[i].exitTime.hrs, venue[i].exitTime.mins, venue[i].venueId);
	}
	rewind(stdin);
	fclose(fp2);
}

void venueVisitedAddRecords() {
	char option = 0;

	int venueVisitedValidateDate = 0, venueVisitedValidateTime = 0, venueVisitedValidatePhoneNum = 0, venueVisitedValidateIcNo = 0;
	double venueVisitedValidateTemperature = 0;

	do
	{
		printf("\t===============Add Venue Visited Records===============\n\n");


		printf("\n\tEnter Visitor Name :");
		scanf("%[^\n]", &venue[vencount].visitor.name);
		rewind(stdin);

		do {
			printf("\n\tEnter Visitor IC Number : ");
			scanf("%s", &venue[vencount].visitor.icNo);
			rewind(stdin);

			venueVisitedValidateIcNo = venueVisitedValidIcNo(venue[vencount].visitor.icNo);

		} while (venueVisitedValidateIcNo == 1);

		do
		{
			printf("\n\tEnter Visitor Phone Number [xxxxxxxxxx 10 digit] : ");
			scanf("%s", &venue[vencount].visitor.phoneNum);
			rewind(stdin);

			venueVisitedValidatePhoneNum = venueVisitedValidPhoneNum(venue[vencount].visitor.phoneNum);

		} while (venueVisitedValidatePhoneNum == 1);


		do {

			printf("\n\tEnter Visitor Temperature [xx:x] : ");
			scanf("%lf", &venue[vencount].temperature);
			rewind(stdin);

			//Function call to validate 
			venueVisitedValidTemperature(venue[vencount].temperature, &venueVisitedValidateTemperature);

			if (venueVisitedValidateTemperature == 1)
			{
				printf("\n");
			}

		} while (venueVisitedValidateTemperature == 1);

		do
		{
			printf("\n\tDate (dd/mm/yyyy): ");
			scanf("%d/%d/%d", &venue[vencount].date.day, &venue[vencount].date.month, &venue[vencount].date.year);
			rewind(stdin);

			//Function call to validate 
			venueVisitedValidDate(venue[vencount].date.day, venue[vencount].date.month, venue[vencount].date.year, &venueVisitedValidateDate);

			if (venueVisitedValidateDate == 1)
			{
				printf("\n\tDate is invalid. Please re-enter!!!\n");
				printf("\n");
			}

		} while (venueVisitedValidateDate == 1);

		do
		{
			printf("\n\tEnter The Visitor Enter Time  (hh:mm in 24 hours form): ");
			scanf("%d:%d", &venue[vencount].enterTime.hrs, &venue[vencount].enterTime.mins);
			rewind(stdin);

			//Function call to validate
			venueVisitedValidTime(venue[vencount].enterTime.hrs, venue[vencount].enterTime.mins, &venueVisitedValidateTime);
			if (venueVisitedValidateTime == 1)
			{
				printf("\n\tInvalid Time. Please Re-enter again!!!\n");
				printf("\n");
			}

		} while (venueVisitedValidateTime == 1);


		do
		{
			printf("\n\tEnter The Visitor Exit Time   (hh:mm in 24 hours form): ");
			scanf("%d:%d", &venue[vencount].exitTime.hrs, &venue[vencount].exitTime.mins);
			rewind(stdin);


			//Function call to validate 

			venueVisitedValidTime(venue[vencount].exitTime.hrs, venue[vencount].exitTime.mins, &venueVisitedValidateTime);

			if (venueVisitedValidateTime == 1)
			{
				printf("\n\tInvalid Time. Please Re-enter again!!!\n");
				printf("\n");
			}
		} while (venueVisitedValidateTime == 1);

		printf("\n\tEnter Venue ID :");
		scanf("%s", &venue[vencount].venueId);
		rewind(stdin);

		printf("\n\tDo you wish to continue add record ( Y = Yes or N = No):");
		scanf("%c", &option);
		rewind(stdin);
		printf("\n");
		vencount++;

	} while (toupper(option) == 'Y');

}

void venueVisitedSearchRecords() {
	int i = 0;
	char venueID[51] = "";
	char option;

	do
	{
		int search = 0;
		printf("\t===============Search for Venue Visited Records===============\n\n");
		printf("\tEnter Venue ID to search :");
		scanf("%s", venueID);
		rewind(stdin);


		for (i = 0; i < vencount; i++)
		{
			if (strcmp(venueID, venue[i].venueId) == 0) {
				search = 1;
				printf("\n\tRecord Found\n");
				printf("\t============\n");
				printf("\tVisitor Name                : %s\n", venue[i].visitor.name);
				printf("\tVisitor IC Number           : %s\n", venue[i].visitor.icNo);
				printf("\tVisitor Phone Number        : %s\n", venue[i].visitor.phoneNum);
				printf("\tVisitor Temperature         : %.1f\n", venue[i].temperature);
				printf("\tDate                        : %02d/%02d/%4d\n", venue[i].date.day, venue[i].date.month, venue[i].date.year);
				printf("\tEnter Time                  : %02d:%02d\n", venue[i].enterTime.hrs, venue[i].enterTime.mins);
				printf("\tExit Time                   : %02d:%02d\n", venue[i].exitTime.hrs, venue[i].exitTime.mins);
			}
		}

		if (search == 0) {
			printf("\n\t----------No record found----------\n");
		}

		printf("\n\tDo you wish to continue search record ( Y = Yes or N = No):");
		scanf("%c", &option);
		rewind(stdin);
		printf("\n\n");

	} while (toupper(option) == 'Y');
}

void venueVisitedModifyRecords() {
	char option;
	char visitorIc[13] = "";

	int venueVisitedValidateDate = 0, venueVisitedValidateTime = 0, venueVisitedValidatePhoneNum = 0, venueVisitedValidateIcNo = 0;
	double venueVisitedValidateTemperature = 0;

	int i = 0;

	do
	{
		int search = 0;

		printf("\t============Venue Visited Modify Records=============\n\n");
		printf("\tEnter Visitor IC Number to be modified: ");
		scanf("%s", visitorIc);
		rewind(stdin);
		printf("\n");

		for (i = 0; i < vencount; i++)
		{
			if (strcmp(visitorIc, venue[i].visitor.icNo) == 0) {
				search = 1;
				printf("\n\tThis Record is You Want To Modified. \n");
				printf("\t============\n");
				printf("\tVisitor Name                : %s\n", venue[i].visitor.name);
				printf("\tVisitor IC Number           : %s\n", venue[i].visitor.icNo);
				printf("\tVisitor Phone Number        : %s\n", venue[i].visitor.phoneNum);
				printf("\tVisitor Temperature         : %.1f\n", venue[i].temperature);
				printf("\tDate                        : %02d/%02d/%4d\n", venue[i].date.day, venue[i].date.month, venue[i].date.year);
				printf("\tEnter Time                  : %02d:%02d\n", venue[i].enterTime.hrs, venue[i].enterTime.mins);
				printf("\tExit Time                   : %02d:%02d\n", venue[i].exitTime.hrs, venue[i].exitTime.mins);
				printf("\tVenue ID                    : %s\n", venue[i].venueId);
			}
		}
		rewind(stdin);
		printf("\n\n");

		for (i = 0; i < vencount; i++) {

			if (strcmp(visitorIc, venue[i].visitor.icNo) == 0) {
				search = 1;

				printf("\n\tEnter Visitor Name :");
				scanf("%[^\n]", &venue[i].visitor.name);
				rewind(stdin);

				do {
					printf("\n\tEnter Visitor IC Number : ");
					scanf("%s", &venue[i].visitor.icNo);
					rewind(stdin);

					venueVisitedValidateIcNo = venueVisitedValidIcNo(venue[i].visitor.icNo);

				} while (venueVisitedValidateIcNo == 1);

				do
				{
					printf("\n\tEnter Visitor Phone Number [xxxxxxxxxx 10 digit] : ");
					scanf("%s", &venue[i].visitor.phoneNum);
					rewind(stdin);

					venueVisitedValidatePhoneNum = venueVisitedValidPhoneNum(venue[i].visitor.phoneNum);

				} while (venueVisitedValidatePhoneNum == 1);


				do {

					printf("\n\tEnter Visitor Temperature [xx:x] : ");
					scanf("%lf", &venue[i].temperature);
					rewind(stdin);

					//Function call to validate 
					venueVisitedValidTemperature(venue[i].temperature, &venueVisitedValidateTemperature);

					if (venueVisitedValidateTemperature == 1)
					{
						printf("\n");
					}

				} while (venueVisitedValidateTemperature == 1);

				do
				{
					printf("\n\tDate (dd/mm/yyyy): ");
					scanf("%d/%d/%d", &venue[i].date.day, &venue[i].date.month, &venue[i].date.year);
					rewind(stdin);

					//Function call to validate 
					venueVisitedValidDate(venue[i].date.day, venue[i].date.month, venue[i].date.year, &venueVisitedValidateDate);

					if (venueVisitedValidateDate == 1)
					{
						printf("\n\tDate is invalid. Please re-enter!!!\n");
						printf("\n");
					}

				} while (venueVisitedValidateDate == 1);

				do
				{
					printf("\n\tEnter The Visitor Enter Time  (hh:mm in 24 hours form): ");
					scanf("%d:%d", &venue[i].enterTime.hrs, &venue[i].enterTime.mins);
					rewind(stdin);

					//Function call to validate .
					venueVisitedValidTime(venue[i].enterTime.hrs, venue[i].enterTime.mins, &venueVisitedValidateTime);
					if (venueVisitedValidateTime == 1)
					{
						printf("\n\tInvalid Time. Please Re-enter again!!!\n");
						printf("\n");
					}

				} while (venueVisitedValidateTime == 1);


				do
				{
					printf("\n\tEnter The Visitor Exit Time   (hh:mm in 24 hours form): ");
					scanf("%d:%d", &venue[i].exitTime.hrs, &venue[i].exitTime.mins);
					rewind(stdin);


					//Function call to validate 

					venueVisitedValidTime(venue[i].exitTime.hrs, venue[i].exitTime.mins, &venueVisitedValidateTime);

					if (venueVisitedValidateTime == 1)
					{
						printf("\n\tInvalid Time. Please Re-enter again!!!\n");
						printf("\n");
					}
				} while (venueVisitedValidateTime == 1);

				printf("\n\tEnter Venue ID :");
				scanf("%s", &venue[i].venueId);
				rewind(stdin);
			}
		}

		if (search == 0) {
			printf("\t----------No record found----------\n");
		}

		printf("\n\tDo you wish to continue modify record ( Y = Yes or N = No):");
		scanf("%c", &option);
		rewind(stdin);
		printf("\n");

	} while (toupper(option) == 'Y');

}

void venueVisitedDisplayRecords() {

	int i = 0;

	printf("\n\n");
	printf("\t ===========================================================Venue Visited Records=========================================================\n");
	printf("\t|                                     |               |               |             |            |              |             |            |\n");
	printf("\t|               Visitor               |    Visitor    |     Visitor   |   Visitor   |    Date    |   Visitor    |   Visitor   |   Venue    |\n");
	printf("\t|                Name                 |   IC Number   |  Phone Number | Temperature |            |  Enter Time  |  Exit Time  |     ID     |\n");
	printf("\t|                                     |               |               |             |            |              |             |            |\n");
	printf("\t ==========================================================================================================================================\n");

	for (i = 0; i < vencount; i++) {

		printf("\t|                                     |               |               |             |            |              |             |            |\n");
		printf("\t| %-35s | %-13s |   %-11s |    %-8.1f | %02d/%02d/%4d |   %02d  :  %02d  |   %02d :  %02d  |    %-7s | \n", venue[i].visitor.name,
			venue[i].visitor.icNo, venue[i].visitor.phoneNum,
			venue[i].temperature, venue[i].date.day, venue[i].date.month, venue[i].date.year,
			venue[i].enterTime.hrs, venue[i].enterTime.mins, venue[i].exitTime.hrs, venue[i].exitTime.mins, venue[i].venueId);
		printf("\t|                                     |               |               |             |            |              |             |            |\n");
		printf("\t|                                     |               |               |             |            |              |             |            |\n");
		printf("\t ==========================================================================================================================================\n");
	}

}

void venueVistedReports() {
	int i = 0;

	printf("\n\n");
	printf("\t ====================================Venue Visited Reports====================================\n");
	printf("\t|                                     |            |              |             |            |\n");
	printf("\t|               Visitor               |    Date    |   Visitor    |   Visitor   |   Venue    |\n");
	printf("\t|                Name                 |            |  Enter Time  |  Exit Time  |     ID     |\n");
	printf("\t|                                     |            |              |             |            |\n");
	printf("\t ============================================================================================\n");

	for (i = 0; i < vencount; i++) {
		printf("\t|                                     |            |              |             |            |\n");
		printf("\t| %-35s | %02d/%02d/%4d |   %02d  :  %02d  |   %02d :  %02d  |    %-7s | \n", venue[i].visitor.name, venue[i].date.day, venue[i].date.month, venue[i].date.year,
			venue[i].enterTime.hrs, venue[i].enterTime.mins, venue[i].exitTime.hrs, venue[i].exitTime.mins, venue[i].venueId);
		printf("\t|                                     |            |              |             |            |\n");
		printf("\t|                                     |            |              |             |            |\n");
		printf("\t ============================================================================================\n");
	}

}

void venueVisitedDeleteRecords() {
	int i = 0, record = 0;
	char choice = 0;
	char option;
	char visitorIc[13] = "";

	do {
		int search = 0;

		printf("\n");
		printf("\t ====================================Venue Visited  Delete Records====================================\n\n");
		printf("\t Enter the Visitor IC you want to delete  records : ");
		scanf("%s", visitorIc);

		for (i = 0; i < vencount; i++)
		{
			if (strcmp(visitorIc, venue[i].visitor.icNo) == 0) {
				search = 1;
				printf("\n\tThis Record is You Want To Delete. \n");
				printf("\t============\n");
				printf("\tVisitor Name                : %s\n", venue[i].visitor.name);
				printf("\tVisitor IC Number           : %s\n", venue[i].visitor.icNo);
				printf("\tVisitor Phone Number        : %s\n", venue[i].visitor.phoneNum);
				printf("\tVisitor Temperature         : %.1f\n", venue[i].temperature);
				printf("\tDate                        : %02d/%02d/%4d\n", venue[i].date.day, venue[i].date.month, venue[i].date.year);
				printf("\tEnter Time                  : %02d:%02d\n", venue[i].enterTime.hrs, venue[i].enterTime.mins);
				printf("\tExit Time                   : %02d:%02d\n", venue[i].exitTime.hrs, venue[i].exitTime.mins);
				printf("\tVenue ID                    : %s\n", venue[i].venueId);
			}
		}
		rewind(stdin);
		printf("\n\n");

		for (i = 0; i < vencount; i++) {
			if (strcmp(visitorIc, venue[i].visitor.icNo) == 0)
			{
				search = 1;
				record = i;

				printf("\t Are you sure you want to delete this  records ( Y = yes or N = no) : ");
				scanf("%c", &choice);
				rewind(stdin);

				if (toupper(choice) == 'Y') {
					for (i = record; i < vencount; i++)
					{
						venue[i] = venue[i + 1];
					}
					vencount--;
					printf("\n\n");
					printf("\t Record is successfully delete.\n");
				}
				else
				{
					printf("\n\n");
					printf("\t You have undeleted records.\n");
				}

			}

		}

		if (search == 0) {
			printf("\t----------No record found----------\n");
		}

		printf("\n\n");
		printf("\t Do you want to continue delete another record ( Y = yes or N = no):");
		scanf("%c", &option);
		rewind(stdin);
		printf("\n");


	} while (toupper(option) == 'Y');
}

void venueVisitedValidDate(int day, int month, int year, int* venueVisitedValidateDate)
{
	//check the Year
	if (year >= 2020 && year <= 9999)
	{
		//check the Month
		if (month >= 1 && month <= 12)
		{
			//check the Month that have 31 Days.
			if ((day >= 1 && day <= 31) && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12))
			{
				*venueVisitedValidateDate = 0;
			}
			//check the Month that have 30 Days.
			else if ((day >= 1 && day <= 30) && (month == 4 || month == 6 || month == 9 || month == 11))
			{
				*venueVisitedValidateDate = 0;
			}
			//check the February for the Non-Leap Year.
			else if ((day >= 1 && day <= 28) && (month == 2))
			{
				*venueVisitedValidateDate = 0;
			}
			//check the February for the Leap Year.
			else if (day == 29 && month == 2 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)))
			{
				*venueVisitedValidateDate = 0;
			}
			else
			{
				*venueVisitedValidateDate = 1;
			}
		}
		else
		{
			*venueVisitedValidateDate = 1;
		}
	}
	else
	{
		*venueVisitedValidateDate = 1;
	}
}

void venueVisitedValidTime(int hrs, int mins, int* venueVisitedValidateTime)
{
	//check the Time
	if (hrs >= 0 && hrs < 24 && mins >= 0 && mins < 60)
	{
		*venueVisitedValidateTime = 0;
	}
	else
	{
		*venueVisitedValidateTime = 1;

	}
}

int venueVisitedValidPhoneNum(char num[12])
{
	int i = 0, d;
	d = strlen(num);//length of the enter number

	for (i = 0; i < d; i++)
	{
		if (isdigit(num[i]) == 0)
		{
			printf("\n\tInvalid Phone Number. Please Re-enter again!!!\n");
			return 1;
		}
	}

	if (d != 10) {
		printf("\n\tInvalid Phone Number. Please Re-enter again!!!\n");
		return 1;

	}
	return 0;
}

int venueVisitedValidIcNo(char num[13])
{
	int i, d;
	d = strlen(num);

	for (i = 0; i < d; i++)
	{
		if (isdigit(num[i]) == 0)
		{
			printf("\n\tInvalid IC Number. Please Re-enter again!!!\n");
			return 1;
		}
	}

	if (d != 12) {
		printf("\n\tInvalid IC Number. Please Re-enter again!!!\n");
		return 1;

	}
	return 0;
}

void venueVisitedValidTemperature(double temperature, double* temperatures)
{
	if (temperature > 35.8 && temperature < 37)
	{
		*temperatures = 0;
	}
	else
	{
		*temperatures = 1;
		printf("\n\tPlease Re-enter again because temperature is more than 37 will not allow go into school and will not be record. \n ");
	}
}