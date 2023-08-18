/*Goon Chin Yi*/
#include "Header.h"

typedef struct {
	char venueId[51];
	char venueCategory[51];
	char description[51];
	int maxNoVisitor;
	int currentVisitor;
	Time lSanitization;
}Venue;

Venue venueInfo[30];
int venueInfocount = 0;

void venueInformation() {

	int choice = 0;

	readVenueInfo();

	do {
		choice = subVenueMenu();
		switch (choice)
		{
		case 1:
			getLogAct("Add Venue Information Record");
			addVenueInfo();
			break;
		case 2:
			getLogAct("Search Venue Information Record");
			searchVenueInfo();
			break;
		case 3:
			getLogAct("Modify Venue Information Record");
			modifyVenueInfo();
			break;
		case 4:
			getLogAct("View Venue Information Record");
			displayVenueInfo();
			break;
		case 5:
			getLogAct("Delete Venue Information Record");
			deleteVenueInfo();
			break;
		case 6:
			getLogAct("View Venue Information Report");
			reportVenueInfo();
			break;
		case 0:
			writeVenueInfo();
			endModule();
			break;
		default: printf("\nInvalid choice. Please re-enter.");
		}
		rewind(stdin);

		system("pause");
		system("cls");
	} while (choice != 0);
}

int subVenueMenu()
{
	int choice = 0;
	printf("\n\n");
	printf("\t===================================================================================\n");
	printf("\t=                                                                                 =\n");
	printf("\t=                            Venue Information Selection                          =\n");
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

void readVenueInfo() {
	FILE* fp;

	fp = fopen("VenueInformation.txt", "r");
	int i = 0;

	if (fp == NULL) {
		printf("Cannot open the file.");
		exit(-1);
	}

	while (fscanf(fp, "%[^\|]|%[^\|]|%[^\|]|%d|%d|%d/%d/%d|\n", venueInfo[i].venueId, venueInfo[i].venueCategory, venueInfo[i].description,
		&venueInfo[i].maxNoVisitor, &venueInfo[i].currentVisitor, &venueInfo[i].lSanitization.day, &venueInfo[i].lSanitization.month,
		&venueInfo[i].lSanitization.year) != EOF) {
		i++;
		venueInfocount++;
	}
	fclose(fp);
}

void addVenueInfo() {
	int i = 10;
	char option = 'Y';
	printf("\n");
	do {
		printf("------------------------Add Venue Information------------------------\n");
		printf("Enter venue id : ");
		scanf("%s", venueInfo[i].venueId);
		rewind(stdin);
		printf("Enter venue category : ");
		scanf("%[^\n]", venueInfo[i].venueCategory);
		rewind(stdin);
		printf("Enter description of the venue : ");
		scanf("%[^\n]", venueInfo[i].description);
		rewind(stdin);
		printf("Enter the maximum number of visitors : ");
		scanf("%d", &venueInfo[i].maxNoVisitor);
		rewind(stdin);
		printf("Enter the current number of visitors : ");
		scanf("%d", &venueInfo[i].currentVisitor);
		rewind(stdin);
		printf("Last Sanitization Date (dd/mm/yyyy): ");
		scanf("%d/%d/%d", &venueInfo[i].lSanitization.day, &venueInfo[i].lSanitization.month, &venueInfo[i].lSanitization.year);
		rewind(stdin);
		venueInfocount++;
		i++;
		printf("\n");
		printf("Do you want to add more information ? ");
		scanf("%c", &option);
		rewind(stdin);
		printf("\n\n");
	} while (toupper(option) == 'Y');
}

void searchVenueInfo() {
	int i, search = 0;
	char vId[10] = "", cont = 'Y';
	printf("\n");
	printf("------------------Search Venue Information------------------\n");
	do {
		printf("Enter the venue ID that want to search :");
		scanf("%s", vId);
		rewind(stdin);

		for (i = 0; i < venueInfocount; i++) {
			if (strcmp(vId, venueInfo[i].venueId) == 0) {
				printf("Venue ID : %s\n", venueInfo[i].venueId);
				printf("Venue Category : %s\n", venueInfo[i].venueCategory);
				printf("Venue Description : %s\n", venueInfo[i].description);
				printf("Maximum Visitor in the venue : %d\n", venueInfo[i].maxNoVisitor);
				printf("Current Visitor in the venue : %d\n", venueInfo[i].currentVisitor);
				printf("Last Sanitization Date : %d/%d/%d\n", venueInfo[i].lSanitization.day, venueInfo[i].lSanitization.month,
					venueInfo[i].lSanitization.year);
				search = 1;
			}
		}
		if (search == 0)
		{
			printf("\n");
			printf("Unable to search the information based on venue ID\n");
		}
		printf("\n");
		printf("Continue to search ? ");
		scanf("%c", &cont);
		rewind(stdin);
	} while (toupper(cont) == 'Y');
}

void modifyVenueInfo() {
	char vId[10] = "", ans, option, modify = 0;
	int mVisitor, cVisitor;
	int i;
	printf("\n");
	printf("------------------Modify Venue Information------------------\n");
	do {
		printf("Enter the venue ID that want to modify : ");
		scanf("%s", vId);
		rewind(stdin);

		for (i = 0; i < venueInfocount; i++) {
			if (strcmp(vId, venueInfo[i].venueId) == 0) {
				printf("Venue ID : %s\n", venueInfo[i].venueId);
				printf("Venue Category : %s\n", venueInfo[i].venueCategory);
				printf("Venue Description : %s\n", venueInfo[i].description);
				printf("Maximum Visitor in the venue : %d\n", venueInfo[i].maxNoVisitor);
				printf("Current Visitor in the venue : %d\n", venueInfo[i].currentVisitor);
				printf("Last Sanitization Date : %d/%d/%d\n", venueInfo[i].lSanitization.day, venueInfo[i].lSanitization.month,
					venueInfo[i].lSanitization.year);
				printf("\n");

				printf("Venue Category : ");
				scanf("%[^\n]", venueInfo[i].venueCategory);
				rewind(stdin);
				printf("Venue Description : ");
				scanf("%[^\n]", venueInfo[i].description);
				rewind(stdin);
				printf("Maximum Visitor : ");
				scanf("%d", &mVisitor);
				rewind(stdin);
				printf("Current Visitor : ");
				scanf("%d", &cVisitor);
				rewind(stdin);
				modify = 1;

				printf("Are you sure you want to modify ? ");
				scanf("%c", &option);
				rewind(stdin);
				if (toupper(option) == 'Y') {
					venueInfo[i].maxNoVisitor = mVisitor;
					venueInfo[i].currentVisitor = cVisitor;
					printf("Modify sucesssfully");
				}
				else {
					printf("Unmodify the information\n");
				}
			}
		}
		if (modify == 0) {
			printf("Cannot modify the information");
		}
		printf("\n");
		printf("Continue to modify ? ");
		scanf("%c", &ans);
		rewind(stdin);
	} while (toupper(ans) == 'Y');
}

void displayVenueInfo() {
	int i;
	printf("\n");
	printf("\t========================================================Venue Information======================================================\n");
	printf("\t|Venue Id|   Venue Category\t| Venue Description\t|Maximum Visitor|Current Visitor|    \tLast Sanitization Date\t      |\n");
	printf("\t===============================================================================================================================\n");
	for (i = 0; i < venueInfocount; i++) {
		printf("\t|%s\t |%-10s            | %-16s      |       %d      |       %d      |              %02d/%02d/%4d             |\n", venueInfo[i].venueId, venueInfo[i].venueCategory, venueInfo[i].description,
			venueInfo[i].maxNoVisitor, venueInfo[i].currentVisitor, venueInfo[i].lSanitization.day, venueInfo[i].lSanitization.month,
			venueInfo[i].lSanitization.year);
	}
	printf("\t===============================================================================================================================\n");
}

void deleteVenueInfo() {
	int i, deleted = 0;
	char vId[10] = "", option = 'Y';
	printf("\n");
	do {
		printf("------------------------Delete Venue Information------------------------\n");
		printf("Enter the venue ID that want to delete : ");
		scanf("%s", &vId);
		rewind(stdin);

		for (i = 0; i < venueInfocount; i++) { //find id in array
			if (strcmp(vId, venueInfo[i].venueId) == 0) {
				for (int iOfDel = i; iOfDel < venueInfocount; iOfDel++){ // start to delete from the found array
					venueInfo[iOfDel] = venueInfo[iOfDel + 1];
				}
				printf("\n");
				printf("Information sucessfully deleted\n");
				deleted = 1;
			}
		}
		venueInfocount--;
		if (deleted == 0)
		{
			printf("\n");
			printf("Unable to delete the information\n");
		}
		printf("Continue to delete ? ");
		scanf("%c", &option);
		rewind(stdin);
	} while (toupper(option) == 'Y');
}

void reportVenueInfo() {
	int i;
	printf("\n");
	printf("\t=========================================================Venue Information Report==============================================\n");
	printf("\t|Venue Id|\tVenue Description\t|Maximum Visitor|Current Visitor|    \tLast Sanitization Date\t                      |\n");
	printf("\t===============================================================================================================================\n");
	for (i = 0; i < venueInfocount; i++) {
		printf("\t|%s\t | %-16s             |       %d      |       %d      |              %02d/%02d/%4d                             |\n", venueInfo[i].venueId, venueInfo[i].description,
			venueInfo[i].maxNoVisitor, venueInfo[i].currentVisitor, venueInfo[i].lSanitization.day, venueInfo[i].lSanitization.month,
			venueInfo[i].lSanitization.year);

	}
	printf("\t===============================================================================================================================\n");
}

void writeVenueInfo() {
	FILE* fp2;
	fp2 = fopen("VenueInformation.txt", "w");

	int i;
	if (fp2 == NULL) {
		printf("Cannot open the file.");
		exit(-1);
	}

	for (i = 0; i < venueInfocount; i++) {
		fprintf(fp2, "%s", venueInfo[i].venueId);
		fprintf(fp2, "|");
		fprintf(fp2, "%s", venueInfo[i].venueCategory);
		fprintf(fp2, "|");
		fprintf(fp2, "%s", venueInfo[i].description);
		fprintf(fp2, "|");
		fprintf(fp2, "%d", venueInfo[i].maxNoVisitor);
		fprintf(fp2, "|");
		fprintf(fp2, "%d", venueInfo[i].currentVisitor);
		fprintf(fp2, "|");
		fprintf(fp2, "%d/", venueInfo[i].lSanitization.day);
		fprintf(fp2, "%d/", venueInfo[i].lSanitization.month);
		fprintf(fp2, "%d", venueInfo[i].lSanitization.year);
		fprintf(fp2, "|");
		fprintf(fp2, "\n");
	}
	fclose(fp2);
}