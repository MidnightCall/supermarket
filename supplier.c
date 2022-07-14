#include "supplier.h"

/* �ֲ�����ģ�� */
static int getChoice();

/**
*  @brief: ���й�Ӧ��
*
*/
void runSupplierSystem()
{
	int choice = getChoice();

	switch (choice)
	{
	default:
		break;
	case 1:
		displaySupplier();
		break;
	case 2:
		querySupplier();
		break;
	case 3:
		addSupplier();
		break;
	case 4:
		delSupplier();
		break;
	}
}

/**
*  @brief: ��ѯ��Ӧ����Ϣ
*
*/
void querySupplier()
{
	int id;
	Supplier_t supplier;
	printf("���������ѯ�Ĺ�����id:");
	scanf("%d", &id);
	if (0 != findIndexByID_d(supplierDat, id, &supplier, sizeof(Supplier_t))) {
		printSupplierInfo(&supplier);
	}else {
		printf("�����ڱ��Ϊ%d�Ĺ�����\n", id);
	}
}

/**
*  @brief: ��ӹ�Ӧ����Ϣ
*
*/
void addSupplier()
{
	Supplier_t* newSupplier = (Supplier_t*)malloc(sizeof(Supplier_t));
	char productName[48];
	while (true)
	{
		printf("��������Ʒ������id:");
		scanf("%d", &newSupplier->id);
		if (findIndexByID(supplierDat, newSupplier ->id) != 0) {
			printf("������id�Ѵ��ڣ�����������\n");
		}
		else {
			break;
		}
	}
	flush();
	printf("�����빩��������:");
	stringGet(newSupplier->name, 21);
	printf("�����빩�����ṩ����Ʒ����:");
	stringGet(productName, 48);
	if (0 == findIndexByName(supplierDat, productName, OFFSET_SUPPLIER))
	{
		Product_t * newProduct = (Product_t*)malloc(sizeof(Product_t));
		/*
			���ɶ�Ӧ����Ʒid
		*/
		strcpy(newProduct->name, productName);
		strcpy(newProduct->supplier, newSupplier->name);
		printf("���������Ʒ�ļ۸�:");
		scanf("%f", &newProduct->price);
		insert(productDat, END, newProduct);
	}
	insert(supplierDat, END, newSupplier);
	printf("������\n");
}

/**
*  @brief: ɾ����Ӧ����Ϣ
*
*/
void delSupplier()
{
	int id;
	int pos;
	printf("�������ɾ����Ӧ��id:");
	scanf("%d", &id);
	if ((pos = findIndexByID(supplierDat, id)) != 0) {
		del(supplierDat, pos);
		printf("ɾ���ɹ�\n");
	}
	else {
		printf("������id%d�Ĺ�Ӧ��\n", id);
	}
}

/**
*  @brief: ��ʾ���й�Ӧ����Ϣ
*
*/
void displaySupplier()
{
	printList(supplierDat, printProductInfo, false);
}

/* �ֲ�����ʵ�� */
static int getChoice()
{
	int choice;

	do
	{
		showSupplierBusinessMenu();
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);

	return choice;
}