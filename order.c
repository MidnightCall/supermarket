#include "order.h"
#include "helpfulFunction.h"


extern Node_t* orderDat, * productDat;
extern Config_t configDat;
extern User_t currentUser;
int currentIndex = 0;
Order_t currentOrder;

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
*  @brief: ���е�ǰ��������ģ�� (������Աʹ��)
*
*/
void runNormalUserOrderSystem()
{
	while (1)
	{
		int choice = getNormalChoice();

		switch (choice)
		{
		default:
			return;
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
	printf("���������ѯ�Ķ��� ID: ");
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

void addProductToCurrentOrder(void)
{
	int id;
	int quantity;
	bool flag = false;
	OnSale_t* onSaleProduct = NULL;
	currentIndex = 0;

	printf("��������Ʒ ID: ");
	scanf("%d", &id);
	if (0 == findIndexByID_d(productDat, id, &onSaleProduct)) {
		printf("�����ڵ���Ʒ ID.\n");
	} else {
		printf("�������������: ");
		scanf("%d", &quantity);

		if (quantity > onSaleProduct->allowance) {
			printf("��治�㣬�ѽ���Ʒȫ����ӣ������ %d ����Ʒ\n", onSaleProduct->allowance);
			quantity = onSaleProduct->allowance;
			onSaleProduct->allowance = 0;
		} else {
			onSaleProduct->allowance -= quantity;
			printf("��ӳɹ�");
		}
		for (int i = 0; i < currentIndex; i++) {
			if (id == currentOrder.items[i].product.id) {
				currentOrder.items[i].quantity = quantity;
				flag = true;
				break;
			}
		}
		if (flag == false) {
			OrderItem_t orderItem;
			orderItem.quantity = quantity;
			orderItem.product.id = id;
			strcpy(orderItem.product.name, onSaleProduct->product.name);
			strcpy(orderItem.product.supplier, onSaleProduct->product.supplier);
			currentOrder.items[currentIndex++] = orderItem;
		}
		
	}
	PAUSE;
	return;
}

/**
*  @brief: ɾ����ǰ��������Ʒ
*
*/
void delProductFromCurrentOrder(void)
{
	int id;
	int pos;

	printf("�������ɾ������Ʒ ID: ");
	scanf("%d", &id);
	if (0 != (findProduct(productDat, id))) {
		del(productDat, pos);
		printf("ɾ���ɹ�\n");
		currentIndex--;
	}else {
		printf("������ ID Ϊ %d ����Ʒ��\n", id);
	}
	PAUSE;
	return;
}

/**
*  @brief: ���ĵ�ǰ��������Ʒ����
*
*/
void modifyProductFromCurrentOrder(void)
{
	int id;
	int quantity;
	bool flag = false;
	OnSale_t* onSaleProduct;

	printf("��������Ҫ���ĵ���Ʒid:");
	scanf("%d", &quantity);
	for (int i = 0; i < currentIndex; i++) {
		if (currentOrder.items[i].product.id == id) {
			printf("������������Ҫ���������: ");
			scanf("%d", &quantity);
			currentOrder.items[i].quantity = quantity;
			flag = true;
			break;
		}
	}
	if (flag == false) {
		printf("��ǰ������û�� ID Ϊ %d ����Ʒ��", id);
	}
	PAUSE;
	return;
}

/**
*  @brief: �����ܼ�
*
*/
void calTurnOverInCurrentOrder()
{
	float sum = 0;

	for (int i = 0; i < currentIndex; i++) {
		sum += currentOrder.items[i].quantity * currentOrder.items[i].product.price;
	}

	printf("�ܼ�Ϊ %.2f", sum);
}

/**
*  @brief: ��������
*
*/
void submitCurrentOrder(void)
{
	Order_t* tempOrder = (Order_t*)malloc(sizeof(Order_t));
	if (NULL == tempOrder)
	{
		printf("�����ڵ��ʼ��ʧ�ܡ�");
		PAUSE;
		exit(0);
	}

	tempOrder->id = ++configDat.maxId_Order;
	for (int i = 0; i < currentIndex; i++) {
		tempOrder->items[i].quantity = currentOrder.items[i].quantity;
		tempOrder->items[i].product.id = currentOrder.items[i].product.id;
		tempOrder->items[i].product.price = currentOrder.items[i].product.price;
		strcpy(tempOrder->items[i].product.name, tempOrder->items->product.name);
		strcpy(tempOrder->items[i].product.supplier, tempOrder->items->product.supplier);
	}
	printf("�ѳɹ��ύ��");
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
		showOrderBusinessMenu();
		HINT;
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);

	return choice;
}

static int getNormalChoice()
{
	int choice = 0;
	showTitle(currentUser);
	do
	{
		showCurrentOrderMenu();
		HINT;
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);

	return choice;
}