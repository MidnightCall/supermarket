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

/* 局部函数模型 */
static int getChoice();
static int getNormalChoice();
static float calTurnOverInCurrentOrder(void);
static float calProfitInCurrentOrder(void);

/**
*  @brief 运行订单系统
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
*  @brief 运行当前订单管理模块 (供收银员使用)
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
*  @brief 显示所有订单信息
*
*/
void displayOrder(bool showSum)
{
	if (NULL == orderDat->next)
	{
		printf("当前没有已交付的订单。");
		PAUSE;
		return;
	}

	printf("┌────────┬─────────────订单信息┬───────┬─────────────┐\n");
	printf("│ %7s│ %20s│ %6s│ %12s│\n", "订单号", "交付时间", "操作人", "总金额");
	printf("├────────┼─────────────────────┼───────┼─────────────┤\n");
	printList(orderDat, printOrderInfo, false);
	if (!showSum)
		printf("└────────┴─────────────────────┴───────┴─────────────┘\n");
	else
	{
		printf("├────────┼─────────────────────┴───────┴─────────────┤\n");
		printf("│  合计  │ %42.2f│\n", calTurnover());
		printf("├────────┼───────────────────────────────────────────┤\n");
		printf("│ 总利润 │ %42.2f│\n", calProfit());
		printf("└────────┴───────────────────────────────────────────┘\n");
	}
	return;
}

/**
*  @brief: 查询订单信息
*
*/
void queryOrder(void)
{
	if (NULL == orderDat->next)
	{
		printf("当前没有已交付的订单。");
		PAUSE;
		return;
	}

	displayOrder(false);

	unsigned int id;
	Order_t* order = NULL;
	id = getNonNegativeNumber("待查询的订单 ID");
	if (0 != findIndexByID_d(orderDat, id, &order)) 
	{
		char* timeStr = timeConv(order->time);
		printf("┌────────────┬────────────┬────────────┬─订单详细信息───────────┬────────────────────────────┐\n");
		printf("│   订单号   │   %07u  │   处理人   │  %05u  │   交付时间   │    %20s    │\n", order->id, order->operatorId, timeStr);
		printf("├────────┬───┴────────────┴────────────┴─────────┴─────────┬────┴──────┬───────┬─────────────┤\n");
		printf("│ %7s│ %48s│ %10s│ %6s│ %12s│\n", "商品 ID", "商品名", "单价", "数量", "总价");
		printf("├────────┼─────────────────────────────────────────────────┼───────────┼───────┼─────────────┤\n");
		printOrderDetail(order);
		printf("├────────┴───┬─────────────────────────────────────────────┴───────────┴───────┴─────────────┤\n");
		printf("│    合计    │ %78.2f│\n", order->total);
		printf("└────────────┴───────────────────────────────────────────────────────────────────────────────┘\n");
		free(timeStr); /* timeConv 返回的是申请的一块临时内存空间，用完了就释放 */
	}
	else 
	{
		printf("不存在 ID 为 %u 号的订单\n", id);
	}
	PAUSE;
	return;
}

void queryOrderByTime(void) /* 其实只能查询月范围内的 */
{
	if (NULL == orderDat->next)
	{
		printf("当前没有已交付的订单。");
		PAUSE;
		return;
	}

	char monthInfo[10]; /* 要查询的时间段 */
	printf("请输入要查询的月份 [格式: 20xx-xx]: ");
	stringGet(monthInfo, 10);

	if (monthInfo[0] != '2' || monthInfo[1] != '0' || !isdigit(monthInfo[2])
		|| !isdigit(monthInfo[3]) || monthInfo[4] != '-' || !isdigit(monthInfo[5])
		|| !isdigit(monthInfo[6]) || monthInfo[5] - '0' > 1 
		|| (monthInfo[5] == '1' && monthInfo[6] - '0' > 2)
		|| (monthInfo[5] == '0' && monthInfo[6] == '0')) /* 字符串格式检查 */
	{
		printf("输入的月份格式有误。");
		PAUSE;
		return;
	}

	char year[5], month[3];
	int iYear, iMonth;
	time_t leftBorder, rightBorder;
	strncpy(year, monthInfo, 4);
	year[4] = '\0'; /* strncpy 似乎不会自动加上终止符，这里手动加一下 */
	strncpy(month, monthInfo + 5, 2);
	month[2] = '\0';

	iYear = atoi(year);
	iMonth = atoi(month);

	struct tm targetInfo = { 0, 0, 0, 1, iMonth - 1, iYear - 1900 };

	leftBorder = mktime(&targetInfo); /* 计算下界 */

	++iMonth;
	if (iMonth == 12) /* 跨年 */
	{
		++iYear;
		iMonth = 1;
	}
	targetInfo.tm_year = iYear - 1900;
	targetInfo.tm_mon = iMonth - 1;
	rightBorder = mktime(&targetInfo); /* 计算上界 */

	if (-1 == leftBorder || -1 == rightBorder) /* 防不胜防 */
	{
		printf("时间转换失败，请确认字符串格式是否正确。");
		PAUSE;
		return;
	}
	
	/* 开始遍历 */
	Node_t* tHead = orderDat->next; /* 函数开头已经检查过是否为空，这里直接指向第一个数据点 */
	float monthlySum = 0, monthlyProfit = 0; /* 月度的营业额和利润就在这里另算 */

	printf("┌────────┬─────────────订单信息┬───────┬─────────────┐\n");
	printf("│ %7s│ %20s│ %6s│ %12s│\n", "订单号", "交付时间", "操作人", "总金额");
	printf("├────────┼─────────────────────┼───────┼─────────────┤\n");

	while (tHead != NULL)
	{
		time_t timeData = *(time_t*)((char*)tHead->data + 4616); /* 比预想的多了 4 个字节... */
		//printf("%lld, %lld, %lld", leftBorder, timeData, rightBorder);
		if (timeData >= leftBorder && timeData < rightBorder) /* 左闭右开 */
		{
			monthlySum += *(float*)((char*)tHead->data + 4604); /* 工作正常 */
			monthlyProfit += *(float*)((char*)tHead->data + 4608);
			printOrderInfo(tHead->data);
		}
		tHead = tHead->next;
	}

	printf("├────────┼─────────────────────┴───────┴─────────────┤\n");
	printf("│  合计  │ %42.2f│\n", monthlySum);
	printf("├────────┼───────────────────────────────────────────┤\n");
	printf("│ 总利润 │ %42.2f│\n", monthlyProfit);
	printf("└────────┴───────────────────────────────────────────┘\n");

	PAUSE;
	return;
}

/**
*  @brief: 计算总营业额
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
		sum += *(float*)((char*)allOrder->data + 4604); /* 一百个商品和一个 ID 占的字节数 */
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
		sum += *(float*)((char*)allOrder->data + 4608); /* 一百个商品和一个 uint 一个 float 占的字节数 */
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

	id = getNonNegativeNumber("商品 ID");
	if (0 == findIndexByID_d(productDat, id, &onSaleProduct)) 
	{
		printf("不存在的商品 ID.\n");
	}
	else
	{
		quantity = getNonNegativeNumber("添加数量");
		if (0 == quantity)
		{
			printf("非法输入，请重新输入。");
			PAUSE;
			return;
		}

		if (quantity > onSaleProduct->allowance)
		{
			if (onSaleProduct->allowance > 0)
			{
				printf("余量不足，已将商品全部添加，共添加 %d 件商品\n", onSaleProduct->allowance);
				quantity = onSaleProduct->allowance;
				onSaleProduct->allowance = 0; 
			}
			else
			{
				printf("该商品已售罄。");
			}
		}
		else
		{
			onSaleProduct->allowance -= quantity; /* 这里商品就已经从货架上拿下来了 */
			printf("添加成功。");
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

	/* 策略：把要删除的商品信息移到数组尾，然后让 currentIndex-- */
	/* 权宜之计 ... */

	id = getNonNegativeNumber("待删除的商品 ID");
	for (int i = 0; i < currentIndex; ++i)
	{
		if (currentOrder.items[i].product.id == id) /* 订单内存在这个物品 */
		{
			flag = true;
			findProduct_d(productDat, id, &onSaleProduct);
			onSaleProduct->allowance += currentOrder.items[i].quantity; /* 更新货架数量信息 */
			pos = i;
			OrderItem_t tempOrderItem;
			memcpy(&tempOrderItem, &currentOrder.items[pos], sizeof(OrderItem_t)); /* 把要删除的信息放到临时变量里 */
			for (int j = pos; j < currentIndex - 1; ++j) /* 剩下的依次前移 */
			{
				memcpy(&currentOrder.items[j], &currentOrder.items[j + 1], sizeof(OrderItem_t));
			}
			memcpy(&currentOrder.items[currentIndex - 1], &tempOrderItem, sizeof(OrderItem_t)); /* 把要删除的节点放到末尾 */
			--currentIndex; /* 把末尾节点屏蔽掉 */
			printf("商品删除成功。");
		}
	}

	if (!flag)
	{
		printf("当前订单中没有 ID 为 %d 的商品。\n", id);
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

	id = getNonNegativeNumber("需要更改的商品 ID");
	for (int i = 0; i < currentIndex; i++) {
		if (currentOrder.items[i].product.id == id) 
		{
			findProduct_d(productDat, id, &onSaleProduct); /* 找到对应的商品 */
			quantity = getNonNegativeNumber("需要购买的数量");
			if (0 == quantity)
			{
				printf("非法输入，请重新输入。");
				PAUSE;
				return;
			}
			if (quantity <= currentOrder.items[i].quantity) /* 新数量比原数量小 */
				onSaleProduct->allowance += (currentOrder.items[i].quantity - quantity); /* 把多出来的部分加回到货架上去 */
			else /* 新数量比原数量大 */
			{
				if (quantity > currentOrder.items[i].quantity + onSaleProduct->allowance) /* 新数量比已经加入订单的和货架上剩下的都多 */
				{
					printf("余量不足，已将商品全部添加，共添加 %d 件商品。\n", currentOrder.items[i].quantity + onSaleProduct->allowance);
					quantity = onSaleProduct->allowance + currentOrder.items[i].quantity;
					onSaleProduct->allowance = 0;
				}
				else
				{
					onSaleProduct->allowance -= (quantity - currentOrder.items[i].quantity); /* 多了几件就从货架上拿几件 */
				}
			}
			currentOrder.items[i].quantity = quantity;
			flag = true;
			printf("更改完成。");
			break;
		}
	}
	if (flag == false)
	{
		printf("当前订单中没有 ID 为 %d 的商品。", id);
	}
	PAUSE;
	return;
}

void showCurrentOrderInfo()
{
	printf("┌────────┬──────────────────────────────当前订单信息───────┬───────────┬───────┬───────────┐\n");
	printf("│ %7s│ %48s│ %10s│ %6s│ %10s│\n", "商品 ID", "商品名", "单价", "数量", "总价");
	printf("├────────┼─────────────────────────────────────────────────┼───────────┼───────┼───────────┤\n");
	for (int i = 0; i < currentIndex; i++) 
	{
		printf("│ %7u│ %48s│ %10.2f│ %6u│ %10.2f│\n", currentOrder.items[i].product.id,
			currentOrder.items[i].product.name, currentOrder.items[i].product.price,
			currentOrder.items[i].quantity, currentOrder.items[i].quantity * currentOrder.items[i].product.price);
	}
	printf("└────────┴─────────────────────────────────────────────────┴───────────┴───────┴───────────┘\n");
	
	showTurnOverInCurrentOrder();
	return;
}

void showTurnOverInCurrentOrder(void)
{
	printf("合计为 ￥%.2f.\n", calTurnOverInCurrentOrder());
}

void submitCurrentOrder()
{
	if (0 == currentIndex) /* 如果当前订单为空 */
	{
		printf("当前订单为空，交付失败。");
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
	tempOrder->items[currentIndex].product.id = 0; /* 用来给遍历指示 */
	insert(orderDat, 0, tempOrder); /* 这里改为插到开头，正好以时间倒序显示 */
	currentIndex = 0;
	printf("已成功提交。");
	PAUSE;
	return;
}

/* 局部函数实现 */
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