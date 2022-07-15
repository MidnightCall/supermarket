#include "onSaleProduct.h"

/* 局部函数模型 */
static int getChoice();

/**
*  @brief: 运行在售商品操作
*
*/
void runOnSaleProductSystem()
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

void queryOnSaleProduct(void)
{
	unsigned int id;
	OnSale_t* onSale = NULL;
	printf("请输入待查询的商品 ID: ");
	scanf("%u", &id);
	if (findProduct_d(productDat, id, &onSale)) {
		printOnSaleInfo(onSale);
	} else {
		printf("不存在 %d 号商品\n", id);
	}
	PAUSE;
	return;
}

/**
*  @brief: 显示所有待售商品信息
*
*/
void displayOnSaleProduct(void)
{
	printList(productDat, printOnSaleInfo, true);
	system("pause");
	return;
}

/* 局部函数实现 */
static int getChoice()
{
	int choice = 0;

	showTitle(currentUser);
	do
	{
		showOnSaleBusinessMenu();
		HINT;
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);

	return choice;
}