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
*  @brief: ��ѯ������Ʒ
*
*/
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

/**
*  @brief: ����µ���Ʒ
*
*/
void addOnSaleProduct()
{
	OnSale_t* newOnSaleProduct = (OnSale_t*)malloc(sizeof(OnSale_t));

	while (true)
	{
		printf("��������Ʒid:");
		scanf("%d",&(newOnSaleProduct->product.id));
		if (0 != findIndexByID(productDat, newOnSaleProduct->product.id)) {
			printf("��Ʒid�Ѵ��ڣ�����������\n");
		}else{
			break;
		}
	}
	flush();
	printf("��������Ʒ����:");
	stringGet(newOnSaleProduct->product.name, 48);
	printf("�����빩Ӧ������:");
	stringGet(newOnSaleProduct->product.supplier, 24);
	printf("������۸�($/��):");
	scanf("%f", &(newOnSaleProduct->product.price));
	insert(productDat, END, newOnSaleProduct);
	printf("������\n");
}

/**
*  @brief: ɾ��������Ʒ
*
*/
void delOnSaleProduct()
{
	int id;
	int pos;
	printf("�������ɾ����Ʒid:");
	scanf("%d", &id);
	if ((pos = findIndexByID(productDat, id)) != 0) {
		del(productDat, pos);
		printf("ɾ���ɹ�\n");
	}else {
		printf("������id%d����Ʒ\n", id);
	}
}

/**
*  @brief: ��ʾ���д�����Ʒ��Ϣ
*
*/
void displayOnSaleProduct()
{
	printList(productDat, printProductInfo, false);
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