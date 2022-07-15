#include "product.h"

/* 局部函数模型 */
static int getChoice();

/**
*  @brief: 运行在售商品操作
*
*/
void runProductSystem()
{
	int choice = getChoice();
	switch (choice)
	{
	default:
		break;
	case 1:
		displayProduct();
		break;
	case 2:
		queryProduct();
		break;
	case 3:
		addProduct();
		break;
	case 4:
		delProduct();
		break;
	}
}

/**
*  @brief: 查询在售商品
*
*/
void queryProduct()
{
	int id;
	Product_t product;
	printf("请输入待查询的商品id:");
	scanf("%d", &id);
	if (findIndexByID_d(productDat, id, &product, sizeof(Product_t)) != 0) {
		printProductInfo(&product);
	}
	else {
		printf("不存在%d号商品\n", id);
	}
}

/**
*  @brief: 添加代售商品
*
*/
void addProduct()
{
	Product_t* newProduct = (Product_t*)malloc(sizeof(Product_t));

	while (true)
	{
		printf("请输入商品id:");
		scanf("%d", &newProduct->id);
		if (findIndexByID(productDat, newProduct->id) != 0) {
			printf("商品id已存在，请重新输入\n");
		}
		else {
			break;
		}
	}
	flush();
	printf("请输入商品名称:");
	stringGet(newProduct->name, 48);
	printf("请输入供应商名称:");
	stringGet(newProduct->supplier, 24);
	printf("请输入价格($/件):");
	scanf("%f", &newProduct->price);
	insert(productDat, END, newProduct);
	printf("添加完成\n");
}

/**
*  @brief: 删除代售商品
*
*/
void delProduct()
{
	int id;
	int pos;
	printf("请输入待删除商品id:");
	scanf("%d", &id);
	if ((pos = findIndexByID(productDat, id)) != 0) {
		del(productDat, pos);
		printf("删除成功\n");
	}
	else {
		printf("不存在id%d的商品\n", id);
	}
}

/**
*  @brief: 显示所有代售商品信息
*
*/
void displayProduct()
{
	printList(productDat, printProductInfo, false);
}

/* 局部函数实现 */
static int getChoice()
{
	int choice;

	do
	{
		showProductMenu();
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);

	return choice;
}