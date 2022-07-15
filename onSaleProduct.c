#include "onSaleProduct.h"

/* �ֲ�����ģ�� */
static int getChoice();

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
	}
	
}

void queryOnSaleProduct()
{
	int id;
	OnSale_t onSale;
	printf("���������ѯ����Ʒid:");
	scanf("%d", &id);
	if (findIndexByID_d(productDat, id, &onSale, sizeof(Product_t)) != 0/* �˴��滻Ϊ��ѯ�ϼ���Ʒ�Ĳ��� */) {
		/* ��ӡ�����ϼ���Ʒ��Ϣ */
	}else {
		printf("������%d����Ʒ\n", id);
	}
}

void addOnSaleProduct(Product_t product, int allowance)
{
	OnSale_t onSaleProduct;
	onSaleProduct.product.id = product.id;
	onSaleProduct.product.price = product.price;
	onSaleProduct.allowance = allowance;
	strcpy(onSaleProduct.product.supplier, product.supplier);
	// ���뵽onSale�������
}

void delOnSaleProduct()
{
	int id;
	int pos;
	printf("�������ɾ����Ʒid:");
	scanf("%d", &id);
	if ((pos = findIndexByID(productDat, id)) != 0) {
		// ɾ����Ӧid�Ĳ���
		printf("ɾ���ɹ�\n");
	}else {
		printf("������id%d����Ʒ\n", id);
	}
}

void displayOnSaleProduct()
{
	// ��ӡ���д�����Ʒ��Ϣ
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