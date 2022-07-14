#include "Admin.h"

/* 局部函数模型 */
static int getChoice();

void runAdminSystem()
{
	int choice = getChoice();

	switch (choice)
	{
		default:
			break;
		case 1:
			runOnSaleSystem();
			break;
		case 2:
			runSupplierSystem();
			break;
		case 3:
			// 订单管理
			break;
		case 4:
			//库存管理
			break;
	}
}

/* 局部函数实现 */
static int getChoice()
{
	int choice;

	do
	{
		showAdminMenu();
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);

	return choice;
}