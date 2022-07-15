#include "storage.h"

/* 局部函数模型 */
static int getChoice();

/**
*  @brief: 运行在售商品操作
*
*/
void runStorageSystem()
{
	int choice = getChoice();
	switch (choice)
	{
	default:
		break;
	case 1:
		displayStorage();
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
void queryStroage()
{
	int id;
	Storage_t storage;
	printf("请输入待查询的商品id:");
	scanf("%d", &id);
	if (findIndexByID_d(storageDat, id, &storage, sizeof(Storage_t)) != 0) {
		printProductInfo(&storage);
	}
	else {
		printf("不存在%d号商品\n", id);
	}
}

/**
*  @brief: 添加代售商品
*
*/
void inStorage()
{
	int id;
	Supplier_t supplier;
	Storage_t storage;
	Storage_t* newStorage = (Storage_t*)malloc(sizeof(Storage_t));

	/* 重复商品，提示用户添加库存 */
	printf("请输入商品id:");
	scanf("%d", &id);
	if (0 != findIndexByID_d(storageDat, id, &storage, sizeof(Storage_t)/* 此处替换为查询库存的函数 */)) {
		int inStorageNumber;
		printf("请填写入库数量:");
		scanf("%d", &inStorageNumber);
		storage.allowance += inStorageNumber;
		printf("入库完毕\n");
	}
	else {
		flush();
		printf("请输入商品名称:");
		stringGet(newStorage->product.name, 48);
		printf("请输入供应商名称:");
		stringGet(newStorage->product.supplier, 24);
		if (findIndexByName_d(supplierDat, newStorage->product.supplier, OFFSET_SUPPLIER, &supplier, sizeof(Supplier_t)))
		{
			newStorage->product.id = ++configDat.maxId_Product;
			strcpy(supplier.name, newStorage->product.supplier);
		}
		printf("请输入价格($/件):");
		scanf("%f", &(newStorage->product.price));
		insert(storageDat, END, newStorage);
		printf("添加完成\n");
	}

	
}

/**
*  @brief: 删除代售商品
*
*/
void outStorage()
{
	int id;
	int pos;
	Storage_t storage;

	printf("请输入待出库商品id:");
	scanf("%d", &id);
	if ((0 != (pos = findIndexByID_d(storageDat, id, &storage, sizeof(Storage_t))))/* 此处替换为查询库存的函数 */) 
	{
		OnSale_t onSale;
		// 补充取得对应的上架商品地址操作
		if (storage.allowance > 0) {
			int outStorageNumber;
			printf("请填写出库数量:");
			scanf("%d", &outStorageNumber);
			if (storage.allowance - outStorageNumber >= 0) {
				storage.allowance -= outStorageNumber;
				// 补充上架操作
				printf("出库成功\n");
			}else{
				// 补充上架操作
				storage.allowance = 0;
				printf("库存不足，已全部出库，共出库%d件商品\n", storage.allowance);
			}
		}
	}else {
		printf("不存在id%d的商品\n", id);
	}
}

/**
*  @brief: 显示所有代售商品信息
*
*/
void displayStorage()
{
	// 打印库存商品信息
}

/* 局部函数实现 */
static int getChoice()
{
	int choice;

	do
	{
		showStorageBusinessMenu();
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);

	return choice;
}