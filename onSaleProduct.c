#include "onSaleProduct.h"

/* �ֲ�����ģ�� */
static int getChoice();

/**
*  @brief: ����������Ʒ����
*
*/
void runOnSaleSystem()
{
	int choice = getChoice();

	switch (choice)
	{
	default:
		break;
	case 1:
		displayOnSaleProduct();
		break;
	case 2:
		queryOnSaleProduct();
		break;
	case 3:
		addOnSaleProduct();
		break;
	case 4:
		delOnSaleProduct();
		break;
	}
}

/**
*  @brief: ����������Ʒ����
*
*/
void queryOnSaleProduct()
{

}

/**
*  @brief: ��Ӵ�����Ʒ
*
*/
void addOnSaleProduct()
{

}

/**
*  @brief: ɾ��������Ʒ
*
*/
void delOnSaleProduct()
{

}

/**
*  @brief: ��ʾ���д�����Ʒ��Ϣ
*
*/
void displayOnSaleProduct()
{

}

/* �ֲ�����ʵ�� */
static int getChoice()
{
	int choice;

	do
	{
		showOnSaleBusinessMenu();
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);

	return choice;
}