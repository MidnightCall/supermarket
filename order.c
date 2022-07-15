#include "order.h"
#include "helpfulFunction.h"

/* 局部函数模型 */
static int getChoice();

int currentIndex = 0;
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

/**
*  @brief: 向当前订单添加商品
*
*/
void addProductToCurrentOrder()
{
	currentIndex = 0;
	int id;
	int quantity;
	OnSale_t* onSaleProduct;
	printf("请输入商品id:");
	scanf("%d", &id);
	if (0 == findIndexByID_d(productDat, id, &onSaleProduct)) {
		printf("不存在的商品id\n");
	}else{
		printf("请输入添加数量:");
		scanf("%d", &quantity);
		if (quantity > onSaleProduct->allowance) {
			printf("库存不足，已将商品全部添加，共添加%d件商品\n", onSaleProduct->allowance);
			quantity = onSaleProduct->allowance;
			onSaleProduct->allowance = 0;
		}else{
			onSaleProduct->allowance -= quantity;
			printf("添加成功");
		}
		for (int i = 0; i < currentIndex; i++) {
			if (id == currentOrder.items[i].product.id) {
				currentOrder.items[i].quantity = quantity;
			}else{
				currentOrder.items[i].quantity = quantity;
				currentOrder.items[i].product.id = onSaleProduct->product.id;
				currentOrder.items[i].product.price = onSaleProduct->product.price;
				strcpy(currentOrder.items[i].product.name, onSaleProduct->product.name);
				strcpy(currentOrder.items[i].product.supplier, onSaleProduct->product.supplier);
			}
		}
	}
	
	
}

/**
*  @brief: 删除当前订单的商品
*
*/
void delProductFromCurrentOrder()
{
	PASS;
}

/**
*  @brief: 更改当前订单的商品数量
*
*/
void modifyProductFromCurrentOrder()
{
	PASS;
}

/**
*  @brief: 计算总价
*
*/
void calTurnOverInCurrentOrder()
{
	PASS;
}

/**
*  @brief: 交付订单
*
*/
void submitCurrentOrder()
{
	PASS;
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
	} while (choice > 5 || choice < 1);
}