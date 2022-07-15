#include "order.h"
#include "helpfulFunction.h"


extern Node_t* orderDat, * productDat;
extern Config_t configDat;
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
*  @brief: 运行当前订单管理模块(供收银员使用)
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
	printf("请输入待查询的订单id:");
	scanf("%d", &id);
	if (0 != findIndexByID_d(orderDat, id, &order, sizeof(Order_t))) {
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

void addProductToCurrentOrder()
{
	int id;
	int quantity;
	bool flag = false;
	OnSale_t* onSaleProduct;
	currentIndex = 0;

	printf("请输入商品id:");
	scanf("%d", &id);
	if (0 == findIndexByID_d(productDat, id, &onSaleProduct)) {
		printf("不存在的商品id\n");
	}else{
		printf("请输入添加数量:");
		scanf("%d", &quantity);
		if (quantity > onSaleProduct->allowance) {
			if (onSaleProduct->allowance > 0) {
				printf("余量不足，已将商品全部添加，共添加%d件商品\n", onSaleProduct->allowance);
				quantity = onSaleProduct->allowance;
				onSaleProduct->allowance = 0;
			}else{
				printf("该商品已售罄\n");
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

	printf("请输入待删除的商品id:");
	scanf("%d", &id);
	if (0 != (pos = findProduct_d(productDat, id, &onSaleProduct))) {
		onSaleProduct->allowance += currentOrder.items[currentIndex - 1].quantity;
		printf("删除成功\n");
		currentIndex--;
	}else {
		printf("不存在id为%d的商品\n", id);
	}
}

void modifyProductFromCurrentOrder()
{
	int id;
	int quantity;
	bool flag = false;
	OnSale_t* onSaleProduct;

	printf("请输入需要更改的商品id:");
	scanf("%d", &id);
	for (int i = 0; i < currentIndex; i++) {
		if (currentOrder.items[i].product.id == id) {
			printf("请重新输入需要购买的数量:");
			scanf("%d", &quantity);
			currentOrder.items[i].quantity = quantity;
			flag = true;
			printf("更改完成\n");
			break;
		}
	}
	if (flag == false) {
		printf("当前订单中没有id为%d的商品\n");
	}
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
	calTurnOverInCurrentOrder();
}

void calTurnOverInCurrentOrder()
{
	float sum = 0;

	for (int i = 0; i < currentIndex; i++) {
		sum += currentOrder.items[i].quantity * currentOrder.items[i].product.price;
	}

	printf("总价为%.2f\n", sum);
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
	insert(orderDat, END, endOrder);/* 用于末尾判断 */
	printf("已成功提交.\n");
}

/* 局部函数实现 */
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