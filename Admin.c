#include "Admin.h"
#include "helpfulFunction.h"

extern User_t currentUser;
/* 局部函数模型 */
static int getChoice();

void runAdminSystem()
{
	int choice = getChoice();

	switch (choice)
	{
		default:
			return;
		case 1:
			runOnSaleSystem();
			break;
		case 2:
			runSupplierSystem();
			break;
		case 3:
			runOrderSystem();
			break;
		case 4:
			runStorageSystem();
			break;
	}
}

/* 局部函数实现 */
static int getChoice()
{
	int choice;
	showTitle(currentUser);
	do
	{
		showAdminMenu();
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);

	return choice;
}