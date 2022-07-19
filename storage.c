/*****************************************************************//**
 * \file   storage.c
 * \brief  �Կ������ܵ�ʵ��
 *
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#include "storage.h"
#include "typeCollection.h"
#include "helpfulFunction.h"

/* �ֲ�����ģ�� */
static int getChoice();

/**
*  \brief ���п�����ϵͳ
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
				printf("<!> Ŀǰû���κο�档\a");
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
			modifyProductInfo();
			break;
		case 4:
			inStorage();
			break;
		case 5:
			outStorage();
			break;
		}
	}
}

/**
*  \brief ��ѯ�����Ʒ
*/
void queryStorage(void)
{
	if (0 == *(int*)storageDat->data)
	{
		printf("<!> Ŀǰû���κο�档\a");
		PAUSE;
		return;
	}

	displayStorage();
	unsigned int id;
	Storage_t* storage = NULL;

	id = getNonNegativeNumber("���������ѯ����Ʒ ID: ");
	if (findProduct_d(storageDat, id, &storage) != 0) {
		printf("�������������������Щ��������������������������������������������������������������������������������ϸ��Ϣ�����������������������Щ����������������������Щ��������������������������������������������������Щ�������������������\n");
		printf("�� %7s�� %48s�� %10s�� %10s�� %24s�� %8s��\n", "��Ʒ ID", "��Ʒ��", "����", "����", "��Ӧ��", "�������");
		printf("�������������������੤�������������������������������������������������������������������������������������������������੤���������������������੤���������������������੤�������������������������������������������������੤������������������\n");
		printStorageInfo(storage);
		printf("�������������������ة��������������������������������������������������������������������������������������������������ة����������������������ة����������������������ة��������������������������������������������������ة�������������������\n");
	}
	else {
		printf("<!> ������ %d ����Ʒ��\a\n", id);
	}
	PAUSE;
	return;
}

/**
 * \brief �޸���Ʒ����
 */
void modifyProductInfo()
{
	if (0 == *(int*)storageDat->data)
	{
		printf("<!> Ŀǰû���κο�档\a");
		PAUSE;
		return;
	}

	displayStorage();
	unsigned int id;
	Storage_t* storage = NULL;
	Storage_t* newStorage = (Storage_t*)malloc(sizeof(Storage_t)); /* ����װ����Ϣ����ʱ���塣�������˳����������ʱ��ǵ� free */
	assert(newStorage != NULL);

	id = getNonNegativeNumber("��������޸ĵ���Ʒ ID: ");

	if (id > 1000000 || id < 100000)
	{
		printf("<!> ������� ID ��Ч��\a");
		free(newStorage); /* free ok */
		PAUSE;
		return;
	}

	if (findProduct_d(storageDat, id, &storage) != 0) /* �ڿ��������Ʒ����Ϊ����еļ�¼ɾ���� */
	{
		memcpy(newStorage, storage, sizeof(Storage_t)); /* �Ȱ�ԭ��Ʒ����Ϣ���Ƶ���ʱ������ */

		/* �±ߵ�������������ƣ�ֻ���������м�¼�������޸� */
		printf("����������Ʒ����");
		stringGet(newStorage->product.name, LEN_PRODUCT_NAME);
		if (0 == strlen(newStorage->product.name))
		{
			printf("<!> ��Ʒ�����Ȳ���Ϊ 0.\a");
			free(newStorage);
			PAUSE;
			return;
		}

		printf("�����빩Ӧ������: ");
		stringGet(newStorage->product.supplier, LEN_SUPPLIER_NAME);
		if (0 == strlen(newStorage->product.supplier))
		{
			printf("<!> ��Ӧ�������Ȳ���Ϊ 0.\a");
			free(newStorage);
			PAUSE;
			return;
		}

		if (!findIndexByName(supplierDat, newStorage->product.supplier, OFFSET_SUPPLIER)) /* ������Ʒ�Ĺ�Ӧ�̲����ڣ�����¹�Ӧ�̼��빩Ӧ��Ŀ¼ */
		{
			Supplier_t* newSupplier = (Supplier_t*)malloc(sizeof(Supplier_t));
			assert(newSupplier != NULL);

			newSupplier->id = ++configDat.maxId_Supplier;
			strcpy(newSupplier->name, newStorage->product.supplier);
			insert(supplierDat, END, newSupplier);
		}

		if (findProductByName_d(storageDat, newStorage->product.name, &newStorage)) /* �жϲֿ����Ƿ���������ͬ����Ӧ��Ҳ��ͬ����Ʒ��¼ */
		{
			if (0 == strcmp(newStorage->product.supplier, newStorage->product.supplier))
			{
				printf("<!> �ֿ����Ѵ��ڸ���Ʒ����Ϣ�޸�ʧ�ܡ�\a");
				free(newStorage); /* free ok */
				PAUSE;
				return;
			}
		}

		newStorage->product.purchase = getNonNegativeFloat("��������� (��/��): ");
		newStorage->product.price = getNonNegativeFloat("������۸� (��/��): ");

		if (newStorage->product.price <= newStorage->product.purchase) /* ���Ҫ������������ */
		{
			printf("<!> ��������ۼ۲����ڽ��ۡ���ȷ��Ҫ������[y/n]\a: ");
			char deleteOp = '\0';
			scanf("%c", &deleteOp);
			if (deleteOp == 'y' || deleteOp == 'Y') { }
			else if (deleteOp == 'n' || deleteOp == 'N')
			{
				free(newStorage); /* free ok */
				PAUSE;
				return;
			}
			else /* �Ȳ��� Y Ҳ���� N */
			{
				printf("<!> ������Ĳ�����Ч��\a");
				free(newStorage);
				PAUSE;
				return;
			}
		}

		int type = 0;
		while (1)
		{
			type = getNonNegativeNumber("��������Ʒ����\n[0. ����, 1. ����Ʒ]\n[2. getNonNegativeNumber, 3. ʳƷ]\n[4. ��ˮ����, 5. ���õ���]\n>>> ");
			if (type < 0 || type > 5)
			{
				printf("<!> ������������������������롣\a");
				continue;
			}
			break;
		}
		newStorage->product.type = type;

		OnSale_t* targetOnSale = NULL;
		if (findProduct_d(productDat, storage->product.id, &targetOnSale))
		{
			memcpy(&targetOnSale->product, &newStorage->product, sizeof(Product_t)); /* �ѻ����϶�Ӧ����Ʒ��ϢҲ�����޸� (����еĻ�) */
		}

		memcpy(storage, newStorage, sizeof(Storage_t)); /* ������Ϣ���Ƶ�ԭ��Ʒ�С���������У�������û�б仯�ġ� */
	}
	else
	{
		printf("<!> ���������Ʒ�����ڡ�\a");
	}

	free(newStorage); /* free ok */
	PAUSE;
	return;
}

/**
*  \brief ��Ʒ���
*/
void inStorage(void)
{
	displayStorage();
	unsigned int id = 0;
	unsigned int inStorageNumber; /* ������� */
	unsigned int type = 0; /* ��Ʒ���� */
	Storage_t* storage = NULL;
	Supplier_t* tsupplier = NULL;
	Storage_t* newStorage = (Storage_t*)malloc(sizeof(Storage_t));

	assert(NULL != newStorage);

	id = getNonNegativeNumber("��������Ʒ ID: ");
	if (id > 1000000 || id < 100000)
	{
		printf("<!> ������� ID ��Ч��\a");
		free(newStorage);
		PAUSE;
		return;
	}
	
	if (findProduct_d(storageDat, id, &storage) != 0) /* ���������Ѽ����˸���Ʒ����Ϣ */
	{ 
		printf("�ֿ����Ѵ��ڸ���Ʒ��");
		inStorageNumber = getNonNegativeNumber("�������������: ");
		storage->allowance += inStorageNumber;
		printf("�����ϡ�");
	} 
	else /* ����Ʒ��� */
	{ 
		//flush();
		printf("�ֿ����޸���Ʒ������Ʒ ID Ϊ %u.\n����������Ʒ����: ", configDat.maxId_Product + 1);
		stringGet(newStorage->product.name, LEN_PRODUCT_NAME);
		if (0 == strlen(newStorage->product.name))
		{
			printf("<!> ��Ʒ�����Ȳ���Ϊ 0.\a");
			free(newStorage);
			PAUSE;
			return;
		}

		printf("�����빩Ӧ������: ");
		stringGet(newStorage->product.supplier, LEN_SUPPLIER_NAME);
		if (0 == strlen(newStorage->product.supplier))
		{
			printf("<!> ��Ӧ�������Ȳ���Ϊ 0.\a");
			free(newStorage);
			PAUSE;
			return;
		}

		if (!findIndexByName(supplierDat, newStorage->product.supplier, OFFSET_SUPPLIER)) /* ������Ʒ�Ĺ�Ӧ�̲����ڣ�����¹�Ӧ�̼��빩Ӧ��Ŀ¼ */
		{
			Supplier_t* newSupplier = (Supplier_t*)malloc(sizeof(Supplier_t));
			assert(newSupplier != NULL);

			newSupplier->id = ++configDat.maxId_Supplier;
			strcpy(newSupplier->name, newStorage->product.supplier);
			insert(supplierDat, END, newSupplier);
		}

		if (findProductByName_d(storageDat, newStorage->product.name, &storage)) /* �жϲֿ����Ƿ���������ͬ����Ӧ��Ҳ��ͬ����Ʒ��¼ */
		{
			if (0 == strcmp(storage->product.supplier, newStorage->product.supplier))
			{
				printf("�ֿ����Ѵ��ڸ���Ʒ��");
				inStorageNumber = getNonNegativeNumber("�������������: ");
				storage->allowance += inStorageNumber;
				printf("�����ϡ�");
			}
		}
		else
		{
			newStorage->product.id = configDat.maxId_Product + 1; /* �Զ����� ID */

			newStorage->product.purchase = getNonNegativeFloat("��������� (��/��): ");
			newStorage->product.price = getNonNegativeFloat("������۸� (��/��): ");

			if (newStorage->product.price <= newStorage->product.purchase) /* ���Ҫ������������ */
			{
				printf("<!> ��������ۼ۲����ڽ��ۡ���ȷ��Ҫ������[y/n]: \a");
				char deleteOp = '\0';
				scanf("%c", &deleteOp);
				if (deleteOp == 'y' || deleteOp == 'Y') {}
				else if (deleteOp == 'n' || deleteOp == 'N')
				{
					free(newStorage); /* free ok */
					PAUSE;
					return;
				}
				else /* �Ȳ��� Y Ҳ���� N */
				{
					printf("<!> ������Ĳ�����Ч��\a");
					free(newStorage);
					PAUSE;
					return;
				}
			}

			while (1)
			{
				type = getNonNegativeNumber("��������Ʒ����\n[0. ����    , 1. ����Ʒ  ]\n[2. �칫��Ʒ, 3. ʳƷ    ]\n[4. ��ˮ����, 5. ���õ���]\n>>> ");
				if (type < 0 || type > 5)
				{
					printf("<!> ������������������������롣\a\n");
					continue;
				}
				break;
			}
			newStorage->product.type = type;
			newStorage->allowance = getNonNegativeNumber("�������������: ");
			++configDat.maxId_Product; /* !!! ��ӳɹ�ǰ���һ��������� ID �������������м�������Ļ����п�����Ϊ���м��˳���������� ID �װ�������*/
			insert(storageDat, END, newStorage);
			printf("�����ɡ�");
		}
	}
	PAUSE;
	return;
}

/**
*  \brief ��Ʒ���� / �ϼ�����
*/
void outStorage(void)
{
	if (0 == *(int*)storageDat->data)
	{
		printf("<!> Ŀǰû���κο�档\a");
		PAUSE;
		return;
	}

	displayStorage();
	unsigned int id;
	unsigned int outStorageNumber = 0;
	Storage_t* storage = NULL;

	id = getNonNegativeNumber("�������������Ʒ ID: ");
	if (findProduct_d(storageDat, id, &storage) != 0) /* ���Ҫ�������Ʒ�ڿ���� */
	{
		if (storage->allowance == 0) /* ���������Ʒ�Ѿ�û���� */
		{
			printf("<!> ����ʧ�ܣ��ֿ�����û��ʣ�����Ʒ %d.\a\n", id);
			PAUSE;
			return;
		}
		
		OnSale_t* tOnSale = NULL;
		if (findProduct_d(productDat, id, &tOnSale)) /* Ҫ�������Ʒ�Ѿ��ڻ������� */
		{
			outStorageNumber = getNonNegativeNumber("�������������: ");
			if (storage->allowance >= outStorageNumber)
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
			assert(newOnSale != NULL);

			newOnSale->product = storage->product;
			outStorageNumber = getNonNegativeNumber("�������������: ");
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
		printf("<!> ������ ID %u ����Ʒ��\a", id);
	}
	PAUSE;
	return;
}

/**
*  \brief ��ʾ���п����Ʒ��Ϣ
*/
void displayStorage(void)
{
	printf("�������������������Щ��������������������������������������������������������������������������������ϸ��Ϣ�����������������������Щ����������������������Щ��������������������������������������������������Щ�������������������\n");
	printf("�� %7s�� %48s�� %10s�� %10s�� %24s�� %8s��\n", "��Ʒ ID", "��Ʒ��", "����/��", "����/��", "��Ӧ��", "�������");
	printf("�������������������੤�������������������������������������������������������������������������������������������������੤���������������������੤���������������������੤�������������������������������������������������੤������������������\n");
	printList(storageDat, printStorageInfo, false);
	printf("�������������������ة��������������������������������������������������������������������������������������������������ة����������������������ة����������������������ة��������������������������������������������������ة�������������������\n");
	return;
}

/* �ֲ�����ʵ�� */
static int getChoice()
{
	int choice = 0;
	do
	{
		showTitle(currentUser);
		showStorageBusinessMenu();
		choice = getMenuChoice();
	} while (choice > 6 || choice < 1);

	return choice;
}