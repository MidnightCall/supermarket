#include "order.h"

/* 局部函数模型 */
static int getChoice();

/**
*  @brief: 运行供应商
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
		displaySupplier();
		break;
	case 2:
		querySupplier();
		break;
	case 3:
		addSupplier();
		break;
	case 4:
		delSupplier();
		break;
	}
}

/**
*  @brief: 查询订单信息
*
*/
void queryOrder()
{

}

/**
*  @brief: 添加订单信息
*
*/
void addOrder()
{
	printf("请输入供货商提供的商品名称");
}

/**
*  @brief: 删除订单信息
*
*/
void delOrder()
{

}

/**
*  @brief: 显示所有订单信息
*
*/
void displayOrder()
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