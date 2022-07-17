#include "supplier.h"
#include "typeCollection.h"

extern Node_t* storageDat;
extern Config_t configDat;
extern User_t currentUser;
/* �ֲ�����ģ�� */
static int getChoice();

/**
*  @brief: ���й�Ӧ��
*
*/
void runSupplierSystem()
{
	while (1)
	{
		int choice = getChoice();

		switch (choice)
		{
		default:
			return;
		case 1:
			displaySupplier();
			PAUSE;
			break;
		case 2:
			querySupplier();
			break;
		case 3:
			modifySupplier();
			break;
		case 4:
			addSupplier();
			break;
		case 5:
			delSupplier();
			break;
		}
	}
}

/**
*  @brief: ��ѯ��Ӧ����Ϣ
*
*/
void querySupplier()
{
	if (0 == *(int*)supplierDat->data)
	{
		printf("Ŀǰû�й�Ӧ�̡�");
		PAUSE;
		return;
	}

	displaySupplier();

	unsigned int id;
	Supplier_t* supplier = NULL;;
	id = getNonNegativeNumber("����ѯ������ ID");

	if (0 != findIndexByID_d(supplierDat, id, &supplier)) /* ��ѯ�ù������Ƿ���� */
	{ /* ��ӡ������������йص�������Ʒ */
		bool flag = false;
		Node_t* tHead = storageDat;
		if (NULL == storageDat->next)
		{
			printf("�ֿ��ڻ�û����Ʒ���޷���ѯ�ù����̹�Ӧ����Ʒ��");
		}
		else
		{
			printf("�������������������Щ��������������������������������������������������������������������������������ϸ��Ϣ�����������������������Щ����������������������Щ��������������������������������������������������Щ�������������������\n");
			printf("�� %7s�� %48s�� %10s�� %10s�� %24s�� %8s��\n", "��Ʒ ID", "��Ʒ��", "����", "����", "��Ӧ��", "�������");
			printf("�������������������੤�������������������������������������������������������������������������������������������������੤���������������������੤���������������������੤�������������������������������������������������੤������������������\n");

			tHead = storageDat->next;
			while (tHead != NULL)
			{
				if (0 == strcmp((char*)tHead->data + 52, supplier->name))
				{
					printStorageInfo(tHead->data);
					flag = true;
				}
				tHead = tHead->next;
			}
		}
		if (!flag)
		{
			printf("��                                              һ��Ҳû�С�                                                ��\n");
		}
		printf("�������������������ة��������������������������������������������������������������������������������������������������ة����������������������ة����������������������ة��������������������������������������������������ة�������������������\n");

	} 
	else 
	{
		printf("�����ڱ��Ϊ %d �Ĺ����̡�", id);
	}

	PAUSE;
	return;
}

/**
*  @brief: ��ӹ�Ӧ����Ϣ
*
*/
void addSupplier()
{
	Supplier_t* newSupplier = (Supplier_t*)malloc(sizeof(Supplier_t));
	assert(newSupplier);

	printf("�¹����� ID �� %d\n", ++configDat.maxId_Supplier);
	newSupplier->id = configDat.maxId_Supplier;
	//getchar();
	printf("�����빩��������: ");
	stringGet(newSupplier->name, 24);

	Supplier_t* tSupplier = NULL; 
	if (findIndexByName_d(supplierDat, newSupplier->name, OFFSET_SUPPLIER, &tSupplier)) /* �ж��Ƿ����ظ���Ӧ�� */
	{
		printf("�˹�Ӧ���Ѵ��ڣ�ID Ϊ %u.\n���ʧ�ܡ�", tSupplier->id);
		PAUSE;
		return;
	}

	insert(supplierDat, END, newSupplier);
	printf("�����ɡ�");
	PAUSE;
	return;
}

/**
*  @brief: ɾ����Ӧ����Ϣ
*
*/
void delSupplier(void)
{
	if (0 == *(int*)supplierDat->data)
	{
		printf("Ŀǰû�й�Ӧ�̡�");
		PAUSE;
		return;
	}

	displaySupplier();
	
	unsigned int id, pos;
	id = getNonNegativeNumber("��ɾ����Ӧ�� ID");
	if ((pos = findIndexByID(supplierDat, id)) != 0) {
		del(supplierDat, pos);
		printf("ɾ���ɹ���\n");
	}
	else {
		printf("������ ID %d �Ĺ�Ӧ�̡�", id);
	}

	PAUSE;
	return;
}


void modifySupplier()
{
	if (0 == *(int*)supplierDat->data)
	{
		printf("Ŀǰû�й�Ӧ�̡�");
		PAUSE;
		return;
	}

	displaySupplier();

	unsigned int id, pos;
	Supplier_t* tSupplier = NULL;
	char newName[21];
	id = getNonNegativeNumber("���޸Ĺ�Ӧ�� ID");
	if ((pos = findIndexByID_d(supplierDat, id, &tSupplier)) != 0)
	{
		printf("�����빩����������: ");
		stringGet(newName, 21);

		if (findIndexByName(supplierDat, newName, OFFSET_SUPPLIER)) /* �����޸ĵ��������Ƿ��������й�Ӧ��ײ���� */
		{
			printf("�������Ѵ��ڡ�");
			PAUSE;
			return;
		}

		Node_t* tHead_storage = storageDat;  /* ���ù�Ӧ���ڿ��ͻ����ϵ���Ʒ�����޸� */
		Node_t* tHead_onSale = productDat;

		if (tHead_storage->next != NULL)
		{
			tHead_storage = storageDat->next;
			while (tHead_storage != NULL)
			{
				if (0 == strcmp((char*)tHead_storage->data + 52, tSupplier->name))
				{
					strncpy((char*)tHead_storage->data + 52, newName, 21);
				}
				tHead_storage = tHead_storage->next;
			}
		}

		if (tHead_onSale->next != NULL)
		{
			tHead_onSale = storageDat->next;
			while (tHead_onSale != NULL)
			{
				if (0 == strcmp((char*)tHead_onSale->data + 52, tSupplier->name))
				{
					strncpy((char*)tHead_onSale->data + 52, newName, 21);
				}
				tHead_onSale = tHead_onSale->next;
			}
		}

		strncpy(tSupplier->name, newName, 21);

		printf("��������Ϣ�޸ĳɹ���\n");
	}
	else {
		printf("������ ID %d �Ĺ�Ӧ�̡�", id);
	}

	PAUSE;
	return;
}

/**
*  @brief ��ʾ���й�Ӧ����Ϣ
*
*/
void displaySupplier(void)
{
	if (0 == *(int*)supplierDat->data)
	{
		printf("Ŀǰû�й�Ӧ�̡�");
		return;
	}

	printf("���������������Щ�������������������������Ӧ����Ϣ����������������������������������������\n");
	printf("�� %5s�� %40s��\n", "ID", "����");
	printf("���������������੤����������������������������������������������������������������������������������\n");
	printList(supplierDat, printSupplierInfo, false);
	printf("���������������ة�����������������������������������������������������������������������������������\n");

	return;
}

/* �ֲ�����ʵ�� */
static int getChoice(void)
{
	int choice;
	do
	{
		showTitle(currentUser);
		showSupplierBusinessMenu();
		HINT;
		scanf("%d", &choice);
	} while (choice > 6 || choice < 1);
	flush();

	return choice;
}