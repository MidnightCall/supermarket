/*****************************************************************//**
 * \file   accountManage.c
 * \brief  对超级管理员 (SU 权限) 的用户管理功能的实现
 *
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#include "accountManage.h"
#include "helpfulFunction.h"
#include "customLookup.h"
#include "linkList.h"
#include "typeCollection.h"

extern Node_t* userDat;
extern User_t currentUser;

/* 局部函数模型 */
static int getChoice();

/**
 * \brief 运行用户处理模块
 */
void runAccountManage()
{
	while (1)
	{
		int choice = getChoice();

		switch (choice)
		{
		default:
			return;
		case 1:
			showAllUsers();
			PAUSE;
			break;
		case 2:
			queryUser();
			break;
		case 3:
			modifyUserPermission();
			break;
		case 4:
			deleteUser();
			break;
		}
	}
}

/**
 * \brief 查找用户信息
 */
void queryUser(void)
{
	User_t* tUser = NULL;
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("═════════════════════查询用户═════════════════════\n");
	unsigned int tId = 0, index = 0;
	while (true)
	{
		tId = getNonNegativeNumber("请输入账号 ID: ");
		if (tId < 10000 || tId > 99999)
		{
			printf("<!> 你输入的 ID 无效，请重新输入。\a\n");
			continue;
		}
		index = findIndexByID_d(userDat, tId, &tUser);
		if (0 == index)
		{
			printf("<!> 没有符合条件的用户。\n");
			PAUSE;
			return;
		}
		showSingleUser(*tUser);
		break;
	}

	PAUSE;
	return;
}

/**
 * \brief 更改用户权限
 */
void modifyUserPermission(void)
{
	User_t* tUser = NULL;
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("═════════════════════修改权限═════════════════════\n");
	unsigned int tId = 0, index = 0;
	while (true)
	{
		tId = getNonNegativeNumber("请输入账号 ID: ");

		if (tId < 10000 || tId > 99999)
		{
			printf("<!> 你输入的 ID 无效，请重新输入。\a\n");
			continue;
		}

		if (tId == 10000)
		{
			printf("<!> 你无法修改超级管理员 [10000] 的权限。\a\n");
			PAUSE;
			return;
		}

		index = findIndexByID_d(userDat, tId, &tUser);
		if (0 == index)
		{
			printf("<!> 没有符合条件的用户。\a");
			PAUSE;
			return;
		}
		showSingleUser(*tUser);
		break;
	}

	unsigned int op = 0;
	while (true)
	{
		op = getNonNegativeNumber("请输入你要更改到的目标权限\n[0. 普通用户, 1. 管理员]: ");
		if (op < 0 || op > 1)
		{
			printf("<!> 你输入的权限等级无效，请重新输入。\a\n");
			continue;
		}
		User_t* tUsr = (User_t*)getData(userDat, index);
		tUsr->permission = op;
		break;
	}
	showSingleUser(*tUser);
	printf("权限修改成功！");
	PAUSE;
	return;

}

/**
 * \brief 删除用户
 */
void deleteUser(void)
{
	showAllUsers();

	User_t* tUser = NULL;

	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("═════════════════════删除用户═════════════════════\n");
	unsigned int index = 0;
	while (true)
	{
		unsigned int tId = 0;
		tId = getNonNegativeNumber("请输入账户 ID: ");
		if (tId < 10000 || tId > 99999)
		{
			printf("<!> 你输入的 ID 无效。\a");
			PAUSE;
			return;
		}

		if (tId == 10000)
		{
			printf("<!> 你无法删除超级管理员 [10000].\a\n");
			PAUSE;
			return;
		}

		index = findIndexByID_d(userDat, tId, &tUser);
		if (0 == index)
		{
			printf("<!> 没有符合条件的用户。\a");
			PAUSE;
			return;
		}
		showSingleUser(*tUser);
		break;
	}

	while (true)
	{
		printf("确定要删除吗？[y/n]: ");
		char deleteOp = '\0';
		scanf("%c", &deleteOp);
		if (deleteOp != 'y' && deleteOp != 'n' && deleteOp != 'Y' && deleteOp != 'N')
		{
			printf("<!> 你输入的操作无效，请重新输入。\a\n");
			continue;
		}
		if (deleteOp == 'y' || deleteOp == 'Y')
		{
			del(userDat, index);
			printf("用户删除成功！\n");
			showAllUsers();
			break;
		}
		if (deleteOp == 'n' || deleteOp == 'N')
			return;
	}

	PAUSE;
	return;
}

/**
 * \brief 显示单条用户信息
 */
void showSingleUser(User_t e)
{
	printf("┌────────┬───────────账号信息────────────────────┐\n");
	printf("│ %7s│ %12s│ %24s│\n", "ID", "密码", "权限等级");
	printf("├────────┼─────────────┼─────────────────────────┤\n");
	printUserInfo(&e);
	printf("└────────┴─────────────┴─────────────────────────┘\n");
}

/**
 * \brief 显示所有用户信息
 */
void showAllUsers(void)
{
	printf("┌────────┬───────────账号信息────────────────────┐\n");
	printf("│ %7s│ %12s│ %24s│\n", "ID", "密码", "权限等级");
	printf("├────────┼─────────────┼─────────────────────────┤\n");
	printList(userDat, printUserInfo, false);
	printf("└────────┴─────────────┴─────────────────────────┘\n");
	return;
}

/* 局部函数实现 */
static int getChoice()
{
	int choice = 0;
	do
	{
		showTitle(currentUser);
		showAccountBusinessMenu();
		choice = getMenuChoice();
	} while (choice > 5 || choice < 1);

	return choice;
}
