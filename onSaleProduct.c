#include "onSaleProduct.h"

extern User_t currentUser;

/* �ֲ�����ģ�� */
static int getChoice();

/**
*  @brief: ����������Ʒ����
*/
void runOnSaleSystem()
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

/**
*  @brief: ��ѯ������Ʒ
*
*/
void queryOnSaleProduct()
{
	unsigned int id;
	OnSale_t onSale;
	printf("���������ѯ����Ʒid:");
	scanf("%u", &id);
	if (findIndexByID_d(productDat, id, &onSale, sizeof(Product_t)) != 0/* �˴��滻Ϊ��ѯ�ϼ���Ʒ�Ĳ��� */) {
		/* ��ӡ�����ϼ���Ʒ��Ϣ */
	} else {
		printf("������%d����Ʒ\n", id);
	}
}

/**
*  @brief: ����µ���Ʒ
*  @param product ��ӵ���Ʒ��Ϣ
*  @param allowance ��ӵĿ������
*
*/
void addOnSaleProduct(Product_t product, int allowance)
{
	OnSale_t onSaleProduct;
	onSaleProduct.product.id = product.id;
	onSaleProduct.product.price = product.price;
	onSaleProduct.allowance = allowance;
	strcpy(onSaleProduct.product.supplier, product.supplier);
	// ���뵽onSale�������
	PASS;
}

/**
*  @brief: ɾ��������Ʒ
*
*/
void delOnSaleProduct(void)
{
	int id;
	int pos;
	printf("�������ɾ����Ʒ ID: ");
	scanf("%d", &id);
	if ((pos = findIndexByID(productDat, id)) != 0) {
		// ɾ����Ӧ ID �Ĳ���
		printf("ɾ���ɹ���");
	} else {
		printf("������ ID %d ����Ʒ��", id);
	}
	system("pause");
	return;
}

/**
*  @brief: ��ʾ���д�����Ʒ��Ϣ
*
*/
void displayOnSaleProduct()
{
	PASS;
}

/* �ֲ�����ʵ�� */
static int getChoice()
{
	int choice;
	showTitle(currentUser);
	do
	{
		showOnSaleBusinessMenu();
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);

	return choice;
}