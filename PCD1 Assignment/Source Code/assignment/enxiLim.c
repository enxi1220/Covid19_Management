//#include<stdio.h>
//#include<stdlib.h>
//#include<math.h>
//#include<ctype.h>
//#pragma warning(disable:4996)
//
////set previous data as constant
//#define PREV_DAY 9
//#define PREV_CASE 19
//#define PREV_TOTAL 100
//#define PREV_DEATH 2
//#define PREV_RECOVER 12
//#define PREV_UNDER_TREATMENT 86
//#define PREV_DEATH_RATE 2.00
//#define PREV_RECOVER_RATE 12.00
//#define PREV_TREATMENT_RATE 86.00
//
////declaration for intro
//void intro();
//int  menu();
//
////declaration for previous day report
//void prevDayReport();
//void updatePrevDayData();
//int prevCase = PREV_CASE;
//int prevDay = PREV_DAY;
//int prevDeath = PREV_DEATH;
//int prevRecover = PREV_RECOVER;
//int prevTotal = PREV_TOTAL;
//int prevUnderTreatment = PREV_UNDER_TREATMENT;
//double prevDeathRate = PREV_DEATH_RATE;
//double prevRecoverRate = PREV_RECOVER_RATE;
//double prevTreatmentRate = PREV_TREATMENT_RATE;
//
////declaration for current data
//void loopCurrData();
//void currData();
//int  getLocal();
//int  getImported();
//void getDeaths();
//void getRecover();
//int  getCurrentCase();
//void getUnderTreatment();
//void showCaseDifference();
//int currCase;
//int currDeath;
//int currImported;
//int currLocal;
//int currRecover;
//
////summary and comparative
//int day;
//
////declaration for summary report
//void calculateSummCases();
//void calculateSummRate();
//void summReport();
//int summCase;
//int summDeath;
//int summImported;
//int summLocal;
//int summRecover;
//int summTotCase;
//int summUnderTreatment;
//double summDeathRate;
//double summRecoverRate;
//double summTreatmentRate;
//
////declaration for comparative report
//void calculateCompCases();
//void compReport();
//int compCase;
//int compDeath;
//int compRecover;
//int compTotCase;
//double compDeathRate;
//double compRecoverRate;
//
////declare for conclusion
//void conclusion();
//void getHighestLowest();
//int dayRecord = 0;
//int highestCases = PREV_CASE;
//int highestDay = PREV_DAY;
//int lowestCases = PREV_CASE;
//int lowestDay = PREV_DAY;
//
//void main()
//{
//	int choice = 1;
//
//	intro();
//	prevDayReport();
//	day = prevDay;
//	loopCurrData();
//
//	while (choice != 0)
//	{
//		choice = menu();
//		switch (choice)
//		{
//		case 1:
//			loopCurrData();
//			break;
//		case 2:
//			prevDayReport();
//			break;
//		case 3:
//			summReport();
//			break;
//		case 4:
//			compReport();
//			break;
//		case 0:
//			conclusion();
//			break;
//		default:
//			printf("\n\n\t\tPlease enter number 0-4\n\n");
//		}
//	}
//}
//
//void loopCurrData()
//{
//	char contChoice = 'Y';
//
//	while (toupper(contChoice) == 'Y')
//	{
//		currData();
//		printf("\n\n\n\n\n\n\n");
//		printf("\n\tContinue to update next day? [ Y for Yes ] : ");
//		rewind(stdin);
//		scanf("%c", &contChoice);
//		system("cls");
//	}
//}
//
//void currData()
//{
//	updatePrevDayData();
//	++day;
//	++dayRecord;
//
//	printf("\n\n");
//	printf("\tNewest Cases\n");
//	printf("\t============\n");
//	printf("\tTo update day %d cases \n\n", day);
//
//	currCase = getCurrentCase();
//	showCaseDifference();
//	getUnderTreatment();
//	calculateSummRate();
//	getHighestLowest();
//	calculateCompCases();
//
//	printf("\n\n");
//	system("cls");
//}
//
//int getCurrentCase()
//{
//	currLocal = getLocal();
//	currImported = getImported();
//
//	return currLocal + currImported;
//}
//
//void showCaseDifference()
//{
//	int difference = currCase - prevCase;
//
//	printf("\n\t\t\tNew total cases: %d\t\t\t", currCase);
//	if (difference == 0)
//		printf("[ Remain as the same as yesterday ]\n");
//	else
//		printf("[ %s by %d from yesterday ]\n", difference < 0 ? "Decreased" : "Increased", abs(difference));
//}
//
//int getLocal()
//{
//	int currLcl;
//
//	do
//	{
//		printf("\n\tNew local cases:");
//		scanf("%d", &currLcl);
//		rewind(stdin);
//
//		if (currLcl < 0)//make sure no negative case
//			printf("\t\tInvalid local cases , should only positive number! \n");
//	} while (currLcl < 0);
//
//	return currLcl;
//}
//
//int getImported()
//{
//	int currImp;
//
//	do
//	{
//		printf("\n\tNew imported cases:");
//		scanf("%d", &currImp);
//		rewind(stdin);
//
//		if (currImp < 0)//make sure no negative case
//			printf("\t\tInvalid imported cases, should only positive number! \n");
//	} while (currImp < 0);
//
//	return currImp;
//}
//
//void getDeaths()
//{
//	do {
//		printf("\n\tNew deaths cases:");
//		scanf("%d", &currDeath);
//		rewind(stdin);
//		if (currDeath < 0)//make sure no negative case
//			printf("\t\tInvalid deaths cases, should only positive number! \n");
//	} while (currDeath < 0);
//}
//
//void getRecover()
//{
//	do {
//		printf("\n\tNew recover cases:");
//		scanf("%d", &currRecover);
//		rewind(stdin);
//		if (currRecover < 0)//make sure no negative case
//			printf("\t\tInvalid recover cases, should only positive number! \n");
//	} while (currRecover < 0);
//}
//
//void getUnderTreatment()
//{
//	do
//	{
//		getDeaths();
//		getRecover();
//		calculateSummCases();
//		if (summUnderTreatment < 0)//make sure no negative case
//			printf("\t\tUnder treament cases are less than 0, please re-input deaths cases and recover cases. \n");
//
//	} while (summUnderTreatment < 0);
//}
//
//void calculateSummCases()
//{
//	summLocal = currLocal;
//	summImported = currImported;
//	summCase = currCase;
//	summTotCase = summCase + prevTotal;
//	summDeath = currDeath + prevDeath;
//	summRecover = currRecover + prevRecover;
//	summUnderTreatment = summTotCase - summDeath - summRecover;
//}
//
//void calculateSummRate()
//{
//	summDeathRate = (double)summDeath / summTotCase * 100;
//	summRecoverRate = (double)summRecover / summTotCase * 100;
//	summTreatmentRate = (double)summUnderTreatment / summTotCase * 100;
//}
//
//void calculateCompCases()
//{
//	compCase = currCase;
//	compTotCase = compCase + prevTotal;
//	compDeath = currDeath + prevDeath;
//	compRecover = currRecover + prevRecover;
//	compDeathRate = (double)compDeath / compTotCase * 100;
//	compRecoverRate = (double)compRecover / compTotCase * 100;
//}
//
//void getHighestLowest()
//{
//	if (currCase > highestCases)
//	{
//		highestCases = currCase;
//		highestDay = day;
//	}
//	if (currCase < lowestCases)
//	{
//		lowestCases = currCase;
//		lowestDay = day;
//	}
//}
//
//void updatePrevDayData()
//{
//	if (prevDay + 1 == day)
//	{
//		prevDay = day;
//		prevCase = summCase;
//		prevDeath = summDeath;
//		prevTotal = summTotCase;
//		prevRecover = summRecover;
//		prevDeathRate = summDeathRate;
//		prevRecoverRate = summRecoverRate;
//		prevTreatmentRate = summTreatmentRate;
//		prevUnderTreatment = summUnderTreatment;
//	}
//}
//
//void summReport()
//{
//	printf("\n\tDay %d Summary Report", day);
//	printf("\n\t=====================\n");
//	printf("\n\t+-----------------+---------------+----------------+-------------------+-------------------+");
//	printf("\n\t|    %s   |  %s  |  %s  |  %s  |  %s  |", "New cases ", "Total Cases", "Total deaths", "Total Recovered", "Under treatment");
//	printf("\n\t+-----------------+---------------+----------------+-------------------+-------------------+");
//	printf("\n\t| %s  %6d | %13s | %14s | %17s | %17s |", "Local  ", summLocal, "", "", "", "");
//	printf("\n\t| %s  %5d | %13s | %14s | %17s | %17s |", "Imported", summImported, "", "", "", "");
//	printf("\n\t|    %12d | %13d | %14d | %17d | %17d |", summCase, summTotCase, summDeath, summRecover, summUnderTreatment);
//	printf("\n\t+-----------------+---------------+----------------+-------------------+-------------------+");
//	printf("\n\t     %28s | %13.2lf%% | %16.2lf%% | %16.2lf%% |", "", summDeathRate, summRecoverRate, summTreatmentRate);
//	printf("\n\t     %28s +----------------+-------------------+-------------------+", "");
//	printf("\n\n  ");
//	system("pause");
//	system("cls");
//}
//
//void compReport()
//{
//	int caseDiff = compCase - prevCase;
//	int totCaseDiff = compTotCase - prevTotal;
//	double deathRateDiff = compDeathRate - prevDeathRate;
//	double recoverRateDiff = compRecoverRate - prevRecoverRate;
//
//	printf("\n\tDaily Comparative Report");
//	printf("\n\t========================\n\n");
//	printf("\t%31s +---------------+-------------+-------------------+\n", "");
//	printf("\t%31s |   Yesterday   |    Today    |    DIFFERENCES    |\n", "");
//	printf("\t%31s |     Day %-4d  |   Day %-4d  |                   |\n", "", prevDay, day);
//	printf("\t+-------------------------------+---------------+-------------+-------------------+\n");
//	printf("\t|  New cases    %15s | %13d | %11d | %4s %c %-5d %2s   |\n", "", prevCase, compCase, "", (caseDiff == 0 ? '\0' : caseDiff >= 0 ? '+' : '-'), abs(caseDiff), "");
//	printf("\t+-------------------------------+---------------+-------------+-------------------+\n");
//	printf("\t|  Total cases  %15s | %13d | %11d | %4s %c %-5d %2s   |\n", "", prevTotal, compTotCase, "", (totCaseDiff == 0 ? '\0' : totCaseDiff >= 0 ? '+' : '-'), abs(totCaseDiff), "");
//	printf("\t+-------------------------------+---------------+-------------+-------------------+\n");
//	printf("\t|  Death Rate   %15s |   %10.2lf%% |   %8.2lf%% | %4s %c %-5.2lf%%  %2s |\n", "", prevDeathRate, compDeathRate, "", (deathRateDiff == 0 ? '\0' : deathRateDiff >= 0 ? '+' : '-'), fabs(deathRateDiff), "");
//	printf("\t+-------------------------------+---------------+-------------+-------------------+\n");
//	printf("\t|  Recover Rate %15s |   %10.2lf%% |   %8.2lf%% | %4s %c %-5.2lf%%  %2s |\n", "", prevRecoverRate, compRecoverRate, "", (recoverRateDiff == 0 ? '\0' : recoverRateDiff >= 0 ? '+' : '-'), fabs(recoverRateDiff), "");
//	printf("\t+-------------------------------+---------------+-------------+-------------------+\n");
//	printf("\n\n\n\n\n\n\n  ");
//	system("pause");
//	system("cls");
//}
//
//void prevDayReport()
//{
//	printf("\n\n");
//	printf("\tPrevious Day Report\n");
//	printf("\t===================\n\n");
//	printf("\t+---------------+-------------+---------------+----------------+-------------------+-------------------+\n");
//	printf("\t|     %3s       |  %s  |  %s  |  %s  |  %s  |  %s  |\n", "", "New Cases", "Total Cases", "Total Deaths", "Total Recovered", "Under treatment");
//	printf("\t+---------------+-------------+---------------+----------------+-------------------+-------------------+\n");
//	printf("\t|     Day %-4d  | %11d | %13d | %14d | %17d | %17d |\n", prevDay, prevCase, prevTotal, prevDeath, prevRecover, prevUnderTreatment);
//	printf("\t+---------------+-------------+---------------+----------------+-------------------+-------------------+\n");
//	printf("\t      %35s     | %13.2lf%% | %16.2lf%% | %16.2lf%% |\n", "", prevDeathRate, prevRecoverRate, prevTreatmentRate);
//	printf("\t                                              +----------------+-------------------+-------------------+");
//	printf("\n\n  ");
//	system("pause");
//	system("cls");
//}
//
//void conclusion()
//{
//	printf("\n\n\n\n");
//	printf("\t\t\t==========================================================================\n");
//	printf("\t\t\t=                                                                        =\n");
//	printf("\t\t\t=     %-25s     => %5d  [  %s %4d ", dayRecord != 1 ? "TOTAL days recorded" : "TOTAL day recorded", dayRecord, " Day", PREV_DAY + 1);
//	if (dayRecord == 1)
//		printf(" ]            =\n");
//	else
//		printf("%s %-4d ]     =\n", "to", day);
//	printf("\t\t\t=     %-25s     => %5d  [  %s %4d  ]            = \n", "HIGHEST number of cases", highestCases, " Day", highestDay);
//	printf("\t\t\t=     %-25s     => %5d  [  %s %4d  ]            = \n", "LOWEST number of cases", lowestCases, " Day", lowestDay);
//	printf("\t\t\t=                                                                        =\n");
//	printf("\t\t\t==========================================================================\n");
//	printf("\n\n");
//	printf("\t\t\t\t      Thank you     Please take full precautions !!! \n\n\n  ");
//	system("pause");
//}
//
//int menu()
//{
//	int choice;
//
//	printf("\n\n");
//	printf("\t===================================================================================\n");
//	printf("\t=                                                                                 =\n");
//	printf("\t=                                    Selection                                    =\n");
//	printf("\t=                                                                                 =\n");
//	printf("\t===================================================================================\n");
//	printf("\t=                                                                                 =\n");
//	printf("\t=                          1. Update New Case                                     =\n");
//	printf("\t=                          2. Previous Day Report                                 =\n");
//	printf("\t=                          3. Daily Summary Report                                =\n");
//	printf("\t=                          4. Daily Comparative Report                            =\n");
//	printf("\t=                          0. Exit                                                =\n");
//	printf("\t=                                                                                 =\n");
//	printf("\t===================================================================================\n");
//	printf("\t=                                                                                 =\n");
//	printf("\t=                          Enter your choice from menu                            =\n");
//	printf("\t=                                                                                 =\n");
//	printf("\t===================================================================================\n");
//	printf("\n\t\t\t\t\t   Here ");
//	scanf("%d", &choice);
//	system("cls");
//
//	return choice;
//}
//
//void intro()
//{
//	printf("\n");
//	printf("\n\tCOVID-19 CASES TRACKER");
//	printf("\n\t=======================");
//	printf("\n\n\n\t\t\t\t");
//	printf("\t\tCOVID-19 CASES Tracking\n");
//	printf("\n\t=====================================================================================================\n");
//	printf("\n\n");
//	printf("\t\t    OOOOOOOOOOO         OOOOOOOOO    OOOOO            OOOOO   OOOOO    OOOOOOOOO       \n");
//	printf("\t\t  OOOOOOOOOOOOOOO     OOOOOOOOOOOOO   OOOOO          OOOOO    OOOOO    OOOOOOOOOOOO    \n");
//	printf("\t\t OOOOO       OOOOO   OOOOO     OOOOO   OOOOO        OOOOO     OOOOO    OOOOO    OOOOO  \n");
//	printf("\t\tOOOOO               OOOOO       OOOOO   OOOOO      OOOOO      OOOOO    OOOOO     OOOOO \n");
//	printf("\t\tOOOOO               OOOOO       OOOOO    OOOOO    OOOOO       OOOOO    OOOOO     OOOOO \n");
//	printf("\t\t OOOOO       OOOOO   OOOOO     OOOOO      OOOOO  OOOOO        OOOOO    OOOOO    OOOOO  \n");
//	printf("\t\t  OOOOOOOOOOOOOOO     OOOOOOOOOOOOO        OOOOOOOOOO         OOOOO    OOOOOOOOOOOO    \n");
//	printf("\t\t    OOOOOOOOOOO         OOOOOOOOO           OOOOOOOO          OOOOO    OOOOOOOOO       \n");
//	printf("\n");
//	printf("\n\t=====================================================================================================\n");
//	printf("\n\t\t\t\t\t    ");
//	printf("Report updated in the evening\n");
//	printf("\n\n  ");
//	system("pause");
//	system("cls");
//}