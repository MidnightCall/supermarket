#include "order.h"
#include "helpfulFunction.h"
#include "typeCollection.h"
#include <time.h>


extern Node_t* orderDat, * productDat;
extern Config_t configDat;
extern User_t currentUser;
int currentIndex = 0;
Order_t currentOrder;

/* 局部函数模型 */
static int getChoice();
static int getNormalChoice();
static float calTurnOverInCurrentOrder(void);

/**
*  @brief: 运行订单系统
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
*  @brief: 运行当前订单管理模块 (供收银员使用)
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
*  @brief: 显示所有订单信息
*
*/
void displayOrder(bool showSum)
{
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
	displayOrder(false);

	unsigned int id;
	Order_t* order = NULL;
	printf("请输入待查询的订单 ID: ");
	scanf("%u", &id);
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

	id = getAnNonNegativeDigit("商品 ID");
	if (0 == findIndexByID_d(productDat, id, &onSaleProduct)) {
		printf("不存在的商品 ID.\n");
		
	} else {
		quantity = getAnNonNegativeDigit("添加数量");
		if (0 == quantity)
		{
			printf("非法输入，请重新输入。");
			PAUSE;
			return;
		}
		if (quantity > onSaleProduct->allowance) {
			if (onSaleProduct->allowance > 0) {
				printf("余量不足，已将商品全部添加，共添加 %d 件商品\n", onSaleProduct->allowance);
				quantity = onSaleProduct->allowance;
				onSaleProduct->allowance = 0;
			} else {
				printf("该商品已售罄.\n");
			}
		}else{
			onSaleProduct->allowance -= quantity;
			printf("添加成功\n");
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

	id = getAnNonNegativeDigit("待删除的商品id");
	if (0 != (pos = findProduct_d(productDat, id, &onSaleProduct))) {
		onSaleProduct->allowance += currentOrder.items[currentIndex - 1].quantity;
		printf("删除成功\n");
		currentIndex--;
	}else {
		printf("不存在 ID 为 %d 的商品。\n", id);
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

	id = getAnNonNegativeDigit("需要更改的商品id");
	for (int i = 0; i < currentIndex; i++) {
		if (currentOrder.items[i].product.id == id) {
			quantity = getAnNonNegativeDigit("需要购买的数量");
			currentOrder.items[i].quantity = quantity;
			flag = true;
			printf("更改完成。");
			break;
		}
	}
	if (flag == false) {
		printf("当前订单中没有 ID 为 %d 的商品。", id);
	}
	PAUSE;
	return;
}

void showCurrentOrderInfo()
{
	printf("商品清单: \n");
	printf("商品id\t商品名\t单价\t数量\t总价\n");
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
	printf("总价为 ￥%.2f.\n", calTurnOverInCurrentOrder());
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
	tempOrder->items[currentIndex].product.id = 0; /* 用来给遍历指示 */
	insert(orderDat, END, tempOrder);
	currentIndex = 0;
	printf("已成功提交。\n");
	PAUSE;
	return;
}

/* 局部函数实现 */
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