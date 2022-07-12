#include <stdio.h>
#include <stdlib.h>
#include "login.h"

/* 局部函数模型 */
static void showMenu();
static void showChar(char ch, int n);

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
	showMenu();
	return 0;
}

/* 局部函数定义 */
static void showMenu()
{
	showChar('-', 45);
	printf("欢迎来到超市管理系统，请选择你要进行的操作:\n");
	printf("1.登录\n");
	printf("2.注册\n");
	printf("3.退出\n");
	showChar('-', 45);
}

static void showChar(char ch, int n)
{
	for (int i = 0; i < n; i++)
		printf(ch);
}