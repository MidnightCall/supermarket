#include "storage.h"
#include "typeCollection.h"
#include "helpfulFunction.h"

extern User_t currentUser;
extern Node_t* productDat, * storageDat;
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
			if (0 == *(int*)storageDat->data)
			{
				printf("Ŀǰû���κο�档");
				PAUSE;
				return;
			}
			displayStorage();
			PAUSE;
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
	if (0 == *(int*)storageDat->data)
	{
		printf("Ŀǰû���κο�档");
		PAUSE;
		return;
	}

	displayStorage();
	unsigned int id;
	Storage_t* storage = NULL;

	id = getNonNegativeNumber("����ѯ����Ʒ ID");
	if (findProduct_d(storageDat, id, &storage) != 0) {
		printf("�������������������Щ��������������������������������������������������������������������������������ϸ��Ϣ�����������������������Щ����������������������Щ��������������������������������������������������Щ�������������������\n");
		printf("�� %7s�� %48s�� %10s�� %10s�� %24s�� %8s��\n", "��Ʒ ID", "��Ʒ��", "����", "����", "��Ӧ��", "�������");
		printf("�������������������੤�������������������������������������������������������������������������������������������������੤���������������������੤���������������������੤�������������������������������������������������੤������������������\n");
		printStorageInfo(storage);
		printf("�������������������ة��������������������������������������������������������������������������������������������������ة����������������������ة����������������������ة��������������������������������������������������ة�������������������\n");
	}
	else {
		printf("������ %d ����Ʒ��\n", id);
	}
	PAUSE;
	return;
}

/**
*  @brief: ���
*/
void inStorage(void)
{
	displayStorage();
	unsigned int id = 0;
	unsigned int inStorageNumber; /* ������� */
	unsigned int type = 0; /* ��Ʒ���� */
	Storage_t* storage = NULL;
	Supplier_t* supplier = NULL;
	Storage_t* newStorage = (Storage_t*)malloc(sizeof(Storage_t));

	assert(NULL != newStorage);

	while (1)
	{
		id = getNonNegativeNumber("��Ʒid");
		if (id > 1000000 || id < 100000)
		{
			printf("������� ID ��Ч�����������롣\b\n");
			continue;
		}
		break;
	}
	
	if (findProduct_d(storageDat, id, &storage) != 0) /* ���������Ѽ����˸���Ʒ����Ϣ */
	{ 
		printf("�ֿ����Ѵ��ڸ���Ʒ��");
		inStorageNumber = getNonNegativeNumber("�������");
		storage->allowance += inStorageNumber;
		printf("�����ϡ�");
	} 
	else /* ����Ʒ��� */
	{ 
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

		if (findProductByName_d(storageDat, newStorage->product.name, &storage)) /* �жϲֿ����Ƿ���������ͬ����Ӧ��Ҳ��ͬ����Ʒ��¼ */
		{
			if (0 == strcmp(storage->product.supplier, newStorage->product.supplier))
			{
				printf("�ֿ����Ѵ��ڸ���Ʒ��");
				inStorageNumber = getNonNegativeNumber("�������");
				storage->allowance += inStorageNumber;
				printf("�����ϡ�");
			}
		}
		else
		{
			newStorage->product.id = ++configDat.maxId_Product; /* �Զ����� ID */

			printf("��������� (��/��): "); // UNDONE (��С���)
			scanf("%f", &(newStorage->product.purchase));
			printf("������۸� (��/��): ");
			scanf("%f", &(newStorage->product.price));
			while (1)
			{
				type = getNonNegativeNumber("��Ʒ����\n[0. ����, 1. ����Ʒ]\n[2. �칫��Ʒ, 3. ʳƷ]\n[4. ��ˮ����, 5. ���õ���]\n>>> ");
				if (type < 0 || type > 5)
				{
					printf("������������������������롣");
					continue;
				}
				break;
			}
			newStorage->product.type = type;
			newStorage->allowance = getNonNegativeNumber("�������");
			insert(storageDat, END, newStorage);
			printf("�����ɡ�");
		}
	}
	PAUSE;
	return;
}

/**
*  @brief: ���� / �ϼ�����
*/
void outStorage(void)
{
	if (0 == *(int*)storageDat->data)
	{
		printf("Ŀǰû���κο�档");
		PAUSE;
		return;
	}

	displayStorage();
	unsigned int id;
	unsigned int outStorageNumber = 0;
	Storage_t* storage = NULL;

	id = getNonNegativeNumber("��������Ʒ ID");
	if (findProduct_d(storageDat, id, &storage) != 0) /* ���Ҫ�������Ʒ�ڿ���� */
	{
		if (storage->allowance == 0) /* ���������Ʒ�Ѿ�û���� */
		{
			printf("����ʧ�ܣ��ֿ�����û��ʣ�����Ʒ %d.\n", id);
			system("pause");
			return;
		}
		
		OnSale_t* tOnSale = NULL;
		if (findProduct_d(productDat, id, &tOnSale)) /* Ҫ�������Ʒ�Ѿ��ڻ������� */
		{
			outStorageNumber = getNonNegativeNumber("��������");
			if (storage->allowance - outStorageNumber >= 0)
			{
				storage->allowance -= outStorageNumber;
				tOnSale->allowance += outStorageNumber;
				printf("����ɹ���");
			}
			else
			{
				tOnSale->allowance += storage->allowance;
				printf("��治�㣬��ȫ�����⣬������ %u ����Ʒ��\n", storage->allowance);
				storage->allowance = 0;
			}
		}
		else /* Ҫ�������Ʒ�����ڻ����� */
		{
			OnSale_t* newOnSale = (OnSale_t*)malloc(sizeof(OnSale_t)); /* �µ�������Ʒ�ڵ� */
			if (NULL == newOnSale)
			{
				printf("����Ʒ�ڵ��ʼ��ʧ�ܡ�");
				system("pause");
				return;
			}

			newOnSale->product = storage->product;
			outStorageNumber = getNonNegativeNumber("��������");
			if (storage->allowance >= outStorageNumber) /* ע�⣬���� unsigned ����������ָ���ʱ�������ɳ�������� */
			{
				storage->allowance -= outStorageNumber;
				newOnSale->allowance = outStorageNumber;
				printf("����ɹ���");
			}
			else
			{
				newOnSale->allowance = storage->allowance;
				printf("��治�㣬��ȫ�����⣬������ %u ����Ʒ��", storage->allowance);
				storage->allowance = 0;
			}

			insert(productDat, END, newOnSale);

		}
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
	printf("�������������������Щ��������������������������������������������������������������������������������ϸ��Ϣ�����������������������Щ����������������������Щ��������������������������������������������������Щ�������������������\n");
	printf("�� %7s�� %48s�� %10s�� %10s�� %24s�� %8s��\n", "��Ʒ ID", "��Ʒ��", "����", "����", "��Ӧ��", "�������");
	printf("�������������������੤�������������������������������������������������������������������������������������������������੤���������������������੤���������������������੤�������������������������������������������������੤������������������\n");
	printList(storageDat, printStorageInfo, false);
	printf("�������������������ة��������������������������������������������������������������������������������������������������ة����������������������ة����������������������ة��������������������������������������������������ة�������������������\n");
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
		HINT;
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);
	flush();

	return choice;
}