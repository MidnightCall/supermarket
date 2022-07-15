#include "superAdminSystem.h"

/* �ֲ�����ģ�� */

extern User_t currentUser;
static int getChoice();

void runSuperAdminSystem()
{
	while (1)
	{
		int choice = getChoice();

		switch (choice)
		{
		default:
			return;
		case 1:
			runAccountManage();
			break;
		case 2:
			runEmployeeManage();
			break;
		}
	}
}

/* �ֲ�����ʵ�� */
static int getChoice()
{
	int choice = 0;
	showTitle(currentUser);
	do
	{
		showSuperAdminMenu();
		printf(">>> ");
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);
	
	return choice;
}