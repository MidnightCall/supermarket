#include "order.h"

/* �ֲ�����ģ�� */
static int getChoice();

/**
*  @brief: ���й�Ӧ��
*
*/
void runOrderSystem()
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
*  @brief: ��ѯ������Ϣ
*
*/
void queryOrder()
{

}

/**
*  @brief: ��Ӷ�����Ϣ
*
*/
void addOrder()
{
	printf("�����빩�����ṩ����Ʒ����");
}

/**
*  @brief: ɾ��������Ϣ
*
*/
void delOrder()
{

}

/**
*  @brief: ��ʾ���ж�����Ϣ
*
*/
void displayOrder()
{
	
}

/* �ֲ�����ʵ�� */
static int getChoice()
{
	int choice;

	do
	{
		showOrderBusinessMenu();
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);

	return choice;
}