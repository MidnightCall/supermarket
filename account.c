/*****************************************************************//**
 * \file   account.c
 * \brief  对用户登录和注册功能的实现
 * 
 * \author praist
 * \date   July 2022
 *********************************************************************/

#include "account.h"
#include "helpfulFunction.h"
#include "SupermarketManageSystem.h"
#include <stdbool.h>

static int getChoice(void);

extern Node_t* userDat;
extern User_t currentUser;
extern Config_t configDat;

/**
 * \brief 进入登录和注册的选择菜单
 */
void runLogIn(void)
{
	if (0 == *(int*)userDat->data) /* 如果文件里一个账户都没有，则自动创建一个超管 (SU) */
	{
		User_t Su = { 10000, "admin", SU }; /* 超管默认属性 */
		User_t* newSu = (User_t*)malloc(sizeof(User_t));
		assert(newSu != NULL);

		memcpy(newSu, &Su, sizeof(User_t));
		insert(userDat, END, newSu);
	}

	int choice = getChoice();

	switch (choice)
	{
	default:
		system("cls");
		showExitMessage();
		PAUSE;
		saveData();
		exit(0);
		return;
	case 1:
		logIn();
		return;
	case 2:
		registration();
		currentUser.permission = -1; /* 回到初始界面 */
		return;
	}
}

/*
* \brief：注册账号
*/
void registration(void)
{
	int choice = 0;
	char firstPassword[LEN_PWD];
	char secondPassword[LEN_PWD];
	User_t* account = (User_t*)malloc(sizeof(User_t));
	assert(account != NULL);

	printf("═════════════════════用户注册═════════════════════\n");
	/* 账号显示 */
	printf("你的账号是 %d.\n", ++configDat.maxId_User); /* 不注册完不让出去，这里可以直接自增 */
	account->id = configDat.maxId_User;
	/* 确认密码 */
	while (1)
	{
		printf("请输入你的密码: ");
		stringGet(firstPassword, LEN_PWD);
		if (strlen(firstPassword) < 6) {
			printf("<!> 密码长度至少为六位，请重新输入。\a\n");
			continue;
		}

		printf("请确认你的密码: ");
		stringGet(secondPassword, LEN_PWD);
		if (strcmp(firstPassword, secondPassword) == 0) {
			strcpy(account->password, firstPassword);
			account->permission = COMMON; /* 默认为普通用户 */
			insert(userDat, END, account);
			break;
		} else {
			printf("<!> 两次密码输入不一致，请重新输入。\a\n");
		}
	}
	printf("注册成功，请重新登录。\n");
	PAUSE;
	return;
}

/**
 * \brief 登录账号
 */
void logIn(void)
{
	int id;
	char rawId[10]; /* ID 原始字符串 */
	char password[LEN_PWD];

	printf("═════════════════════用户登录═════════════════════\n");
	while (true)
	{
		printf("请输入账号: ");
		stringGet(rawId, 10);
		if (strlen(rawId) > 5)
		{
			printf("<!> 你输入的 ID 过长，请重新输入。\a\n");
			continue;
		}

		if (hasNonNumerical(rawId, false))
		{
			printf("<!> 你输入的 ID 格式有误，请重新输入。\a\n");
			continue;
		}

		id = atoi(rawId);

		User_t* account = NULL;
		if (findIndexByID_d(userDat, id, &account) != 0) {
			printf("您好，ID %d 的用户\n", id);
			printf("请输入密码: ");
			stringGet(password, LEN_PWD);
			if (strcmp(password, account->password) == 0) {
				printf("登录成功！");
				memcpy(&currentUser, account, sizeof(User_t));
				PAUSE;
				break;
			} else {
				printf("<!> 密码错误，请重新输入账号和密码。\a\n");
				continue;
			}
		} else {
			printf("<!> 账号不存在，请确认后重新输入。\a\n");
			continue;
		}
	}
}

static int getChoice(void)
{
	int choice = 0;
	do
	{
		showWelcomeMessage();
		showLoginMessage();
		choice = getMenuChoice();
	} while (choice > 3 || choice < 1);

	return choice;
}