/*By Lim En Xi*/
/*Share*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>
#pragma warning (disable:4996)
#pragma warning (disable:6031)
#pragma warning (disable:4129)
#define SPACE 26 //used by jy
#define LARGER_SPACE 64 //used by jy

SYSTEMTIME autoTime;

typedef struct
{
	int day;
	int month;
	int year;
	int hrs;
	int mins;
	int sec;
}Time;

typedef struct
{
	char name[51];
	char password[11];
	char icNo[13];
	char phoneNum[12];
}Private;

//design
void splashScreen();
int mainMenu();
void endSystem();
void endModule();

/*Visit Exit Module*/
void venueVisited();
int subVenueVisitedMenu();
void venueVisitedReadFile();
void venueVisitedWriteFile();
void venueVisitedAddRecords();
void venueVisitedSearchRecords();
void venueVisitedModifyRecords();
void venueVisitedDisplayRecords();
void venueVistedReports();
void venueVisitedDeleteRecords();

//validate 
void venueVisitedValidDate(int day, int month, int year, int* venueVisitedValidateDate);
void venueVisitedValidTime(int hrs, int mins, int* venueVisitedValidateTime);
int  venueVisitedValidPhoneNum(char num[12]);
int venueVisitedValidIcNo(char num[13]);
void venueVisitedValidTemperature(double temperature, double* temperatures);

/*Admin Staff Module*/
//Administrative Staff Module (display no need loop)
void adminStaff();
void loopAddAdmin();
void loopSearchAdmin();
void loopDeleteAdmin();
void loopEditAdmin();

//design
int subAdminMenu();

//file
void checkAdminFile(FILE* fp);
void readAdminFromBin();
void writeAdminToBin();
void readLoginFromBin();
void writeLoginToBin();
int readAdminIdCountFromTxt();
void writeAdminIdCountToTxt(int);

//login before enter system
void staffLogin();
int validLogin();

//system get data automatically
void getLogAct(char data[40]);
void getTime(int);
void getAdminId();
void displayAdminId();

//input admin data
void inputKeyword(char data[51]);
void inputAdminName(char data[51]);
void inputAdminId(char data[5]);
void inputAdminPassword(char data[11]);
void inputAdminFaculty(char data[5]);
void inputAdminContactNo(char data[12]);
void inputAdminPosition(char data[40]);

//validation of input
int validDigit(char data[14]);
int validLetter(char data[51]);
int validNoEmpty(char data[11]);

//add data
void addAdmin();

//display data
void displayAdmin();
void adminTable();

//search data
void searchAdmin();
void getAdminById(int* i, int* isFound);
void showAdminRecord(int i);

//edit data
void editAdmin();
void confirmEditAdmin(int i, char name[51], char position[40], char faculty[5], char pw[11], char phoneNum[12]);

//delete data
void deleteAdmin();
void confirmDeleteAdmin(int index);

//report data
void displayLogActReport();
void adminReportTable();

/*Sanitization Module*/
void sanitization();
int subSaznitizationMenu(); // Function for the menu.
void readFile();
void writeFile();
void addRecords();
void searchRecords();
void modifyRecords();
void displayRecords();
void deleteRecords();
void report();
int validDate(int day, int month, int year); //Function for validate the Date.
int validTime(int hour, int min); //Function for validate the Time.
int validPhoneNum(char num[11]); //Function for validate the Phone Number.

/*Venue Information Module*/
void venueInformation();
int subVenueMenu();
void readVenueInfo();
void writeVenueInfo();
void addVenueInfo();
void searchVenueInfo();
void modifyVenueInfo();
void displayVenueInfo();
void deleteVenueInfo();
void reportVenueInfo();

/*Visitor Information Module*/
void visitorInformation();
int visitor_validateOccup(char occu[SPACE]);
int visitor_validateVisited(char place[SPACE]);
void visitor_add();
void visitor_delete();
void visitor_display();
void visitor_modify();
void visitor_report();
void visitor_search();
int subVisitorMenu();