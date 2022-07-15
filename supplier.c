#include "supplier.h"


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
	unsigned int id;
	Supplier_t* supplier = NULL;;
	printf("���������ѯ�Ĺ����� ID:");
	scanf("%u", &id);

	if (0 != findIndexByID_d(supplierDat, id, &supplier)) {
		printSupplierInfo(supplier);
	} else {
		printf("�����ڱ��Ϊ %d �Ĺ����̡�", id);
	}
	system("pause");
	return;
}

/**
*  @brief: ��ӹ�Ӧ����Ϣ
*
*/
void addSupplier()
{
	Supplier_t* newSupplier = (Supplier_t*)malloc(sizeof(Supplier_t));
	if (NULL == newSupplier)
	{
		printf("�����̽ڵ��ʼ��ʧ�ܡ�");
		system("pause");
		exit(0);
	}

	printf("�¹����� ID �� %d\n", ++configDat.maxId_Supplier);
	newSupplier->id = configDat.maxId_Supplier;
	flush();
	printf("�����빩��������: ");
	stringGet(newSupplier->name, 21);
	insert(supplierDat, END, newSupplier);
	printf("�����ɡ�");
	system("pause");
	return;
}

/**
*  @brief: ɾ����Ӧ����Ϣ
*
*/
void delSupplier(void)
{
	unsigned int id, pos;
	printf("�������ɾ����Ӧ�� ID:");
	scanf("%u", &id);
	if ((pos = findIndexByID(supplierDat, id)) != 0) {
		del(supplierDat, pos);
		printf("ɾ���ɹ�\n");
	}
	else {
		printf("������ ID %d �Ĺ�Ӧ�̡�", id);
	}
	system("pause");
	return;
}

/**
*  @brief: ��ʾ���й�Ӧ����Ϣ
*
*/
void displaySupplier(void)
{
	printList(supplierDat, printSupplierInfo, false);
	system("pause");
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

	return choice;
}