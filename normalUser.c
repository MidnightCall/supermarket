/*****************************************************************//**
 * \file   normalUser.c
 * \brief  ������ͨ�û� (COMMON Ȩ��) �Ĺ������
 *
 * \author praist
 * \date   July 2022
 *********************************************************************/

#include "admin.h"

extern User_t currentUser;

/* �ֲ�����ģ�� */
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

/* �ֲ�����ʵ�� */
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