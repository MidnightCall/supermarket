#include "onSaleProduct.h"
#include "helpfulFunction.h"

/* 局部函数模型 */
static int getChoice();
extern User_t currentUser;
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
		printf("┌────────┬──────────────────────────────商品详细信息───────┬───────────┬───────────┬───────┐\n");
		printf("│ %7s│ %48s│ %10s│ %10s│ %6s│\n", "商品 ID", "商品名", "单价", "种类", "余量");
		printf("├────────┼─────────────────────────────────────────────────┼───────────┼───────────┼───────┤\n");
		printOnSaleInfo(onSale);
		printf("└────────┴─────────────────────────────────────────────────┴───────────┴───────────┴───────┘\n");
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
	printf("┌────────┬──────────────────────────────商品详细信息───────┬───────────┬───────────┬───────┐\n");
	printf("│ %7s│ %48s│ %10s│ %10s│ %6s│\n", "商品 ID", "商品名", "单价", "种类", "余量");
	printf("├────────┼─────────────────────────────────────────────────┼───────────┼───────────┼───────┤\n");
	printList(productDat, printOnSaleInfo, false);
	printf("└────────┴─────────────────────────────────────────────────┴───────────┴───────────┴───────┘\n");
	PAUSE;
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