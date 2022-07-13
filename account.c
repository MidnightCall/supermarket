#include "account.h"


/* 局部函数模型 */
static char* stringGet(char *st, int n);

/*
* 操作：运行登录/注册系统
*/
void runLogIn()
{
	int choice = getChoice();
	switch (choice)
	{
		default:
			break;
		case 1:
			logIn();
		case 2:
			registration();
	}
}

/*
* 操作：显示操作菜单、读取用户的选择的操作
* 后置条件：显示操作菜单
*/
int getChoice()
{
	int choice;

	do
	{
		showLoginMessage();
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);
	while (getchar() != '\n')
		continue;

	return choice;
}

/*
* 操作：注册账号
*/
void registration()
{
	int choice;
	User_t account;
	static int currentAccount = 10000;
	char * firstPassword[LEN_PWD];
	char * secondPassword[LEN_PWD];

	/* 账号显示 */
	printf("你的账号是 %d\n", currentAccount);
	account.id = currentAccount++;

	/* 账号权限分配 */
	do
	{
		printf("请选择你要注册的权限类型:\n");
		printf("1.普通用户\n2.管理员\n3.超级管理员\n");
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);
	while (getchar() != '\n')
		continue;
	switch (choice)
	{
		default:
			break;
		case 1:
			account.permission = USER;
			break;
		case 2:
			account.permission = ADMIN;
			break;
		case 3:
			account.permission = SU;
			break;
	}

	/* 确认密码 */
	while (1)
	{
		printf("请输入你的密码:");
		stringGet(firstPassword, LEN_PWD);
		if (strlen(firstPassword) < 6) {
			printf("密码至少六位,请重新输入\n");
			continue;
		}
		printf("请确认你的密码:");
		stringGet(secondPassword, LEN_PWD);
		if (strcmp(firstPassword, secondPassword) == 0) {
			strcpy(account.password, firstPassword);
			break;
		}else{
			printf("两次输入不一致，请重新输入\n");
		}
	}
	printf("注册成功,请重新登录\n");
}

/*
*  操作: 登录账号
*/
void logIn()
{
	int id;
	char* password[LEN_PWD];

	User_t* accounts = newList();
	loadFile("account.dat", accounts, sizeof(accounts));


}


/* 局部函数定义 */

static char* stringGet(char* st, int n)
{
	char* ret_val;
	char* find;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');
		if (find){
			*find = '\0';
		}
		else {
			while (getchar() != '\n')
				continue;
		}
	}

	return ret_val;
}