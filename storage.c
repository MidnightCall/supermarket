#include "storage.h"
#include "typeCollection.h"

extern User_t currentUser;
extern Node_t* productDat;
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
void queryStorage(void)
{
	unsigned int id;
	Storage_t* storage = NULL;
	printf("���������ѯ����Ʒ ID: ");
	scanf("%u", &id);
	if (findProduct_d(storageDat, id, &storage) != 0) {
		printProductInfo(storage);
	}
	else {
		printf("������ %d ����Ʒ��\n", id);
	}
	system("pause");
	return;
}

/**
*  @brief: ���
*
*/
void inStorage(void)
{
	unsigned int id = 0;
	unsigned int inStorageNumber; /* ������� */
	Storage_t* storage = NULL;
	Supplier_t* supplier = NULL;
	Storage_t* newStorage = (Storage_t*)malloc(sizeof(Storage_t));

	if (NULL == newStorage)
	{
		printf("�¿��ڵ��ʼ��ʧ�ܡ�");
		system("pause");
		exit(0);
	}

	while (1)
	{
		printf("��������Ʒ ID: ");
		scanf("%u", &id);
		if (id > 1000000 || id < 100000)
		{
			printf("������� ID ��Ч�����������롣\b\n");
			continue;
		}
		break;
	}
	
	if (0 != findProduct_d(storageDat, id, &storage)) { /* ���������Ѽ����˸���Ʒ����Ϣ */
		printf("�ֿ����Ѵ��ڸ���Ʒ������д�������: ");
		scanf("%u", &inStorageNumber);
		storage->allowance += inStorageNumber;
		printf("�����ϡ�");
	}
	else { /* ����Ʒ��� */
		flush();
		printf("�ֿ����޸���Ʒ������Ʒ ID Ϊ %u.\n����������Ʒ����: ", configDat.maxId_Product + 1);
		stringGet(newStorage->product.name, 48);
		printf("�����빩Ӧ������: ");
		stringGet(newStorage->product.supplier, 24);

		if (!findIndexByName_d(supplierDat, newStorage->product.supplier, OFFSET_SUPPLIER, &supplier)) /* ������Ʒ�Ĺ�Ӧ�̲����ڣ�����¹�Ӧ�̼��빩Ӧ��Ŀ¼ */
		{
			Supplier_t* newSupplier = (Supplier_t*)malloc(sizeof(Supplier_t));
			newSupplier->id = ++configDat.maxId_Supplier;
			strcpy(newSupplier->name, newStorage->product.supplier);
			insert(supplierDat, END, newSupplier);
		}
		newStorage->product.id = ++configDat.maxId_Product; /* �Զ����� ID */

		printf("������۸�(��/��): ");
		scanf("%f", &(newStorage->product.price));
		printf("�������������: ");
		scanf("%u", &(newStorage->allowance));
		insert(storageDat, END, newStorage);
		printf("�����ɡ�");
	}
	system("pause");
	return;
}

/**
*  @brief: ���� / �ϼ�����
*/
void outStorage(void)
{
	unsigned int id, pos;
	unsigned int outStorageNumber;
	Storage_t* storage;

	printf("�������������Ʒ ID: ");
	scanf("%u", &id);
	if (findProduct_d(storageDat, id, &storage) != 0) /* ���Ҫ�������Ʒ�ڿ���� */
	{
		if (storage->allowance == 0) /* ���������Ʒ�Ѿ�û���� */
		{
			printf("����ʧ�ܣ��ֿ�����û��ʣ�����Ʒ %d", id);
			system("pause");
			return;
		}
		
		OnSale_t* tOnSale = NULL;
		if (findProduct_d(productDat, id, &tOnSale)) /* Ҫ�������Ʒ�Ѿ��ڻ������� */
		{
			printf("����д��������: ");
			scanf("%u", &outStorageNumber);
			if (storage->allowance - outStorageNumber >= 0)
			{
				storage->allowance -= outStorageNumber;
				tOnSale->allowance += outStorageNumber;
				printf("����ɹ���");
			}
			else
			{
				tOnSale->allowance += storage->allowance;
				printf("��治�㣬��ȫ�����⣬������ %u ����Ʒ\n", storage->allowance);
				storage->allowance = 0;
			}
		}
		else /* Ҫ�������Ʒ�����ڻ����� */
		{
			OnSale_t* newOnSale = (OnSale_t*)malloc(sizeof(OnSale_t));
			if (NULL == newOnSale)
			{
				printf("����Ʒ�ڵ��ʼ��ʧ�ܡ�");
				system("pause");
				return;
			}
		}
		/*
		// ����ȡ�ö�Ӧ���ϼ���Ʒ��ַ����
		if (storage.allowance > 0) {
			printf("����д��������: ");
			scanf("%u", &outStorageNumber);
			if (storage.allowance - outStorageNumber >= 0) {
				storage.allowance -= outStorageNumber;
				// �����ϼܲ���
				printf("����ɹ�\n");
			}else{
				// �����ϼܲ���
				storage.allowance = 0;
				printf("��治�㣬��ȫ�����⣬������ %u ����Ʒ��", storage.allowance);
			}
		}
		*/
	} else {
		printf("������ ID %u ����Ʒ��", id);
	}
	system("pause");
	return;
}

/**
*  @brief: ��ʾ���д�����Ʒ��Ϣ
*
*/
void displayStorage(void)
{
	// ��ӡ�����Ʒ��Ϣ
	printList(storageDat, printStorageInfo, true);
	system("pause");
	return;
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