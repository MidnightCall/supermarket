/*****************************************************************//**
 * \file   admin.c
 * \brief  �������Ա (ADMIN Ȩ��) �Ĺ������
 *
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#include "admin.h"
#include "helpfulFunction.h"

extern User_t currentUser;
/* �ֲ�����ģ�� */
static int getChoice();

/**
 * \brief ���й���Ա����ģ��
 */
void runAdminSystem(void)
{
	while (1)
	{
		int choice = getChoice();
		switch (choice)
		{
		default:
			return;
		case 1:
			runOnSaleProductSystem();
			break;
		case 2:
			runSupplierSystem();
			break;
		case 3:
			runOrderSystem();
			break;
		case 4:
			runStorageSystem();
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
		showAdminMenu();
		choice = getMenuChoice();
	} while (choice > 5 || choice < 1);

	return choice;
}