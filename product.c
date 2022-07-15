#include "product.h"

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
	case 3:
		addProduct();
		break;
	case 4:
		delProduct();
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
	Product_t product;
	printf("���������ѯ����Ʒid:");
	scanf("%d", &id);
	if (findIndexByID_d(productDat, id, &product, sizeof(Product_t)) != 0) {
		printProductInfo(&product);
	}
	else {
		printf("������%d����Ʒ\n", id);
	}
}

/**
*  @brief: ��Ӵ�����Ʒ
*
*/
void addProduct()
{
	Product_t* newProduct = (Product_t*)malloc(sizeof(Product_t));

	while (true)
	{
		printf("��������Ʒid:");
		scanf("%d", &newProduct->id);
		if (findIndexByID(productDat, newProduct->id) != 0) {
			printf("��Ʒid�Ѵ��ڣ�����������\n");
		}
		else {
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
void delProduct()
{
	int id;
	int pos;
	printf("�������ɾ����Ʒid:");
	scanf("%d", &id);
	if ((pos = findIndexByID(productDat, id)) != 0) {
		del(productDat, pos);
		printf("ɾ���ɹ�\n");
	}
	else {
		printf("������id%d����Ʒ\n", id);
	}
}

/**
*  @brief: ��ʾ���д�����Ʒ��Ϣ
*
*/
void displayProduct()
{
	printList(productDat, printProductInfo, false);
}

/* �ֲ�����ʵ�� */
static int getChoice()
{
	int choice;

	do
	{
		showProductMenu();
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);

	return choice;
}