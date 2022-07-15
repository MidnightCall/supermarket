#include "onSaleProduct.h"

/* 局部函数模型 */
static int getChoice();

/**
*  @brief: 运行在售商品操作
*
*/
void runOnSaleProductSystem()
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
	}
}

/**
*  @brief: 查询在售商品
*
*/
void queryOnSaleProduct()
{
	int id;
	OnSale_t* onSaleProduct;
	printf("请输入待查询的商品id:");
	scanf("%d", &id);
	if (0 != findProduct_d(productDat, id, &onSaleProduct)) {
		// 打印上架商品信息
	}
	else {
		printf("不存在%d号商品\n", id);
	}
}

/**
*  @brief: 显示所有代售商品信息
*
*/
void displayOnSaleProduct()
{
	// 打印全部上架商品信息
}

/* 局部函数实现 */
static int getChoice()
{
	int choice;

	do
	{
		showOnSaleBusinessMenu();
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);

	return choice;
}