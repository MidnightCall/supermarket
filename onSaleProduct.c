#include "onSaleProduct.h"

extern User_t currentUser;

/* 局部函数模型 */
static int getChoice();

/**
*  @brief: 运行在售商品操作
*/
void runOnSaleSystem()
{
	while (1)
	{
		int choice = getChoice();

		switch (choice)
		{
		default:
			return;
		case 1:
			displayOnSaleProduct();
			break;
		case 2:
			queryOnSaleProduct();
			break;
		}
	}
}

void queryOnSaleProduct()
{
	unsigned int id;
	OnSale_t onSale;
	printf("请输入待查询的商品id:");
	scanf("%u", &id);
	if (findIndexByID_d(productDat, id, &onSale, sizeof(Product_t)) != 0/* 此处替换为查询上架商品的操作 */) {
		/* 打印单条上架商品信息 */
	} else {
		printf("不存在%d号商品\n", id);
	}
}

void addOnSaleProduct(Product_t product, int allowance)
{
	OnSale_t onSaleProduct;
	onSaleProduct.product.id = product.id;
	onSaleProduct.product.price = product.price;
	onSaleProduct.allowance = allowance;
	strcpy(onSaleProduct.product.supplier, product.supplier);
	// 插入到onSale链表操作
	PASS;
}

/**
*  @brief: 删除代售商品
*
*/
void delOnSaleProduct(void)
{
	int id;
	int pos;
	printf("请输入待删除商品 ID: ");
	scanf("%d", &id);
	if ((pos = findIndexByID(productDat, id)) != 0) {
		// 删除对应 ID 的操作
		printf("删除成功。");
	} else {
		printf("不存在 ID %d 的商品。", id);
	}
	system("pause");
	return;
}

/**
*  @brief: 显示所有待售商品信息
*
*/
void displayOnSaleProduct()
{
	PASS;
}

/* 局部函数实现 */
static int getChoice()
{
	int choice;
	showTitle(currentUser);
	do
	{
		showOnSaleBusinessMenu();
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);

	return choice;
}