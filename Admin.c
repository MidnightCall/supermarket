#include "Admin.h"
#include "helpfulFunction.h"

/* �ֲ�����ģ�� */
static int getChoice();

void runAdminSystem()
{
	int choice = getChoice();

	switch (choice)
	{
		default:
			break;
		case 1:
			runOnSaleSystem();
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

/* �ֲ�����ʵ�� */
static int getChoice()
{
	int choice;

	do
	{
		showAdminMenu();
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);

	return choice;
}