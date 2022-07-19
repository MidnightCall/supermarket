/*****************************************************************//**
 * \file   admin.c
 * \brief  进入管理员 (ADMIN 权限) 的管理界面
 *
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#include "admin.h"
#include "helpfulFunction.h"

extern User_t currentUser;
/* 局部函数模型 */
static int getChoice();

/**
 * \brief 运行管理员管理模块
 */
void runAdminSystem(void)
{
	while (1)
	{
		int choice = getChoice();
		switch (choice)
		{
		default:
			return;
		case 1:
			runOnSaleProductSystem();
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
}

/* 局部函数实现 */
static int getChoice()
{
	int choice = 0;
	do
	{
		showTitle(currentUser);
		showAdminMenu();
		choice = getMenuChoice();
	} while (choice > 5 || choice < 1);

	return choice;
}