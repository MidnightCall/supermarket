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
*
*/
void addOnSaleProduct()
{
	OnSale_t* newOnSaleProduct = (OnSale_t*)malloc(sizeof(OnSale_t));

	while (true)
	{
		printf("请输入商品id:");
		scanf("%d",&(newOnSaleProduct->product.id));
		if (0 != findIndexByID(productDat, newOnSaleProduct->product.id)) {
			printf("商品id已存在，请重新输入\n");
		}else{
			break;
		}
	}
	flush();
	printf("请输入商品名称:");
	stringGet(newOnSaleProduct->product.name, 48);
	printf("请输入供应商名称:");
	stringGet(newOnSaleProduct->product.supplier, 24);
	printf("请输入价格($/件):");
	scanf("%f", &(newOnSaleProduct->product.price));
	insert(productDat, END, newOnSaleProduct);
	printf("添加完成\n");
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
		del(productDat, pos);
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
	printList(productDat, printProductInfo, false);
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