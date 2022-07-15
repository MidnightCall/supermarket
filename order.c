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
	while (true)
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
			modifyProductFromCurrentOrder();
			break;
		case 4:
			calTurnOverInCurrentOrder();
			break;
		case 5:
			submitCurrentOrder();
			break;
		case 6:
			showCurrentOrderInfo();
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
	printf("���������ѯ�Ķ���id:");
	scanf("%d", &id);
	if (0 != findIndexByID_d(orderDat, id, &order, sizeof(Order_t))) {
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
			if (onSaleProduct->allowance > 0) {
				printf("�������㣬�ѽ���Ʒȫ����ӣ������%d����Ʒ\n", onSaleProduct->allowance);
				quantity = onSaleProduct->allowance;
				onSaleProduct->allowance = 0;
			}else{
				printf("����Ʒ������\n");
			}
		}else{
			onSaleProduct->allowance -= quantity;
			printf("��ӳɹ�\n");
		}
		for (int i = 0; i < currentIndex; i++) {
			if (id == currentOrder.items[i].product.id) {
				currentOrder.items[i].quantity += quantity;
				flag = true;
				break;
			}
		}
		if (flag == false) {
			currentOrder.items[currentIndex].quantity = quantity;
			currentOrder.items[currentIndex].product.id = id;
			currentOrder.items[currentIndex].product.price = onSaleProduct->product.price;
			strcpy(currentOrder.items[currentIndex].product.name, onSaleProduct->product.name);
			strcpy(currentOrder.items[currentIndex++].product.supplier, onSaleProduct->product.supplier);
		}
		
	}
}

void delProductFromCurrentOrder()
{
	int id;
	int pos;
	OnSale_t* onSaleProduct = NULL;

	printf("�������ɾ������Ʒid:");
	scanf("%d", &id);
	if (0 != (pos = findProduct_d(productDat, id, &onSaleProduct))) {
		onSaleProduct->allowance += currentOrder.items[currentIndex - 1].quantity;
		printf("ɾ���ɹ�\n");
		currentIndex--;
	}else {
		printf("������idΪ%d����Ʒ\n", id);
	}
}

void modifyProductFromCurrentOrder()
{
	int id;
	int quantity;
	bool flag = false;
	OnSale_t* onSaleProduct;

	printf("��������Ҫ���ĵ���Ʒid:");
	scanf("%d", &id);
	for (int i = 0; i < currentIndex; i++) {
		if (currentOrder.items[i].product.id == id) {
			printf("������������Ҫ���������:");
			scanf("%d", &quantity);
			currentOrder.items[i].quantity = quantity;
			flag = true;
			printf("�������\n");
			break;
		}
	}
	if (flag == false) {
		printf("��ǰ������û��idΪ%d����Ʒ\n");
	}
}

void showCurrentOrderInfo()
{
	printf("��Ʒ�嵥: \n");
	printf("��Ʒid\t��Ʒ��\t����\t����\t�ܼ�\n");
	for (int i = 0; i < currentIndex; i++) {
		printf("%d\t%s\t%.2f\t%d\t%.2f\n", currentOrder.items[i].product.id,
			currentOrder.items[i].product.name, currentOrder.items[i].product.price,
			currentOrder.items[i].quantity, currentOrder.items[i].quantity * currentOrder.items[i].product.price);
	}
	calTurnOverInCurrentOrder();
}

void calTurnOverInCurrentOrder()
{
	float sum = 0;

	for (int i = 0; i < currentIndex; i++) {
		sum += currentOrder.items[i].quantity * currentOrder.items[i].product.price;
	}

	printf("�ܼ�Ϊ%.2f\n", sum);
}

void submitCurrentOrder()
{
	Order_t* tempOrder = (Order_t*)malloc(sizeof(Order_t));
	Order_t* endOrder = (Order_t*)malloc(sizeof(Order_t));
	tempOrder->id = ++configDat.maxId_Order;
	endOrder->id = 0;
	for (int i = 0; i < currentIndex; i++) {
		tempOrder->items[i].quantity = currentOrder.items[i].quantity;
		tempOrder->items[i].product.id = currentOrder.items[i].product.id;
		tempOrder->items[i].product.price = currentOrder.items[i].product.price;
		strcpy(tempOrder->items[i].product.name, tempOrder->items->product.name);
		strcpy(tempOrder->items[i].product.supplier, tempOrder->items->product.supplier);
	}
	insert(orderDat, END, tempOrder);
	insert(orderDat, END, endOrder);/* ����ĩβ�ж� */
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
	} while (choice > 7 || choice < 1);

	return choice;
}