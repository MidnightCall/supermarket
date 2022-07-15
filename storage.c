#include "storage.h"


extern User_t currentUser;
/* �ֲ�����ģ�� */
static int getChoice();

/**
*  @brief: ����������Ʒ����
*
*/
void runStorageSystem()
{
	while (1)
	{
		int choice = getChoice();

		switch (choice)
		{
		default:
			return;
		case 1:
			displayStorage();
			break;
		case 2:
			queryStorage();
			break;
		case 3:
			inStorage();
			break;
		case 4:
			outStorage();
			break;
		}
	}
}

/**
*  @brief: ��ѯ������Ʒ
*
*/
void queryStorage()
{
	unsigned int id;
	Storage_t* storage = NULL;
	printf("���������ѯ����Ʒ ID: ");
	scanf("%u", &id);
	if (findIndexByID_d(storageDat, id, &storage) != 0) {
		printProductInfo(&storage);
	}
	else {
		printf("������ %d ����Ʒ��\n", id);
	}
}

/**
*  @brief: ���
*
*/
void inStorage()
{
	unsigned int id = 0;
	Supplier_t supplier;
	Storage_t* storage = NULL;
	Storage_t* newStorage = (Storage_t*)malloc(sizeof(Storage_t));

	/* �ظ���Ʒ����ʾ�û���ӿ�� */
	printf("��������Ʒ ID: ");
	scanf("%u", &id);
	if (0 != findProduct_d(storageDat, id, &storage)) {
		unsigned int inStorageNumber;
		printf("�ֿ����Ѵ��ڸ���Ʒ������д�������: ");
		scanf("%u", &inStorageNumber);
		storage->allowance += inStorageNumber;
		printf("������\n");
	}
	else {
		flush();
		printf("��������Ʒ����:");
		stringGet(newStorage->product.name, 48);
		printf("�����빩Ӧ������:");
		stringGet(newStorage->product.supplier, 24);
		if (findIndexByName_d(supplierDat, newStorage->product.supplier, OFFSET_SUPPLIER, &supplier, sizeof(Supplier_t)))
		{
			newStorage->product.id = ++configDat.maxId_Product;
			strcpy(supplier.name, newStorage->product.supplier);
		}
		printf("������۸�($/��):");
		scanf("%f", &(newStorage->product.price));
		insert(storageDat, END, newStorage);
		printf("������\n");
	}

	
}

/**
*  @brief: ɾ��������Ʒ
*
*/
void outStorage()
{
	int id;
	int pos;
	Storage_t storage;

	printf("�������������Ʒ ID: ");
	scanf("%d", &id);
	if ((0 != (pos = findIndexByID_d(storageDat, id, &storage, sizeof(Storage_t))))/* �˴��滻Ϊ��ѯ���ĺ��� */) 
	{
		OnSale_t onSale;
		// ����ȡ�ö�Ӧ���ϼ���Ʒ��ַ����
		if (storage.allowance > 0) {
			int outStorageNumber;
			printf("����д��������: ");
			scanf("%d", &outStorageNumber);
			if (storage.allowance - outStorageNumber >= 0) {
				storage.allowance -= outStorageNumber;
				// �����ϼܲ���
				printf("����ɹ�\n");
			}else{
				// �����ϼܲ���
				storage.allowance = 0;
				printf("��治�㣬��ȫ�����⣬������%d����Ʒ\n", storage.allowance);
			}
		}
	}else {
		printf("������id%d����Ʒ\n", id);
	}
}

/**
*  @brief: ��ʾ���д�����Ʒ��Ϣ
*
*/
void displayStorage()
{
	// ��ӡ�����Ʒ��Ϣ
	PASS;
}

/* �ֲ�����ʵ�� */
static int getChoice()
{
	int choice;
	showTitle(currentUser);
	do
	{
		showStorageBusinessMenu();
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);

	return choice;
}