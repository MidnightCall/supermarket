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
			addSupplier();
			break;
		case 4:
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
	id = getAnNonNegativeDigit("����ѯ������ ID");

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
			printf("�������������������Щ��������������������������������������������������������������������������������ϸ��Ϣ�����������������������Щ��������������������������������������������������Щ�������������������\n");
			printf("�� %7s�� %48s�� %10s�� %24s�� %8s��\n", "��Ʒ ID", "��Ʒ��", "����", "��Ӧ��", "�������");
			printf("�������������������੤�������������������������������������������������������������������������������������������������੤���������������������੤�������������������������������������������������੤������������������\n");

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
		printf("�������������������ة��������������������������������������������������������������������������������������������������ة����������������������ة��������������������������������������������������ة�������������������\n");
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
	stringGet(newSupplier->name, 21);

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
	id = getAnNonNegativeDigit("��ɾ����Ӧ�� ID");
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

/**
*  @brief: ��ʾ���й�Ӧ����Ϣ
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
	showTitle(currentUser);
	do
	{
		showSupplierBusinessMenu();
		HINT;
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);
	flush();

	return choice;
}