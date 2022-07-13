#include "superAdminSystem.h"

/* 局部函数模型 */
static int getChoice();

void runSuperAdminSystem()
{
	int choice = getChoice();

	switch (choice)
	{
		default:
			break;
		case 1:
			runAccountManage();
			break;
		case 2:
			// 此处处理员工信息
			break;
	}

}

/* 局部函数实现 */
static int getChoice()
{
	int choice;

	do
	{
		showSuperAdminMenu();
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);
	
	return choice;
}