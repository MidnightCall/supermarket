#include "accountManage.h"
#include "helpfulFunction.h"

/* 局部函数模型 */
static int getChoice();

void runAccountManage() 
{
	int choice = getChoice();

	switch (choice)
	{
		default:
			break;
		case 1:
			modifyUserPermission();
			break;
		case 2:
			deleteUserInfo();
			break;
		case 3:
			addUserInfo();
			break;
		case 4:
			queryUser();
			break;
	}
}

void queryUser()
{

}

void modifyUserPermission()
{

}

void deleteUserInfo()
{

}

void addUserInfo()
{

}

/* 局部函数实现 */
static int getChoice()
{
	int choice;

	do
	{
		showAccountBusinessMenu();
		scanf("%d", &choice);
	} while (choice > 4 || choice < 1);

	return choice;
}