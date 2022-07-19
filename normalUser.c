/*****************************************************************//**
 * \file   normalUser.c
 * \brief  进入普通用户 (COMMON 权限) 的管理界面
 *
 * \author praist
 * \date   July 2022
 *********************************************************************/

#include "admin.h"

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
	int choice = 0;
	do
	{
		showTitle(currentUser);
		showUserMenu();
		choice = getMenuChoice();
	} while (choice > 5 || choice < 1);

	return choice;
}