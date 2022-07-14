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
	Product_t product;
	printf("���������ѯ����Ʒ ID: ");
	scanf("%d", &id);
	if (findIndexByID_d(productDat, id, &product, sizeof(Product_t)) != 0) {
		printProductInfo(&product);
	}else {
		printf("������ %d ����Ʒ\n", id);
	}
}

/**
*  @brief: ��Ӵ�����Ʒ
*
*/
void addOnSaleProduct()
{
	Product_t* newProduct = (Product_t*)malloc(sizeof(Product_t));

	while (true)
	{
		printf("��������Ʒid:");
		scanf("%d",& newProduct->id);
		if (findIndexByID(productDat, newProduct->id) != 0) {
			printf("��Ʒid�Ѵ��ڣ�����������\n");
		}else{
			break;
		}
	}
	flush();
	printf("��������Ʒ����:");
	stringGet(newProduct->name, 48);
	printf("�����빩Ӧ������:");
	stringGet(newProduct->supplier, 24);
	printf("������۸�($/��):");
	scanf("%f", &newProduct->price);
	insert(productDat, END, newProduct);
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