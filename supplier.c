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
	int id;
	Supplier_t supplier;
	printf("请输入待查询的供货商id:");
	scanf("%d", &id);
	if (0 != findIndexByID_d(supplierDat, id, &supplier, sizeof(Supplier_t))) {
		printSupplierInfo(&supplier);
	}else {
		printf("不存在编号为%d的供货商\n", id);
	}
}

/**
*  @brief: 添加供应商信息
*
*/
void addSupplier()
{
	Supplier_t* newSupplier = (Supplier_t*)malloc(sizeof(Supplier_t));
	char productName[48];
	while (true)
	{
		printf("请输入商品供货商id:");
		scanf("%d", &newSupplier->id);
		if (findIndexByID(supplierDat, newSupplier ->id) != 0) {
			printf("供货商id已存在，请重新输入\n");
		}
		else {
			break;
		}
	}
	flush();
	printf("请输入供货商名称:");
	stringGet(newSupplier->name, 21);
	printf("请输入供货商提供的商品名称:");
	stringGet(productName, 48);
	if (0 == findIndexByName(supplierDat, productName, OFFSET_SUPPLIER))
	{
		Product_t * newProduct = (Product_t*)malloc(sizeof(Product_t));
		/*
			生成对应的商品id
		*/
		strcpy(newProduct->name, productName);
		strcpy(newProduct->supplier, newSupplier->name);
		printf("请输入该商品的价格:");
		scanf("%f", &newProduct->price);
		insert(productDat, END, newProduct);
	}
	insert(supplierDat, END, newSupplier);
	printf("添加完成\n");
}

/**
*  @brief: 删除供应商信息
*
*/
void delSupplier()
{
	int id;
	int pos;
	printf("请输入待删除供应商id:");
	scanf("%d", &id);
	if ((pos = findIndexByID(supplierDat, id)) != 0) {
		del(supplierDat, pos);
		printf("删除成功\n");
	}
	else {
		printf("不存在id%d的供应商\n", id);
	}
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
		showSupplierBusinessMenu();
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);

	return choice;
}