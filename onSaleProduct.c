#include "onSaleProduct.h"

/* 局部函数模型 */
static int getChoice();

/**
*  @brief: 运行在售商品操作
*
*/
void runOnSaleSystem()
{
	int choice = getChoice();

	switch (choice)
	{
	default:
		break;
	case 1:
		displayOnSaleProduct();
		break;
	case 2:
		queryOnSaleProduct();
		break;
	case 3:
		addOnSaleProduct();
		break;
	case 4:
		delOnSaleProduct();
		break;
	}
}

/**
*  @brief: 运行在售商品操作
*
*/
void queryOnSaleProduct()
{

}

/**
*  @brief: 添加代售商品
*
*/
void addOnSaleProduct()
{

}

/**
*  @brief: 删除代售商品
*
*/
void delOnSaleProduct()
{

}

/**
*  @brief: 显示所有代售商品信息
*
*/
void displayOnSaleProduct()
{

}

/* 局部函数实现 */
static int getChoice()
{
	int choice;

	do
	{
		showOnSaleBusinessMenu();
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);

	return choice;
}