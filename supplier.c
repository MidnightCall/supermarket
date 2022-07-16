#include "supplier.h"
#include "typeCollection.h"


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

	unsigned int id;
	Supplier_t* supplier = NULL;;
	id = getAnNonNegativeDigit("����ѯ������ ID");

	if (0 != findIndexByID_d(supplierDat, id, &supplier)) {
		printSupplierInfo(supplier);
	} else {
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
	//assert_null(newSupplier);

	printf("�¹����� ID �� %d\n", ++configDat.maxId_Supplier);
	newSupplier->id = configDat.maxId_Supplier;
	flush();
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
		PAUSE;
		return;
	}

	printf("���������������Щ�������������������������Ӧ����Ϣ����������������������������������������\n");
	printf("�� %5s�� %40s��\n", "ID", "����");
	printf("���������������੤����������������������������������������������������������������������������������\n");
	printList(supplierDat, printSupplierInfo, false);
	printf("���������������ة�����������������������������������������������������������������������������������\n");

	PAUSE;
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
		printf(">>> ");
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);
	flush();

	return choice;
}