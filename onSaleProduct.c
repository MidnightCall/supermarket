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
	}
	
}

/**
*  @brief: 查询在售商品
*
*/
void queryOnSaleProduct()
{
	int id;
	OnSale_t onSale;
	printf("请输入待查询的商品id:");
	scanf("%d", &id);
	if (findIndexByID_d(productDat, id, &onSale, sizeof(Product_t)) != 0/* 此处替换为查询上架商品的操作 */) {
		/* 打印单条上架商品信息 */
	}else {
		printf("不存在%d号商品\n", id);
	}
}

/**
*  @brief: 添加新的商品
*  @param product 添加的商品信息
*  @param allowance 添加的库存数量
*
*/
void addOnSaleProduct(Product_t product, int allowance)
{
	OnSale_t onSaleProduct;
	onSaleProduct.product.id = product.id;
	onSaleProduct.product.price = product.price;
	onSaleProduct.allowance = allowance;
	strcpy(onSaleProduct.product.supplier, product.supplier);
	// 插入到onSale链表操作
}

/**
*  @brief: 删除代售商品
*
*/
void delOnSaleProduct()
{
	int id;
	int pos;
	printf("请输入待删除商品id:");
	scanf("%d", &id);
	if ((pos = findIndexByID(productDat, id)) != 0) {
		// 删除对应id的代码
		printf("删除成功\n");
	}else {
		printf("不存在id%d的商品\n", id);
	}
}

/**
*  @brief: 显示所有代售商品信息
*
*/
void displayOnSaleProduct()
{
	// 打印所有待售商品信息
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