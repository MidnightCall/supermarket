#include "supplier.h"

/* 局部函数模型 */
static int getChoice();

/**
*  @brief: 运行供应商
*
*/
void runSupplierSystem()
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
*  @brief: 查询供应商信息
*
*/
void querySupplier()
{

}

/**
*  @brief: 添加供应商信息
*
*/
void addSupplier()
{
	printf("请输入供货商提供的商品名称");
}

/**
*  @brief: 删除供应商信息
*
*/
void delSupplier()
{

}

/**
*  @brief: 显示所有供应商信息
*
*/
void displaySupplier()
{
	printList(supplierDat, printProductInfo, false);
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