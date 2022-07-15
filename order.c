#include "order.h"

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