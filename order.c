#include "order.h"

/* �ֲ�����ģ�� */
static int getChoice();

/**
*  @brief: ���ж���ϵͳ
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
		displayOrder();
		break;
	case 2:
		queryOrder();
		break;
	case 3:
		calTurnover();
		break;
	}
}

/**
*  @brief: ��ʾ���ж�����Ϣ
*
*/
void displayOrder() 
{
	// ��ӡ���ж�����Ϣ�Ĳ���
}

/**
*  @brief: ��ѯ������Ϣ
*
*/
void queryOrder()
{
	int id;
	Order_t order;
	printf("���������ѯ�Ķ���id:");
	scanf("%d", &id);
	if (findIndexByID_d(orderDat, id, &order, sizeof(Order_t)) != 0/* �˴��滻Ϊ��ѯ�ϼ���Ʒ�Ĳ��� */) {
		printOrderInfo(&order);
	}else {
		printf("������idΪ%d�ŵĶ���\n", id);
	}
}

/**
*  @brief: ������Ӫҵ��
*
*/
void calTurnover()
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