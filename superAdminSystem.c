/*****************************************************************//**
 * \file   superAdminSystem.c
 * \brief  进入超级管理员 (SU 权限) 的管理界面
 *
 * \author moonlightvigil
 * \date   July 2022
 *********************************************************************/

#include "superAdminSystem.h"

/* 局部函数模型 */

extern User_t currentUser;
static int getChoice();

/*
*  \brief 运行超级管理员管理模块
*/
void runSuperAdminSystem(void)
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

/* 局部函数实现 */
static int getChoice()
{
	int choice = 0;
	do
	{
		showTitle(currentUser);
		showSuperAdminMenu();
		choice = getMenuChoice();
	} while (choice > 3 || choice < 1);
	
	return choice;
}