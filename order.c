#include "order.h"
#include "helpfulFunction.h"
#include "typeCollection.h"
#include <time.h>


extern Node_t* orderDat, * productDat;
extern Config_t configDat;
extern User_t currentUser;
int currentIndex = 0;
Order_t currentOrder;

/* �ֲ�����ģ�� */
static int getChoice();
static int getNormalChoice();
static float calTurnOverInCurrentOrder(void);

/**
*  @brief: ���ж���ϵͳ
*
*/
void runOrderSystem()
{
	while (1)
	{
		int choice = getChoice();

		switch (choice)
		{
		default:
			return;
		case 1:
			displayOrder(true);
			PAUSE;
			break;
		case 2:
			queryOrder();
			break;
		case 3:
			calTurnover();
			break;
		}
	}
}

/**
*  @brief: ���е�ǰ��������ģ�� (������Աʹ��)
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
			showTurnOverInCurrentOrder();
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
void displayOrder(bool showSum)
{
	printf("�������������������Щ�������������������������������Ϣ�Щ��������������Щ���������������������������\n");
	printf("�� %7s�� %20s�� %6s�� %12s��\n", "������", "����ʱ��", "������", "�ܽ��");
	printf("�������������������੤�����������������������������������������੤�������������੤��������������������������\n");
	printList(orderDat, printOrderInfo, false);
	if (!showSum)
		printf("�������������������ة������������������������������������������ة��������������ة���������������������������\n");
	else
	{
		printf("�������������������੤�����������������������������������������ة��������������ة���������������������������\n");
		printf("��  �ϼ�  �� %42.2f��\n", calTurnover());
		printf("�������������������ة���������������������������������������������������������������������������������������\n");
	}
	return;
}

/**
*  @brief: ��ѯ������Ϣ
*
*/
void queryOrder(void)
{
	displayOrder(false);

	unsigned int id;
	Order_t* order = NULL;
	printf("���������ѯ�Ķ��� ID: ");
	scanf("%u", &id);
	if (0 != findIndexByID_d(orderDat, id, &order)) 
	{
		char* timeStr = timeConv(order->time);
		printf("���������������������������Щ������������������������Щ������������������������Щ�������ϸ��Ϣ�����������������������Щ���������������������������������������������������������\n");
		printf("��   ������   ��   %07u  ��   ������   ��  %05u  ��   ����ʱ��   ��    %20s    ��\n", order->id, order->operatorId, timeStr);
		printf("�������������������Щ������ة������������������������ة������������������������ة������������������ة������������������Щ��������ة������������Щ��������������Щ���������������������������\n");
		printf("�� %7s�� %48s�� %10s�� %6s�� %12s��\n", "��Ʒ ID", "��Ʒ��", "����", "����", "�ܼ�");
		printf("�������������������੤�������������������������������������������������������������������������������������������������੤���������������������੤�������������੤��������������������������\n");
		printOrderDetail(order);
		printf("�������������������ة������Щ������������������������������������������������������������������������������������������ة����������������������ة��������������ة���������������������������\n");
		printf("��    �ϼ�    �� %78.2f��\n", order->total);
		printf("���������������������������ة���������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
		free(timeStr); /* timeConv ���ص��������һ����ʱ�ڴ�ռ䣬�����˾��ͷ� */
	}
	else 
	{
		printf("������ ID Ϊ %u �ŵĶ���\n", id);
	}
	PAUSE;
	return;
}

/**
*  @brief: ������Ӫҵ��
*
*/
float calTurnover()
{
	float sum = 0.0f;
	Node_t* allOrder = orderDat;
	
	if (NULL == orderDat->next)
	{
		return 0.0f;
	}

	allOrder = orderDat->next;
	while (allOrder != NULL)
	{
		sum += *(float*)((char*)allOrder->data + 8804);
		allOrder = allOrder->next;
	}
	return sum;
}

void addProductToCurrentOrder(void)
{
	unsigned int id;
	int quantity;
	bool flag = false;
	OnSale_t* onSaleProduct = NULL;

	id = getAnNonNegativeDigit("��Ʒ ID");
	if (0 == findIndexByID_d(productDat, id, &onSaleProduct)) {
		printf("�����ڵ���Ʒ ID.\n");
		
	} else {
		quantity = getAnNonNegativeDigit("�������");
		if (0 == quantity)
		{
			printf("�Ƿ����룬���������롣");
			PAUSE;
			return;
		}
		if (quantity > onSaleProduct->allowance) {
			if (onSaleProduct->allowance > 0) {
				printf("�������㣬�ѽ���Ʒȫ����ӣ������ %d ����Ʒ\n", onSaleProduct->allowance);
				quantity = onSaleProduct->allowance;
				onSaleProduct->allowance = 0;
			} else {
				printf("����Ʒ������.\n");
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
			currentOrder.items[currentIndex].product.type = onSaleProduct->product.type;
			strcpy(currentOrder.items[currentIndex].product.name, onSaleProduct->product.name);
			strcpy(currentOrder.items[currentIndex++].product.supplier, onSaleProduct->product.supplier);
		}
		
	}
	PAUSE;
	return;
}

void delProductFromCurrentOrder()
{
	int id;
	int pos;
	OnSale_t* onSaleProduct = NULL;

	id = getAnNonNegativeDigit("��ɾ������Ʒid");
	if (0 != (pos = findProduct_d(productDat, id, &onSaleProduct))) {
		onSaleProduct->allowance += currentOrder.items[currentIndex - 1].quantity;
		printf("ɾ���ɹ�\n");
		currentIndex--;
	}else {
		printf("������ ID Ϊ %d ����Ʒ��\n", id);
	}
	PAUSE;
	return;
}

void modifyProductFromCurrentOrder(void)
{
	int id;
	int quantity;
	bool flag = false;
	OnSale_t* onSaleProduct = NULL;

	id = getAnNonNegativeDigit("��Ҫ���ĵ���Ʒid");
	for (int i = 0; i < currentIndex; i++) {
		if (currentOrder.items[i].product.id == id) {
			quantity = getAnNonNegativeDigit("��Ҫ���������");
			currentOrder.items[i].quantity = quantity;
			flag = true;
			printf("������ɡ�");
			break;
		}
	}
	if (flag == false) {
		printf("��ǰ������û�� ID Ϊ %d ����Ʒ��", id);
	}
	PAUSE;
	return;
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
	showTurnOverInCurrentOrder();
	return;
}

void showTurnOverInCurrentOrder(void)
{
	printf("�ܼ�Ϊ ��%.2f.\n", calTurnOverInCurrentOrder());
	PAUSE;
}

void submitCurrentOrder()
{
	Order_t* tempOrder = (Order_t*)malloc(sizeof(Order_t));
	assert(tempOrder != NULL);

	tempOrder->id = ++configDat.maxId_Order;
	for (int i = 0; i < currentIndex; i++) {
		tempOrder->items[i].quantity = currentOrder.items[i].quantity;
		tempOrder->items[i].product.id = currentOrder.items[i].product.id;
		tempOrder->items[i].product.price = currentOrder.items[i].product.price;
		tempOrder->items[i].product.type = currentOrder.items[i].product.type;
		strcpy(tempOrder->items[i].product.name, currentOrder.items[i].product.name);
		strcpy(tempOrder->items[i].product.supplier, currentOrder.items[i].product.supplier);
	}

	tempOrder->total = calTurnOverInCurrentOrder();
	tempOrder->time = time(NULL);
	tempOrder->operatorId = currentUser.id;
	tempOrder->items[currentIndex].product.id = 0; /* ����������ָʾ */
	insert(orderDat, END, tempOrder);
	currentIndex = 0;
	printf("�ѳɹ��ύ��\n");
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
	flush();

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
	} while (choice > 7 || choice < 1);
	flush();

	return choice;
}

static float calTurnOverInCurrentOrder(void)
{
	float sum = 0;

	for (int i = 0; i < currentIndex; i++) {
		sum += currentOrder.items[i].quantity * currentOrder.items[i].product.price;
	}

	return sum;
}