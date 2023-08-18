/*By Lim En Xi*/
#include "Header.h"

void main()
{
	int choice = 1;
	splashScreen();
	readAdminFromBin();
	readLoginFromBin();
	staffLogin();
	while (choice != 0)
	{
		choice = mainMenu();
		switch (choice)
		{
		case 1:
			visitorInformation();
			break;
		case 2:
			venueInformation();
			break;
		case 3:
			adminStaff();
			break;
		case 4:
			venueVisited();
			break;
		case 5:
			sanitization();
			break;
		case 0:
			writeAdminToBin();
			writeLoginToBin();
			endSystem();
			break;
		default:
			printf("\n\n\t\tPlease Enter Number 0-5!\n\n");
		}
	}
}

int mainMenu()
{
	int choice;
	printf("\n\n");
	printf("\t===================================================================================\n");
	printf("\t=                                                                                 =\n");
	printf("\t=                                Main Selection                                   =\n");
	printf("\t=                                                                                 =\n");
	printf("\t===================================================================================\n");
	printf("\t=                                                                                 =\n");
	printf("\t=                          1. Visitor Information                                 =\n");
	printf("\t=                          2. Venue Information                                   =\n");
	printf("\t=                          3. Administrative Staff                                =\n");
	printf("\t=                          4. Visits and Exits                                    =\n");
	printf("\t=                          5. Sanitization Records                                =\n");
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

void endSystem()
{
	printf("\n\n");
	printf("\t===================================================================================\n");
	printf("\t=                                                                                 =\n");
	printf("\t=                           You have Closed the System.                           =\n");
	printf("\t=                                                                                 =\n");
	printf("\t===================================================================================\n ");
}

void endModule()
{
	printf("\n\n");
	printf("\t===================================================================================\n");
	printf("\t=                                                                                 =\n");
	printf("\t=                           You have Closed the Module.                           =\n");
	printf("\t=                                                                                 =\n");
	printf("\t===================================================================================\n ");
}

void splashScreen()
{
	printf("\n");
	printf("\n\tTarucSejahtera CONTACT TRACKER");
	printf("\n\t==============================");
	printf("\n\n\n\t\t\t\t");
	printf("\tTarucSejahtera Contact Tracking System\n");
	printf("\n\t=====================================================================================================\n");
	printf("\n\n");
	printf("\t\t\t  OOOOOOOOO      OOO        OOO OOO     OOO     OOO     OOOOO    \n");
	printf("\t\t\t     OOO       OOO OOO      OOO   OOO   OOO     OOO   OOO    OOO \n");
	printf("\t\t\t     OOO      OOOOOOOOO     OOO OOO     OOO     OOO  OOO         \n");
	printf("\t\t\t     OOO      OOO   OOO     OOO  OOO     OOO   OOO    OOO    OOO \n");
	printf("\t\t\t     OOO      OOO   OOO     OOO    OOO     OOOOO        OOOOO    \n");
	printf("\n");
	printf("\t         //////   //////        //       /////   //   //   //////   //////   //////         /////\n");
	printf("\t        //       //            //      //  //   //   //     //     //       //   //       //  //\n");
	printf("\t       //////   //////        //     ///////   ///////     //     //////   //////       ///////\n");
	printf("\t          //   //       //   //    //    //   //   //     //     //       //  //      //    //\n");
	printf("\t     //////   //////   ///////   //     //   //   //     //     //////   //    //   //     //\n");
	printf("\n\n");
	printf("\n\t=====================================================================================================\n");
	printf("\n\n\t");
	system("pause");
	system("cls");
}