#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"

/* 局部函数模型 */
static void showMenu();
static void showChar(char ch, int n);
static char* stringGet(char *st,int n);

/*
* 操作：运行登录/注册系统
*/
void runLogIn()
{
	int choice = getChoice();
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
		showMenu();
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);

	return choice;
}

/*
* 操作：注册账号
*/
void registration()
{
	UI account;
	static int currentAccount = 10000;
	int firstPassword;
	int secondPassword;

	printf("你的账号是%d\n", currentAccount);
	account.id = currentAccount++;
	do {
		printf("请输入你的密码:");
		stringGet(firstPassword, PSIZE);
		printf("请确认你的密码:");
		stringGet(secondPassword, PSIZE);
		if (firstPassword == secondPassword) {
			strcpy(account.password, firstPassword);
			break;
		}
	} while (1);
	printf("注册成功!\n");
	fwrite()
}

/* 局部函数定义 */
static void showMenu()
{
	showChar('-', 45);
	putchar('\n');
	printf("欢迎来到超市管理系统，请选择你要进行的操作:\n");
	printf("1.登录\n");
	printf("2.注册\n");
	printf("3.退出\n");
	showChar('-', 45);
	putchar('\n');
}

static void showChar(char ch, int n)
{
	for (int i = 0; i < n; i++)
		putchar(ch);
}

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
			FLUSH;
		}
	}

	return ret_val;
}