/*****************************************************************//**
 * \file   onSaleProduct.c
 * \brief  对在售商品管理功能的实现
 *
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#include "onSaleProduct.h"
#include "helpfulFunction.h"

/* 局部函数模型 */
static int getChoice();
static void showSingleOnSale(OnSale_t* onSale);
extern User_t currentUser;

/**
*  \brief: 运行在售商品操作
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
			PAUSE;
			break;
		case 2:
			queryOnSaleProduct();
			break;
		case 3:
			offshelfOnSaleProduct();
		}
	}
}

/**
*  \brief 查询在售商品
*/
void queryOnSaleProduct(void)
{
	if (NULL == productDat->next)
	{
		printf("<!> 货架上还没有商品，无法查询信息。\a");
		PAUSE;
		return;
	}

	displayOnSaleProduct();

	unsigned int id = 0;
	char tempName[48];
	int op = 0, onSaleType;
	OnSale_t* onSale = NULL;
	while (true)
	{
		op = getNonNegativeNumber("请输入查询条件[0. ID, 1. 商品名, 2. 种类]: ");
		if (op > 2 || op < 0)
		{
			printf("<!> 输入的操作格式不正确，请重新输入。\a");
			PAUSE;
			continue;
		}
		break;
	}

	switch (op)
	{
	case 0:
		id = getNonNegativeNumber("请输入商品 ID: ");

		if (findProduct_d(productDat, id, &onSale))
			showSingleOnSale(onSale);
		else
			printf("<!> 不存在 %d 号商品\a\n", id);
		break;

	case 1:
		printf("请输入商品名: ");
		stringGet(tempName, 48);

		if (findProductByName_d(productDat, tempName, &onSale))
			showSingleOnSale(onSale);
		else
			printf("<!> 不存在商品 [%s]\a\n", tempName);
		break;

	case 2:
		while (1)
		{
			onSaleType = getNonNegativeNumber("请输入商品种类\n[0. 果蔬    , 1. 日用品  ]\n[2. 办公用品, 3. 食品    ]\n[4. 酒水饮料, 5. 家用电器]\n>>> ");
			if (onSaleType > 5)
			{
				printf("<!> 输入的操作格式不正确，请重新输入。\a");
				PAUSE;
				continue;
			}
			break;
		}

		printf("┌────────┬──────────────────────────────商品详细信息───────┬───────────┬───────────┬───────┐\n");
		printf("│ %7s│ %48s│ %10s│ %10s│ %6s│\n", "商品 ID", "商品名", "单价", "种类", "余量");
		printf("├────────┼─────────────────────────────────────────────────┼───────────┼───────────┼───────┤\n");

		Node_t* tHead = productDat;
		tHead = productDat->next;
		bool flag = false;

		while (tHead != NULL)
		{
			if (*(ProductTypeEnum*)((char*)tHead->data + 84) == onSaleType)
			{
				printOnSaleInfo(tHead->data);
				flag = true;
			}
			tHead = tHead->next;
		}

		if (!flag)
		{
			printf("│                                       一件也没有。                                       │\n");
		}

		printf("└────────┴─────────────────────────────────────────────────┴───────────┴───────────┴───────┘\n");
	}
	PAUSE;
	return;
}

/**
*  \brief 显示所有在售商品信息
*/
void displayOnSaleProduct(void)
{
	printf("┌────────┬──────────────────────────────商品详细信息───────┬───────────┬───────────┬───────┐\n");
	printf("│ %7s│ %48s│ %10s│ %10s│ %6s│\n", "商品 ID", "商品名", "单价", "种类", "余量");
	printf("├────────┼─────────────────────────────────────────────────┼───────────┼───────────┼───────┤\n");
	printList(productDat, printOnSaleInfo, false);
	printf("└────────┴─────────────────────────────────────────────────┴───────────┴───────────┴───────┘\n");
	
	return;
}

/**
 * \brief 将在售商品下架
 */
void offshelfOnSaleProduct()
{
	if (NULL == productDat->next)
	{
		printf("<!> 货架上还没有商品，无法进行下架操作。\a");
		PAUSE;
		return;
	}

	displayOnSaleProduct();

	unsigned int id = 0;
	int op = 0, pos = 0;
	OnSale_t* onSale = NULL;
	Storage_t* originStorage = NULL;

	id = getNonNegativeNumber("请输入商品 ID: ");

	if (!(pos = findProduct_d(productDat, id, &onSale)))
	{
		printf("<!> 不存在 %d 号商品。\a", id);
		PAUSE;
		return;
	}

	op = getNonNegativeNumber("请输入下架操作类型条件 [0. 回到库存, 1. 直接撤下]: ");
	if (op > 2 || op < 0)
	{
		printf("<!> 输入的操作格式不正确。\a");
		PAUSE;
		return;
	}

	if (op == 0) /* 回到库存 */
	{
		findProduct_d(storageDat, id, &originStorage);
		originStorage->allowance += onSale->allowance;
		onSale->allowance = 0; /* 其实是假下架。*/
		printf("商品已回到库存。");
	}
	else /* 直接删除 */
	{
		del(productDat, pos); /* 这下真下架了 */
		printf("商品已下架。");
	}

	PAUSE;
	return;
}

/* 局部函数实现 */
static int getChoice()
{
	int choice = 0;

	do
	{
		showTitle(currentUser);
		showOnSaleBusinessMenu();
		choice = getMenuChoice();
	} while (choice > 4 || choice < 1);

	return choice;
}

/**
 * \brief 显示单条在售商品信息
 * 
 * \param 要显示的在售商品信息节点
 */
static void showSingleOnSale(OnSale_t* onSale)
{
	printf("┌────────┬──────────────────────────────商品详细信息───────┬───────────┬───────────┬───────┐\n");
	printf("│ %7s│ %48s│ %10s│ %10s│ %6s│\n", "商品 ID", "商品名", "单价", "种类", "余量");
	printf("├────────┼─────────────────────────────────────────────────┼───────────┼───────────┼───────┤\n");
	printOnSaleInfo(onSale);
	printf("└────────┴─────────────────────────────────────────────────┴───────────┴───────────┴───────┘\n");
	return;
}
