#include "onSaleProduct.h"
#include "helpfulFunction.h"

/* �ֲ�����ģ�� */
static int getChoice();
extern User_t currentUser;
/**
*  @brief: ����������Ʒ����
*
*/
void runOnSaleProductSystem()
{
	while (1)
	{
		int choice = getChoice();

		switch (choice)
		{
		default:
			return;
		case 1:
			displayOnSaleProduct();
			break;
		case 2:
			queryOnSaleProduct();
			break;
		}
	}
}

void queryOnSaleProduct(void)
{
	unsigned int id;
	OnSale_t* onSale = NULL;
	printf("���������ѯ����Ʒ ID: ");
	scanf("%u", &id);
	if (findProduct_d(productDat, id, &onSale)) {
		printf("�������������������Щ�������������������������������������������������������������Ʒ��ϸ��Ϣ���������������Щ����������������������Щ����������������������Щ���������������\n");
		printf("�� %7s�� %48s�� %10s�� %10s�� %6s��\n", "��Ʒ ID", "��Ʒ��", "����", "����", "����");
		printf("�������������������੤�������������������������������������������������������������������������������������������������੤���������������������੤���������������������੤��������������\n");
		printOnSaleInfo(onSale);
		printf("�������������������ة��������������������������������������������������������������������������������������������������ة����������������������ة����������������������ة���������������\n");
	} else {
		printf("������ %d ����Ʒ\n", id);
	}
	PAUSE;
	return;
}

/**
*  @brief: ��ʾ���д�����Ʒ��Ϣ
*
*/
void displayOnSaleProduct(void)
{
	printf("�������������������Щ�������������������������������������������������������������Ʒ��ϸ��Ϣ���������������Щ����������������������Щ����������������������Щ���������������\n");
	printf("�� %7s�� %48s�� %10s�� %10s�� %6s��\n", "��Ʒ ID", "��Ʒ��", "����", "����", "����");
	printf("�������������������੤�������������������������������������������������������������������������������������������������੤���������������������੤���������������������੤��������������\n");
	printList(productDat, printOnSaleInfo, false);
	printf("�������������������ة��������������������������������������������������������������������������������������������������ة����������������������ة����������������������ة���������������\n");
	PAUSE;
	return;
}

/* �ֲ�����ʵ�� */
static int getChoice()
{
	int choice = 0;

	showTitle(currentUser);
	do
	{
		showOnSaleBusinessMenu();
		HINT;
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);

	return choice;
}