#include "onSaleProduct.h"

/* �ֲ�����ģ�� */
static int getChoice();

/**
*  @brief: ����������Ʒ����
*
*/
void runOnSaleProductSystem()
{
	while (1)
	{
		int choice = getChoice();

		switch (choice)
		{
		default:
			return;
		case 1:
			displayOnSaleProduct();
			break;
		case 2:
			queryOnSaleProduct();
			break;
		}
	}
}

void queryOnSaleProduct(void)
{
	unsigned int id;
	OnSale_t* onSale = NULL;
	printf("���������ѯ����Ʒ ID: ");
	scanf("%u", &id);
	if (findProduct_d(productDat, id, &onSale)) {
		printOnSaleInfo(onSale);
	} else {
		printf("������ %d ����Ʒ\n", id);
	}
	PAUSE;
	return;
}

/**
*  @brief: ��ʾ���д�����Ʒ��Ϣ
*
*/
void displayOnSaleProduct(void)
{
	printList(productDat, printOnSaleInfo, true);
	system("pause");
	return;
}

/* �ֲ�����ʵ�� */
static int getChoice()
{
	int choice = 0;

	showTitle(currentUser);
	do
	{
		showOnSaleBusinessMenu();
		HINT;
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);

	return choice;
}