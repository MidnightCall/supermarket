#include "account.h"
#include "helpfulFunction.h"
#include <stdbool.h>

extern Node_t* userDat;

/*
* @brief：运行登录/注册系统
*/
void runLogIn()
{
	if (0 == *(int*)userDat->data) /* 如果文件里一个账户都没有，则自动创建一个超管 (SU) */ /* passed */
	{
		User_t Su = { 10000, "nE0ntLUlE", SU }; /* 超管默认属性 */
		User_t* newSu = (User_t*)malloc(sizeof(User_t));

		if (NULL == newSu)
		{
			printf("超级管理员账户初始化失败。\b\n");
			exit(0);
		}
		memcpy(newSu, &Su, sizeof(User_t));
		insert(userDat, END, newSu);
	}

	int choice = getChoice();
	switch (choice)
	{
		default:
			break;
		case 1:
			logIn();
			break;
		case 2:
			registration();
			break;
		case 3:
			system("cls");
			showExitMessage();
			break;
	}
}

/*
* @brief：显示操作菜单、读取用户的选择的操作
* 
*/
int getChoice()
{
	int choice;

	do
	{
		showLoginMessage();
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);
	flush();

	return choice;
}

/*
* @brief：注册账号
*/
void registration()
{
	printList(userDat, printUserInfo, false);
	int choice;
	User_t* account = (User_t*) malloc(sizeof(User_t));
	static int currentAccount = 10000;
	char firstPassword[LEN_PWD];
	char secondPassword[LEN_PWD];

	/* 账号显示 */
	printf("你的账号是 %d\n", currentAccount);
	account->id = currentAccount++;

	/* 账号权限分配
	do
	{
		printf("请选择你要注册的权限类型:\n");
		printf("1.普通用户\n2.管理员\n3.超级管理员\n");
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);
	
	flush();
	switch (choice)
	{
		default:
			break;
		case 1:
			account->permission = COMMON;
			break;
		case 2:
			account->permission = ADMIN;
			break;
		case 3:
			account->permission = SU;
			break;
	}
	*/

	/* 确认密码 */
	while (1)
	{
		printf("请输入你的密码: ");
		stringGet(firstPassword, LEN_PWD);
		if (strlen(firstPassword) < 6) {
			printf("密码至少六位，请重新输入\n");
			continue;
		}
		printf("请确认你的密码:");
		stringGet(secondPassword, LEN_PWD);
		if (strcmp(firstPassword, secondPassword) == 0) {
			strcpy(account->password, firstPassword);
			account->permission = COMMON; /* 默认为普通用户 */
			insert(userDat, END, account);
			break;
		}else{
			printf("两次输入不一致，请重新输入\n");
		}
	}
	printf("注册成功，请重新登录。\n");
}

/*
*  @brief: 登录账号
*/
void logIn()
{
	int id;
	char rawId[10]; /* ID 原始字符串 */
	char password[LEN_PWD];

	while (true)
	{
		printf("请输入账号: ");
		stringGet(rawId, 10);
		if (strlen(rawId) > 5)
		{
			printf("你输入的 ID 过长，请重新输入。\n");
			continue;
		}

		if (hasNonNumerical(rawId))
		{
			printf("你输入的 ID 格式有误，请重新输入。\n");
			continue;
		}

		id = atoi(rawId);

		User_t account;
		if (findIndexByID_d(userDat, id, &account, sizeof(User_t)) != 0) {
			printf("你好，ID %d 的用户\n", id);
			flush();
			printf("请输入密码:");
			stringGet(password, LEN_PWD);
			if (strcmp(password, account.password) == 0) {
				printf("登陆成功\n");
				currentUser.id = account.id;
				currentUser.permission = account.permission;
				strcpy(currentUser.password, account.password);
				break;
			} else {
				printf("密码错误,请重新输入账号和密码\n");
				flush();
				continue;
			}
		}
		else {
			printf("账号不存在，请重新确认后输入\n");
			continue;
		}
	}
	
}