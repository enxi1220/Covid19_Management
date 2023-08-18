/*By Lim En Xi*/
#include "Header.h"

typedef struct
{
	Private privacy;
	char id[5];
	char faculty[5];
	char position[40];
	char activity[40];//display the last module visited
	Time time;
}Staff;

Staff staff[999] = { "" };
int staffCount = 0;

Staff loginStaff[999] = { "" };//display all actvities performed by staff
int loginCount = 0;

void adminStaff()
{
	int choice = 1;
	while (choice != 0)
	{
		choice = subAdminMenu();
		switch (choice)
		{
		case 1:
			getLogAct("Add Admin Record");
			loopAddAdmin();
			break;
		case 2:
			getLogAct("Search Admin Record");
			loopSearchAdmin();
			break;
		case 3:
			getLogAct("Edit Admin Record");
			loopEditAdmin();
			break;
		case 4:
			getLogAct("View Admin Record");
			displayAdmin();
			break;
		case 5:
			getLogAct("Delete Admin Record");
			loopDeleteAdmin();
			break;
		case 6:
			getLogAct("View Admin Perform Report");
			displayLogActReport();
			break;
		case 0:
			endModule();
			system("pause");
			break;
		default:
			printf("\n\n\t\tPlease Enter Number 0-6!\n\n ");
			system("pause");
		}
		system("cls");
	}
}

void checkAdminFile(FILE* fp)
{
	if (fp == NULL)
	{
		printf(" Unable to Open the File!\n");
		exit(-1);
	}
}

void readAdminFromBin()
{
	FILE* fp;
	fp = fopen("Administrative Staff.bin", "rb");
	checkAdminFile(fp);
	while (fread(&staff[998], sizeof(Staff), 1, fp) != 0)
	{
		staff[staffCount] = staff[998];
		staffCount++;
	}
	fclose(fp);
}

void writeAdminToBin()
{
	FILE* fp;
	fp = fopen("Administrative Staff.bin", "wb");
	fwrite(&staff, sizeof(Staff), staffCount, fp);
	fclose(fp);
}

void readLoginFromBin()
{
	FILE* fp;
	fp = fopen("Admin Login.bin", "rb");
	checkAdminFile(fp);
	while (fread(&loginStaff[998], sizeof(Staff), 1, fp) != 0)
	{
		loginStaff[loginCount] = loginStaff[998];
		loginCount++;
	}
	fclose(fp);
}

void writeLoginToBin()
{
	FILE* fp;
	fp = fopen("Admin Login.bin", "wb");
	fwrite(&loginStaff, sizeof(Staff), loginCount, fp);
	fclose(fp);
}

//for auto-generated id, save in individual file, to ensure no repeated ID occur
int readAdminIdCountFromTxt()
{
	FILE* fp;
	int count;
	fp = fopen("Admin Counter.txt", "r");
	checkAdminFile(fp);
	fscanf(fp, "%d", &count);
	fclose(fp);
	return count;
}

void writeAdminIdCountToTxt(int count)
{
	FILE* fp;
	fp = fopen("Admin Counter.txt", "w");
	fprintf(fp, "%d", count);
	fclose(fp);
}

void staffLogin()
{
	int isValid = 0;
	do
	{
		printf("\n\n");
		printf("  Login Detail\n");
		printf("  ============\n\n");
		inputAdminId(loginStaff[loginCount].id);
		inputAdminPassword(loginStaff[loginCount].privacy.password);
		isValid = validLogin();
		system("pause");
		system("cls");
	} while (!isValid);
}

//check existing staff
int validLogin()
{
	int isValid = 0;
	for (int i = 0; i < staffCount; i++)
	{
		if (strcmp(loginStaff[loginCount].id, staff[i].id) == 0 && strcmp(loginStaff[loginCount].privacy.password, staff[i].privacy.password) == 0)
		{
			isValid = 1;
			printf("\n%9s Welcome %s\n\n ", "", staff[i].privacy.name);
			getLogAct("Log in");
			break;
		}
	}
	if (!isValid)
		printf("\n%s\n ", "\tWrong ID or Password. You Are Not Allowed to Enter the System!\n");

	return isValid;
}

void getLogAct(char data[40])
{
	static int temp = 1;
	static int iLogin = 1;//hold the value even after function call

	//make sure login count remain unchange
	if (temp == 1)
		iLogin = loginCount;
	temp++;

	for (int i = 0; i < staffCount; i++)
	{
		if (strcmp(loginStaff[iLogin].id, staff[i].id) == 0)
		{
			strcpy(staff[i].activity, data);//get from various modules
			getTime(i);
			loginStaff[loginCount] = staff[i];
			loginCount++;
			break;
		}
	}
}

void getTime(int i)
{
	GetLocalTime(&autoTime);
	staff[i].time.year = autoTime.wYear;
	staff[i].time.month = autoTime.wMonth;
	staff[i].time.day = autoTime.wDay;
	staff[i].time.hrs = autoTime.wHour;
	staff[i].time.mins = autoTime.wMinute;
	staff[i].time.sec = autoTime.wSecond;
}

void addAdmin()
{
	getAdminId();
	displayAdminId();
	inputAdminName(staff[staffCount].privacy.name);
	inputAdminPosition(staff[staffCount].position);
	inputAdminFaculty(staff[staffCount].faculty);
	inputAdminPassword(staff[staffCount].privacy.password);
	inputAdminContactNo(staff[staffCount].privacy.phoneNum);
}

void searchAdmin()
{
	char keyword[51];
	int isFound = 0;
	char name[51] = "", pw[11] = "",  id[5] = "";
	char position[40] = "", faculty[5] = "", activity[40] = "";

	inputKeyword(keyword);
	for (int i = 0; i < staffCount; i++)
	{
		int isMatch = 0;

		strcpy(id, staff[i].id);
		strupr(id);
		strcpy(name, staff[i].privacy.name);
		strupr(name);
		strcpy(faculty, staff[i].faculty);
		strupr(faculty);
		strcpy(position, staff[i].position);
		strupr(position);
		strcpy(activity, staff[i].activity);
		strupr(activity);

		if (strstr(id, keyword) != NULL)
		{
			isMatch++;
		}
		else if (strstr(name, keyword) != NULL)
		{
			isMatch++;
		}
		else if (strstr(staff[i].privacy.phoneNum, keyword) != NULL)
		{
			isMatch++;
		}
		else if (strstr(faculty, keyword) != NULL)
		{
			isMatch++;
		}
		else if (strstr(position, keyword) != NULL)
		{
			isMatch++;
		}
		else if (strstr(activity, keyword) != NULL)
		{
			isMatch++;
		}
		if (isMatch)
		{
			showAdminRecord(i);
			printf("\n");
			isFound = 1;
		}
	}
	if (!isFound)
		printf("\n %8s %s\n ", "", "Staff Not Found!");
}

//return the array index & isFound of search result
void getAdminById(int* i, int* isFound)
{
	char id[5];
	inputAdminId(id);
	
	for (*i = 0; *i < staffCount; *i += 1)
	{
		if (strcmp(id, staff[*i].id) == 0)
		{
			showAdminRecord(*i);
			*isFound = 1;
			break;
		}
	}
	if (*isFound != 1)
		printf("\n%8s %s ", "", "Staff Not Found!");
}

void editAdmin()
{
	int index, isFound;
	char choice;
	char name[51] = "", pw[11] = "", phoneNum[12] = "";
	char position[40] = "", faculty[5] = "";

	printf("\n%30s", "Search Original Record");
	printf("\n%31s\n", "......................\n");
	getAdminById(&index, &isFound); //get index of record & isFound (to ensure the record exist)

	if (isFound == 1)
	{
		printf("\n%30s", "Modify Original Record");
		printf("\n%31s\n", "......................\n");
		printf("\n%100s\n", "Leave <Blank> and Press <Enter> to Skip Current Position to the Next Information Edition.\n");
		
		inputAdminName(name);
		inputAdminPosition(position);
		inputAdminFaculty(faculty);
		inputAdminPassword(pw);
		inputAdminContactNo(phoneNum);

		printf("\n%9s Sure to Edit? [Y for Yes] > ", "");
		scanf("%c", &choice);
		rewind(stdin);
		if (toupper(choice) == 'Y')
		{
			confirmEditAdmin(index, name, position, faculty, pw, phoneNum);
			printf("\n%9s %s", "", "Successfully Edited Record!");
		}
		else
			printf("\n%9s %s", "", "No Change Made!");
	}
}

void deleteAdmin()
{
	int index, isFound;
	char choice;
	getAdminById(&index, &isFound); //get index of record & isFound (to ensure the record exist)
	if (isFound == 1)
	{
		printf("%40s", "Sure to Delete? [Y for Yes] > ");
		scanf("%c", &choice);
		rewind(stdin);
		if (toupper(choice) == 'Y')
		{
			confirmDeleteAdmin(index);
			printf("\n%9s Successfully Deleted Record!", "");
		}
		else
			printf("\n%9s No Change Made.", "");
	}
}

void confirmEditAdmin(int i, char name[51], char position[40], char faculty[5], char pw[11], char phoneNum[12])
{
	if (strlen(name) != 0)
		strcpy(staff[i].privacy.name, name);
	if (strlen(position) != 0)
		strcpy(staff[i].position, position);
	if (strlen(faculty) != 0)
		strcpy(staff[i].faculty, faculty);
	if (strlen(pw) != 0)
		strcpy(staff[i].privacy.password, pw);
	if (strlen(phoneNum) != 0)
		strcpy(staff[i].privacy.phoneNum, phoneNum);
}

void confirmDeleteAdmin(int index)
{
	for (int i = index; i < staffCount; i++)
		staff[i] = staff[i + 1];
	staffCount--;
}

void displayAdmin()
{
	printf("\n\n");
	printf("  Show Admin Staff Detail\n");
	printf("  =======================\n");
	printf("\n");
	adminTable();
	printf("| %-39s| %-9s| %-14s| %-9s| %-19s| %-15s| %-39s| %-12s| %-11s|\n",
		"Name",
		"ID",
		"Password",
		"Faculty",
		"Position",
		"Contact Number",
		"Last Activity",
		"Date",
		"Time");
	adminTable();
	for (int i = 0; i < staffCount; i++)
	{
		printf("| %-39s| %-9s| %-14s| %-9s| %-19s| %-15s| %-39s| %02d/%02d/%04d  | %02d:%02d:%02d   |\n",
			staff[i].privacy.name,
			staff[i].id,
			staff[i].privacy.password,
			staff[i].faculty,
			staff[i].position,
			staff[i].privacy.phoneNum,
			staff[i].activity,
			staff[i].time.day,
			staff[i].time.month,
			staff[i].time.year,
			staff[i].time.hrs,
			staff[i].time.mins,
			staff[i].time.sec);
		adminTable();
	}
	system("pause");
}

void displayLogActReport()
{
	printf("\n\n");
	printf("  Report Login Staff Detail\n");
	printf("  =========================\n");
	printf("\n");
	adminReportTable();
	printf("| %-39s| %-9s| %-39s| %-12s| %-11s|\n",
		   "Name",
		   "ID",
		   "All Activities",
		   "Date",
		   "Time");
	adminReportTable();
	for (int i = 0; i < loginCount; i++)
	{
		printf("| %-39s| %-9s| %-39s| %02d/%02d/%04d  | %02d:%02d:%02d   |\n",
			   loginStaff[i].privacy.name,
			   loginStaff[i].id,
			   loginStaff[i].activity,
			   loginStaff[i].time.day,
		   	   loginStaff[i].time.month,
			   loginStaff[i].time.year,
			   loginStaff[i].time.hrs,
			   loginStaff[i].time.mins,
			   loginStaff[i].time.sec);
		adminReportTable();
	}
	system("pause");
}

void showAdminRecord(int i)
{
	printf("\n");
	adminTable();
	printf("| %-39s| %-9s| %-14s| %-9s| %-19s| %-15s| %-39s| %-12s| %-11s|\n",
		   "Name",
		   "ID",
		   "Password",
		   "Faculty",
		   "Position",
		   "Contact Number",
		   "Last Activity",
		   "Date",
		   "Time");
	adminTable();
	printf("| %-39s| %-9s| %-14s| %-9s| %-19s| %-15s| %-39s| %02d/%02d/%04d  | %02d:%02d:%02d   |\n",
		   staff[i].privacy.name,
		   staff[i].id,
		   staff[i].privacy.password,
		   staff[i].faculty,
		   staff[i].position,
		   staff[i].privacy.phoneNum,
		   staff[i].activity,
		   staff[i].time.day,
		   staff[i].time.month,
		   staff[i].time.year,
		   staff[i].time.hrs,
		   staff[i].time.mins,
		   staff[i].time.sec);
	adminTable();
}

void getAdminId()
{
	int count;
	char id[4];
	char temp[5] = "S";
	count = readAdminIdCountFromTxt();
	count++;//auto generate id
	writeAdminIdCountToTxt(count);

	sprintf(id, "%03d", count);
	strcat(temp, id);
	strcpy(staff[staffCount].id, temp);
}

void inputKeyword(char data[51])
{
	strcpy(data, "");
	printf("%10s %-20s > ", "", "Enter Keyword");
	scanf("%[^\n]", data);
	rewind(stdin);
	strupr(data);
}

void inputAdminName(char data[51])
{
	int isValid = 0;
	do
	{
		strcpy(data, "");
		printf("%10s %-20s > ", "", "Enter Name");
		scanf("%[^\n]", data);
		rewind(stdin);
		isValid = validLetter(data);
	} while (!isValid);
}

void inputAdminId(char data[5])
{
	int isValid = 0;
	do
	{
		strcpy(data, "");
		printf("%10s %-20s > ", "", "Enter ID");
		scanf("%[^\n]", data);
		rewind(stdin);
		isValid = validNoEmpty(data);
	} while (!isValid);
}

void inputAdminPosition(char data[40])
{
	int isValid = 0;
	do
	{
		strcpy(data, "");
		printf("%10s %-20s > ", "", "Enter Position");
		scanf("%[^\n]", data);
		rewind(stdin);
		data[0] = toupper(data[0]);
		isValid = validLetter(data);
	} while (!isValid);
}

void inputAdminFaculty(char data[5])
{
	int isValid = 0;
	do
	{
		strcpy(data, "");
		printf("%10s %-20s > ", "", "Enter Faculty");
		scanf("%[^\n]", data);
		rewind(stdin);
		strupr(data);
		isValid = validLetter(data);
	} while (!isValid);
}

void inputAdminPassword(char data[11])
{
	strcpy(data, "");
	printf("%10s %-20s > ", "", "Enter Password");
	scanf("%[^\n]", data);
	rewind(stdin);
}

void inputAdminContactNo(char data[12])
{
	int isValid = 0;
	do
	{
		strcpy(data, "");
		printf("%10s %-20s > ", "", "Enter Contact Number");
		scanf("%[^\n]", data);
		rewind(stdin);
		isValid = validDigit(data);
	} while (!isValid);
}

int validDigit(char data[14])
{
	int buff = strlen(data);
	for (int i = 0; i < buff; i++)
	{
		//make sure numeric phone no., space is valid in modify
		if (isdigit(data[i]) == 0 && isspace(data[i]) == 0)
		{
			printf("\n\t%s is Invalid. Please Enter Proper Number!\n\n", data);
			return 0;
		}
	}
	return 1;
}

int validLetter(char data[51])
{
	int buff = strlen(data);
	for (int i = 0; i < buff; i++)
	{
		//make sure alphabet name, space is valid in modify
		if (isalpha(data[i]) == 0 && isspace(data[i]) == 0)
		{
			printf("\n\t%s is Invalid. Please Enter Proper Letter!\n\n", data);
			return 0;
		}
	}
	return 1;
}

int validNoEmpty(char data[11])
{
	int buff = strlen(data);
	if (buff == 0)
	{
		printf("\n\t<Blank> is NOT Available. Please Enter Again!\n\n");
		return 0;
	}
	for (int i = 0; i < buff; i++)
	{
		if (isspace(data[i]) != 0)
		{
			printf("\n\t<Space> is NOT Available. Please Enter Again!\n\n");
			return 0;
		}
	}
	return 1;
}

void loopAddAdmin()
{
	char choice = 'y';
	while (toupper(choice) == 'Y')
	{
		printf("\n\n");
		printf("  Add Admin Staff Detail\n");
		printf("  ======================\n\n");
		addAdmin();
		printf("\n\n");
		printf("%7s Successfully Added Record!\n", "");
		printf("%51s", "Continue to Add New Record ? [Y for Yes] > ");
		scanf("%c", &choice);
		rewind(stdin);
		system("cls");
		staffCount++;
	}
}

void loopSearchAdmin()
{
	char choice = 'y';
	while (toupper(choice) == 'Y')
	{
		printf("\n\n");
		printf("  Search Admin Staff Detail\n");
		printf("  =========================\n\n");
		printf("%9s %s\n", "", "Do Not Enter Password and Time!\n");
		searchAdmin();
		printf("\n\n");
		printf("%9s %s", "", "Continue to Search Record ? [Y for Yes] > ");
		scanf("%c", &choice);
		rewind(stdin);
		system("cls");
	}
}

void loopDeleteAdmin()
{
	char choice = 'y';
	while (toupper(choice) == 'Y')
	{
		printf("\n\n");
		printf("  Delete Admin Staff Detail\n");
		printf("  =========================\n\n");
		deleteAdmin();
		printf("\n\n");
		printf("%9s %s", "", "Continue to Delete Record ? [Y for Yes] > ");
		scanf("%c", &choice);
		rewind(stdin);
		system("cls");
	}
}

void loopEditAdmin()
{
	char choice = 'y';
	while (toupper(choice) == 'Y')
	{
		printf("\n\n");
		printf("  Edit Admin Staff Detail\n");
		printf("  =======================\n\n");
		editAdmin();
		printf("\n\n");
		printf("%50s", "Continue to Edit Record ? [Y for Yes] > ");
		scanf("%c", &choice);
		rewind(stdin);
		system("cls");
	}
}

void displayAdminId()
{
	printf("%10s %-20s > ", "", "Enter ID");
	printf("%s\n", staff[staffCount].id);
}

void adminReportTable()
{
	printf(" ");
	for (int i = 0; i < 121; i++)
	{
		if (i == 0 || i == 120)
			printf("+");
		else
			printf("-");
	}
	printf("\n ");
}

void adminTable()
{
	printf(" ");
	for (int i = 0; i < 186; i++)
	{
		if (i == 0 || i == 185)
			printf("+");
		else
			printf("-");
	}
	printf("\n ");
}

int subAdminMenu()
{
	int choice;
	printf("\n\n");
	printf("\t===================================================================================\n");
	printf("\t=                                                                                 =\n");
	printf("\t=                        Administrative Staff Selection                           =\n");
	printf("\t=                                                                                 =\n");
	printf("\t===================================================================================\n");
	printf("\t=                                                                                 =\n");
	printf("\t=                          1. Add Records                                         =\n");
	printf("\t=                          2. Search Records                                      =\n");
	printf("\t=                          3. Modify Records                                      =\n");
	printf("\t=                          4. Display Records                                     =\n");
	printf("\t=                          5. Delete Records                                      =\n");
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