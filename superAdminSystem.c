/*****************************************************************//**
 * \file   superAdminSystem.c
 * \brief  ���볬������Ա (SU Ȩ��) �Ĺ������
 *
 * \author moonlightvigil
 * \date   July 2022
 *********************************************************************/

#include "superAdminSystem.h"

/* �ֲ�����ģ�� */

extern User_t currentUser;
static int getChoice();

/*
*  \brief ���г�������Ա����ģ��
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

/* �ֲ�����ʵ�� */
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