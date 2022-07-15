#include "onSaleProduct.h"

/* �ֲ�����ģ�� */
static int getChoice();

/**
*  @brief: ����������Ʒ����
*
*/
void runProductSystem()
{
	int choice = getChoice();
	switch (choice)
	{
	default:
		break;
	case 1:
		displayProduct();
		break;
	case 2:
		queryProduct();
		break;
	}
}

/**
*  @brief: ��ѯ������Ʒ
*
*/
void queryProduct()
{
	int id;
	OnSale_t* onSaleProduct;
	printf("���������ѯ����Ʒid:");
	scanf("%d", &id);
	if (0 != findProduct_d(productDat, id, &onSaleProduct)) {
		// ��ӡ�ϼ���Ʒ��Ϣ
	}
	else {
		printf("������%d����Ʒ\n", id);
	}
}

/**
*  @brief: ��ʾ���д�����Ʒ��Ϣ
*
*/
void displayProduct()
{
	// ��ӡȫ���ϼ���Ʒ��Ϣ
}

/* �ֲ�����ʵ�� */
static int getChoice()
{
	int choice;

	do
	{
		showOnSaleBusinessMenu();
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);

	return choice;
}