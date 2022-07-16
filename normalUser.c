#include "Admin.h"


/* 局部函数模型 */
static int getChoice();

void runNormalUserSystem()
{
	int choice = getChoice();
	switch (choice)
	{
	default:
		break;
	case 1:
		queryOnSaleProduct();
		break;
	case 2:
		runSupplierSystem();
		break;
	}
}

/* 局部函数实现 */
static int getChoice()
{
	int choice;

	do
	{
		showUserMenu();
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);
	flush();

	return choice;
}