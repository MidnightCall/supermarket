#include "superAdminSystem.h"

/* �ֲ�����ģ�� */
static int getChoice();

void runSuperAdminSystem()
{
	int choice = getChoice();

	switch (choice)
	{
		default:
			break;
		case 1:
			runAccountManage();
			break;
		case 2:
			// �˴�����Ա����Ϣ
			break;
	}

}

/* �ֲ�����ʵ�� */
static int getChoice()
{
	int choice;

	do
	{
		showSuperAdminMenu();
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);
	
	return choice;
}