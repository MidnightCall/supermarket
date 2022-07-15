#include "order.h"
#include "helpfulFunction.h"


extern Node_t* orderDat, * productDat;
extern Config_t configDat;
extern User_t currentUser;
int currentIndex = 0;
Order_t currentOrder;

/* 局部函数模型 */
static int getChoice();

/**
*  @brief: 运行订单系统
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
*  @brief: 运行当前订单管理模块 (供收银员使用)
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
*  @brief: 显示所有订单信息
*
*/
void displayOrder() 
{
	// 打印所有订单信息的操作
}

/**
*  @brief: 查询订单信息
*
*/
void queryOrder()
{
	int id;
	Order_t order;
	printf("请输入待查询的订单 ID: ");
	scanf("%d", &id);
	if (findIndexByID_d(orderDat, id, &order, sizeof(Order_t)) != 0/* 此处替换为查询上架商品的操作 */) {
		printOrderInfo(&order);
	}else {
		printf("不存在id为%d号的订单\n", id);
	}
}

/**
*  @brief: 计算总营业额
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

	printf("请输入商品 ID: ");
	scanf("%d", &id);
	if (0 == findIndexByID_d(productDat, id, &onSaleProduct)) {
		printf("不存在的商品 ID.\n");
	} else {
		printf("请输入添加数量: ");
		scanf("%d", &quantity);

		if (quantity > onSaleProduct->allowance) {
			printf("库存不足，已将商品全部添加，共添加 %d 件商品\n", onSaleProduct->allowance);
			quantity = onSaleProduct->allowance;
			onSaleProduct->allowance = 0;
		} else {
			onSaleProduct->allowance -= quantity;
			printf("添加成功");
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
*  @brief: 删除当前订单的商品
*
*/
void delProductFromCurrentOrder(void)
{
	int id;
	int pos;

	printf("请输入待删除的商品 ID: ");
	scanf("%d", &id);
	if (0 != (findProduct(productDat, id))) {
		del(productDat, pos);
		printf("删除成功\n");
		currentIndex--;
	}else {
		printf("不存在 ID 为 %d 的商品。\n", id);
	}
	PAUSE;
	return;
}

/**
*  @brief: 更改当前订单的商品数量
*
*/
void modifyProductFromCurrentOrder(void)
{
	int id;
	int quantity;
	bool flag = false;
	OnSale_t* onSaleProduct;

	printf("请输入需要更改的商品id:");
	scanf("%d", &quantity);
	for (int i = 0; i < currentIndex; i++) {
		if (currentOrder.items[i].product.id == id) {
			printf("请重新输入需要购买的数量: ");
			scanf("%d", &quantity);
			currentOrder.items[i].quantity = quantity;
			flag = true;
			break;
		}
	}
	if (flag == false) {
		printf("当前订单中没有 ID 为 %d 的商品。", id);
	}
	PAUSE;
	return;
}

/**
*  @brief: 计算总价
*
*/
void calTurnOverInCurrentOrder()
{
	float sum = 0;

	for (int i = 0; i < currentIndex; i++) {
		sum += currentOrder.items[i].quantity * currentOrder.items[i].product.price;
	}

	printf("总价为 %.2f", sum);
}

/**
*  @brief: 交付订单
*
*/
void submitCurrentOrder(void)
{
	Order_t* tempOrder = (Order_t*)malloc(sizeof(Order_t));
	if (NULL == tempOrder)
	{
		printf("订单节点初始化失败。");
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
	printf("已成功提交。");
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