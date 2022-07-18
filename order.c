/*****************************************************************//**
 * \file   order.c
 * \brief  
 * 
 * \author East Monster
 * \date   July 2022
 *********************************************************************/
#include "order.h"
#include "helpfulFunction.h"
#include "onSaleProduct.h"
#include "typeCollection.h"
#include <time.h>
#include <ctype.h>
#include <stdio.h>


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
*  @brief ���ж���ϵͳ
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
			queryOrderByTime();
			break;
		}
	}
}

/**
*  @brief ���е�ǰ��������ģ�� (������Աʹ��)
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
			submitCurrentOrder();
			break;
		case 5:
			showCurrentOrderInfo();
			PAUSE;
			break;
		}
	}
	
}

/**
*  @brief ��ʾ���ж�����Ϣ
*
*/
void displayOrder(bool showSum)
{
	if (NULL == orderDat->next)
	{
		printf("��ǰû���ѽ����Ķ�����");
		PAUSE;
		return;
	}

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
	if (NULL == orderDat->next)
	{
		printf("��ǰû���ѽ����Ķ�����");
		PAUSE;
		return;
	}

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

void queryOrderByTime(void) /* ��ʵֻ�ܲ�ѯ�·�Χ�ڵ� */
{
	if (NULL == orderDat->next)
	{
		printf("��ǰû���ѽ����Ķ�����");
		PAUSE;
		return;
	}

	char monthInfo[10]; /* Ҫ��ѯ��ʱ��� */
	printf("������Ҫ��ѯ���·� [��ʽ: 20xx-xx]: ");
	stringGet(monthInfo, 10);

	if (monthInfo[0] != '2' || monthInfo[1] != '0' || !isdigit(monthInfo[2])
		|| !isdigit(monthInfo[3]) || monthInfo[4] != '-' || !isdigit(monthInfo[5])
		|| !isdigit(monthInfo[6]) || monthInfo[5] - '0' > 1 
		|| (monthInfo[5] == '1' && monthInfo[6] - '0' > 2)
		|| (monthInfo[5] == '0' && monthInfo[6] == '0')) /* �ַ�����ʽ��� */
	{
		printf("������·ݸ�ʽ����");
		PAUSE;
		return;
	}

	char year[5], month[3];
	int iYear, iMonth;
	time_t leftBorder, rightBorder;
	strncpy(year, monthInfo, 4);
	year[4] = '\0'; /* strncpy �ƺ������Զ�������ֹ���������ֶ���һ�� */
	strncpy(month, monthInfo + 5, 2);
	month[2] = '\0';

	iYear = atoi(year);
	iMonth = atoi(month);

	struct tm targetInfo = { 0, 0, 0, 1, iMonth - 1, iYear - 1900 };

	leftBorder = mktime(&targetInfo); /* �����½� */

	++iMonth;
	if (iMonth == 12) /* ���� */
	{
		++iYear;
		iMonth = 1;
	}
	targetInfo.tm_year = iYear - 1900;
	targetInfo.tm_mon = iMonth - 1;
	rightBorder = mktime(&targetInfo); /* �����Ͻ� */

	if (-1 == leftBorder || -1 == rightBorder) /* ����ʤ�� */
	{
		printf("ʱ��ת��ʧ�ܣ���ȷ���ַ�����ʽ�Ƿ���ȷ��");
		PAUSE;
		return;
	}
	
	/* ��ʼ���� */
	Node_t* tHead = orderDat->next; /* ������ͷ�Ѿ������Ƿ�Ϊ�գ�����ֱ��ָ���һ�����ݵ� */
	float monthlySum = 0, monthlyProfit = 0; /* �¶ȵ�Ӫҵ������������������ */

	printf("�������������������Щ�������������������������������Ϣ�Щ��������������Щ���������������������������\n");
	printf("�� %7s�� %20s�� %6s�� %12s��\n", "������", "����ʱ��", "������", "�ܽ��");
	printf("�������������������੤�����������������������������������������੤�������������੤��������������������������\n");

	while (tHead != NULL)
	{
		time_t timeData = *(time_t*)((char*)tHead->data + 4616); /* ��Ԥ��Ķ��� 4 ���ֽ�... */
		//printf("%lld, %lld, %lld", leftBorder, timeData, rightBorder);
		if (timeData >= leftBorder && timeData < rightBorder) /* ����ҿ� */
		{
			monthlySum += *(float*)((char*)tHead->data + 4604); /* �������� */
			monthlyProfit += *(float*)((char*)tHead->data + 4608);
			printOrderInfo(tHead->data);
		}
		tHead = tHead->next;
	}

	printf("�������������������੤�����������������������������������������ة��������������ة���������������������������\n");
	printf("��  �ϼ�  �� %42.2f��\n", monthlySum);
	printf("�������������������੤��������������������������������������������������������������������������������������\n");
	printf("�� ������ �� %42.2f��\n", monthlyProfit);
	printf("�������������������ة���������������������������������������������������������������������������������������\n");

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
	displayOnSaleProduct();

	unsigned int id;
	int quantity;
	bool flag = false;
	OnSale_t* onSaleProduct = NULL;

	id = getNonNegativeNumber("��Ʒ ID");
	if (0 == findIndexByID_d(productDat, id, &onSaleProduct)) 
	{
		printf("�����ڵ���Ʒ ID.\n");
	}
	else
	{
		quantity = getNonNegativeNumber("�������");
		if (0 == quantity)
		{
			printf("�Ƿ����룬���������롣");
			PAUSE;
			return;
		}

		if (quantity > onSaleProduct->allowance)
		{
			if (onSaleProduct->allowance > 0)
			{
				printf("�������㣬�ѽ���Ʒȫ����ӣ������ %d ����Ʒ\n", onSaleProduct->allowance);
				quantity = onSaleProduct->allowance;
				onSaleProduct->allowance = 0; 
			}
			else
			{
				printf("����Ʒ��������");
			}
		}
		else
		{
			onSaleProduct->allowance -= quantity; /* ������Ʒ���Ѿ��ӻ������������� */
			printf("��ӳɹ���");
		}

		for (int i = 0; i < currentIndex; i++)
		{
			if (id == currentOrder.items[i].product.id)
			{
				currentOrder.items[i].quantity += quantity;
				flag = true;
				break;
			}
		}

		if (flag == false) {
			memcpy(&currentOrder.items[currentIndex], &onSaleProduct->product, sizeof(Product_t));
			currentOrder.items[currentIndex].quantity = quantity;
			++currentIndex;
		}
		
	}
	PAUSE;
	return;
}

void delProductFromCurrentOrder()
{
	showCurrentOrderInfo();

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
			printf("��Ʒɾ���ɹ���");
		}
	}

	if (!flag)
	{
		printf("��ǰ������û�� ID Ϊ %d ����Ʒ��\n", id);
	}

	PAUSE;
	return;
}

void modifyProductFromCurrentOrder(void)
{
	showCurrentOrderInfo();

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

void showCurrentOrderInfo()
{
	printf("�������������������Щ�������������������������������������������������������������ǰ������Ϣ���������������Щ����������������������Щ��������������Щ�����������������������\n");
	printf("�� %7s�� %48s�� %10s�� %6s�� %10s��\n", "��Ʒ ID", "��Ʒ��", "����", "����", "�ܼ�");
	printf("�������������������੤�������������������������������������������������������������������������������������������������੤���������������������੤�������������੤����������������������\n");
	for (int i = 0; i < currentIndex; i++) 
	{
		printf("�� %7u�� %48s�� %10.2f�� %6u�� %10.2f��\n", currentOrder.items[i].product.id,
			currentOrder.items[i].product.name, currentOrder.items[i].product.price,
			currentOrder.items[i].quantity, currentOrder.items[i].quantity * currentOrder.items[i].product.price);
	}
	printf("�������������������ة��������������������������������������������������������������������������������������������������ة����������������������ة��������������ة�����������������������\n");
	
	showTurnOverInCurrentOrder();
	return;
}

void showTurnOverInCurrentOrder(void)
{
	printf("�ϼ�Ϊ ��%.2f.\n", calTurnOverInCurrentOrder());
}

void submitCurrentOrder()
{
	if (0 == currentIndex) /* �����ǰ����Ϊ�� */
	{
		printf("��ǰ����Ϊ�գ�����ʧ�ܡ�");
		PAUSE;
		return;
	}

	Order_t* tempOrder = (Order_t*)malloc(sizeof(Order_t));
	assert(tempOrder != NULL);

	tempOrder->id = ++configDat.maxId_Order;

	for (int i = 0; i < currentIndex; i++) {
		memcpy(&tempOrder->items[i], &currentOrder.items[i], sizeof(OrderItem_t));
		/*tempOrder->items[i].quantity = currentOrder.items[i].quantity;
		tempOrder->items[i].product.id = currentOrder.items[i].product.id;
		tempOrder->items[i].product.price = currentOrder.items[i].product.price;
		tempOrder->items[i].product.purchase = currentOrder.items[i].product.purchase;
		tempOrder->items[i].product.type = currentOrder.items[i].product.type;
		strcpy(tempOrder->items[i].product.name, currentOrder.items[i].product.name);
		strcpy(tempOrder->items[i].product.supplier, currentOrder.items[i].product.supplier);*/
	}

	tempOrder->profit = calProfitInCurrentOrder();
	tempOrder->total = calTurnOverInCurrentOrder();
	tempOrder->time = time(NULL);
	tempOrder->operatorId = currentUser.id;
	tempOrder->items[currentIndex].product.id = 0; /* ����������ָʾ */
	insert(orderDat, 0, tempOrder); /* �����Ϊ�嵽��ͷ��������ʱ�䵹����ʾ */
	currentIndex = 0;
	printf("�ѳɹ��ύ��");
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
	} while (choice > 4 || choice < 1);
	flush();

	return choice;
}

static int getNormalChoice()
{
	int choice = 0;
	do
	{
		showTitle(currentUser);
		showCurrentOrderMenu();
		HINT;
		scanf("%d", &choice);
	} while (choice > 6 || choice < 1);
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