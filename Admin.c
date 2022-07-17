#include "admin.h"
#include "helpfulFunction.h"

extern User_t currentUser;
/* �ֲ�����ģ�� */
static int getChoice();

void runAdminSystem()
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
	int choice;
	showTitle(currentUser);
	do
	{
		showAdminMenu();
		HINT;
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);
	flush();

	return choice;
}