/*****************************************************************//**
 * \file   order.c
 * \brief  
 * 
 * \author East Monster
 * \date   July 2022
 *********************************************************************/
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
static float calProfitInCurrentOrder(void);

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
*  @brief ��ʾ���ж�����Ϣ
*
*/
void displayOrder(bool showSum) // UNDONE (������ѯ��Ʒ, ������Ʒ��Ϣ)
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
		printf("�������������������੤��������������������������������������������������������������������������������������\n");
		printf("�� ������ �� %42.2f��\n", calProfit());
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
	id = getNonNegativeNumber("����ѯ�Ķ��� ID");
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
		sum += *(float*)((char*)allOrder->data + 4604); /* һ�ٸ���Ʒ��һ�� ID ռ���ֽ��� */
		allOrder = allOrder->next;
	}
	return sum;
}

float calProfit()
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
		sum += *(float*)((char*)allOrder->data + 4608); /* һ�ٸ���Ʒ��һ�� uint һ�� float ռ���ֽ��� */
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

	id = getNonNegativeNumber("��Ʒ ID");
	if (0 == findIndexByID_d(productDat, id, &onSaleProduct)) {
		printf("�����ڵ���Ʒ ID.\n");
		
	} else {
		quantity = getNonNegativeNumber("�������");
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
		} else {
			onSaleProduct->allowance -= quantity; /* ������Ʒ���Ѿ��ӻ������������� */
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
			currentOrder.items[currentIndex].product.purchase = onSaleProduct->product.purchase;
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
	int pos = 0;
	bool flag = false;
	OnSale_t* onSaleProduct = NULL;

	/* ���ԣ���Ҫɾ������Ʒ��Ϣ�Ƶ�����β��Ȼ���� currentIndex-- */
	/* Ȩ��֮�� ... */

	id = getNonNegativeNumber("��ɾ������Ʒ ID");
	for (int i = 0; i < currentIndex; ++i)
	{
		if (currentOrder.items[i].product.id == id) /* �����ڴ��������Ʒ */
		{
			flag = true;
			findProduct_d(productDat, id, &onSaleProduct);
			onSaleProduct->allowance += currentOrder.items[i].quantity; /* ���»���������Ϣ */
			pos = i;
			OrderItem_t tempOrderItem;
			memcpy(&tempOrderItem, &currentOrder.items[pos], sizeof(OrderItem_t)); /* ��Ҫɾ������Ϣ�ŵ���ʱ������ */
			for (int j = pos; j < currentIndex - 1; ++j) /* ʣ�µ�����ǰ�� */
			{
				memcpy(&currentOrder.items[j], &currentOrder.items[j + 1], sizeof(OrderItem_t));
			}
			memcpy(&currentOrder.items[currentIndex - 1], &tempOrderItem, sizeof(OrderItem_t)); /* ��Ҫɾ���Ľڵ�ŵ�ĩβ */
			--currentIndex; /* ��ĩβ�ڵ����ε� */
		}
	}
	if (!flag)
	{
		printf("��ǰ������û�� ID Ϊ %d ����Ʒ��\n", id);
	}
	/*if (0 != (pos = findProduct_d(productDat, id, &onSaleProduct)))
	{

		// �������ֱ�Ӱ�ĩβ��ɾ�� (���ε�) ��
		onSaleProduct->allowance += currentOrder.items[currentIndex - 1].quantity;
		printf("ɾ���ɹ���");
		currentIndex--;
	}*/
	/*else
	{
		printf("��ǰ������û�� ID Ϊ %d ����Ʒ��\n", id);
	}*/
	PAUSE;
	return;
}

void modifyProductFromCurrentOrder(void)
{
	int id;
	int quantity;
	bool flag = false;
	OnSale_t* onSaleProduct = NULL;

	id = getNonNegativeNumber("��Ҫ���ĵ���Ʒ ID");
	for (int i = 0; i < currentIndex; i++) {
		if (currentOrder.items[i].product.id == id) 
		{
			findProduct_d(productDat, id, &onSaleProduct); /* �ҵ���Ӧ����Ʒ */
			quantity = getNonNegativeNumber("��Ҫ���������");
			if (0 == quantity)
			{
				printf("�Ƿ����룬���������롣");
				PAUSE;
				return;
			}
			if (quantity <= currentOrder.items[i].quantity) /* ��������ԭ����С */
				onSaleProduct->allowance += (currentOrder.items[i].quantity - quantity); /* �Ѷ�����Ĳ��ּӻص�������ȥ */
			else /* ��������ԭ������ */
			{
				if (quantity > currentOrder.items[i].quantity + onSaleProduct->allowance) /* ���������Ѿ����붩���ĺͻ�����ʣ�µĶ��� */
				{
					printf("�������㣬�ѽ���Ʒȫ����ӣ������ %d ����Ʒ��\n", currentOrder.items[i].quantity + onSaleProduct->allowance);
					quantity = onSaleProduct->allowance + currentOrder.items[i].quantity;
					onSaleProduct->allowance = 0;
				}
				else
				{
					onSaleProduct->allowance -= (quantity - currentOrder.items[i].quantity); /* ���˼����ʹӻ������ü��� */
				}
			}
			currentOrder.items[i].quantity = quantity;
			flag = true;
			printf("������ɡ�");
			break;
		}
	}
	if (flag == false)
	{
		printf("��ǰ������û�� ID Ϊ %d ����Ʒ��", id);
	}
	PAUSE;
	return;
}

void showCurrentOrderInfo() // TODO (�ĸ�ʽ)
{
	printf("��ƷID \t��Ʒ�� \t���� \t���� \t�ܼ�\n");
	for (int i = 0; i < currentIndex; i++) {
		printf("%d \t%s \t%.2f \t%d \t%.2f\n", currentOrder.items[i].product.id,
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
		tempOrder->items[i].product.purchase = currentOrder.items[i].product.purchase;
		tempOrder->items[i].product.type = currentOrder.items[i].product.type;
		strcpy(tempOrder->items[i].product.name, currentOrder.items[i].product.name);
		strcpy(tempOrder->items[i].product.supplier, currentOrder.items[i].product.supplier);
	}

	tempOrder->profit = calProfitInCurrentOrder();
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
	do
	{
		showTitle(currentUser);
		showOrderBusinessMenu();
		HINT;
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);
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

static float calProfitInCurrentOrder(void)
{
	float sum = 0;

	for (int i = 0; i < currentIndex; ++i)
	{
		sum += ((currentOrder.items[i].product.price
			- currentOrder.items[i].product.purchase)) * currentOrder.items[i].quantity;
	}

	return sum;
}