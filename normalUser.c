#include "Admin.h"


extern User_t currentUser;

/* 局部函数模型 */
static int getChoice();

void runNormalUserSystem()
{
	while (1)
	{
		int choice = getChoice();
		switch (choice)
		{
		default:
			return;
		case 1:
			queryOnSaleProduct();
			break;
		case 2:
			runNormalUserOrderSystem();
			break;
		}
	}
}

/* 局部函数实现 */
static int getChoice()
{
	int choice;

	do
	{
		showTitle(currentUser);
		showUserMenu();
		HINT;
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);
	flush();

	return choice;
}