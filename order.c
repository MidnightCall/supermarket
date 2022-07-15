#include "order.h"
#include "helpfulFunction.h"


extern Node_t* orderDat, * productDat;
extern Config_t configDat;
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

void addProductToCurrentOrder()
{
	int id;
	int quantity;
	bool flag = false;
	OnSale_t* onSaleProduct;
	currentIndex = 0;

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
}

/**
*  @brief: ɾ����ǰ��������Ʒ
*
*/
void delProductFromCurrentOrder()
{
	int id;
	int pos;

	printf("�������ɾ������Ʒid:");
	scanf("%d", &id);
	if (0 != (findProduct(productDat, id))) {
		del(productDat, pos);
		printf("ɾ���ɹ�\n");
		currentIndex--;
	}else {
		printf("������idΪ%d����Ʒ\n", id);
	}
}

/**
*  @brief: ���ĵ�ǰ��������Ʒ����
*
*/
void modifyProductFromCurrentOrder()
{
	int id;
	int quantity;
	bool flag = false;
	OnSale_t* onSaleProduct;

	printf("��������Ҫ���ĵ���Ʒid:");
	scanf("%d", &quantity);
	for (int i = 0; i < currentIndex; i++) {
		if (currentOrder.items[i].product.id == id) {
			printf("������������Ҫ���������:");
			scanf("%d", &quantity);
			currentOrder.items[i].quantity = quantity;
			flag = true;
			break;
		}
	}
	if (flag == false) {
		printf("��ǰ������û��idΪ%d����Ʒ\n");
	}
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

	printf("�ܼ�Ϊ%.2f", sum);
}

/**
*  @brief: ��������
*
*/
void submitCurrentOrder()
{
	Order_t* tempOrder = (Order_t*)malloc(sizeof(Order_t));
	tempOrder->id = ++configDat.maxId_Order;
	for (int i = 0; i < currentIndex; i++) {
		tempOrder->items[i].quantity = currentOrder.items[i].quantity;
		tempOrder->items[i].product.id = currentOrder.items[i].product.id;
		tempOrder->items[i].product.price = currentOrder.items[i].product.price;
		strcpy(tempOrder->items[i].product.name, tempOrder->items->product.name);
		strcpy(tempOrder->items[i].product.supplier, tempOrder->items->product.supplier);
	}
	printf("�ѳɹ��ύ.\n");
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

	return choice;
}