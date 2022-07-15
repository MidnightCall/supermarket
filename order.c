#include "order.h"
#include "helpfulFunction.h"

/* �ֲ�����ģ�� */
static int getChoice();

int currentIndex = 0;
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
*  @brief: ���е�ǰ��������ģ��(������Աʹ��)
*
*/
void runNormalUserOrderSystem()
{
	int choice = getNormalChoice();

	switch (choice)
	{
	default:
		break;
	case 1:
		addProductToCurrentOrder();
		break;
	case 2:
		delProductFromCurrentOrder();
		break;
	case 3:
		calTurnOverInCurrentOrder();
		break;
	case 4:
		submitCurrentOrder();
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

/**
*  @brief: ��ǰ���������Ʒ
*
*/
void addProductToCurrentOrder()
{
	currentIndex = 0;
	int id;
	int quantity;
	OnSale_t* onSaleProduct;
	printf("��������Ʒid:");
	scanf("%d", &id);
	if (0 == findIndexByID_d(productDat, id, &onSaleProduct)) {
		printf("�����ڵ���Ʒid\n");
	}else{
		printf("�������������:");
		scanf("%d", &quantity);
		if (quantity > onSaleProduct->allowance) {
			printf("��治�㣬�ѽ���Ʒȫ����ӣ������%d����Ʒ\n", onSaleProduct->allowance);
			quantity = onSaleProduct->allowance;
			onSaleProduct->allowance = 0;
		}else{
			onSaleProduct->allowance -= quantity;
			printf("��ӳɹ�");
		}
		for (int i = 0; i < currentIndex; i++) {
			if (id == currentOrder.items[i].product.id) {
				currentOrder.items[i].quantity = quantity;
			}else{
				currentOrder.items[i].quantity = quantity;
				currentOrder.items[i].product.id = onSaleProduct->product.id;
				currentOrder.items[i].product.price = onSaleProduct->product.price;
				strcpy(currentOrder.items[i].product.name, onSaleProduct->product.name);
				strcpy(currentOrder.items[i].product.supplier, onSaleProduct->product.supplier);
			}
		}
	}
	
	
}

/**
*  @brief: ɾ����ǰ��������Ʒ
*
*/
void delProductFromCurrentOrder()
{
	PASS;
}

/**
*  @brief: ���ĵ�ǰ��������Ʒ����
*
*/
void modifyProductFromCurrentOrder()
{
	PASS;
}

/**
*  @brief: �����ܼ�
*
*/
void calTurnOverInCurrentOrder()
{
	PASS;
}

/**
*  @brief: ��������
*
*/
void submitCurrentOrder()
{
	PASS;
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

static int getNormalChoice()
{
	int choice;

	do
	{
		showCurrentOrderMenu();
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);
}