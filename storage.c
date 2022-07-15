#include "storage.h"
#include "typeCollection.h"

extern User_t currentUser;
extern Node_t* productDat;
/* 局部函数模型 */
static int getChoice();

/**
*  @brief: 运行在售商品操作
*
*/
void runStorageSystem()
{
	while (1)
	{
		int choice = getChoice();

		switch (choice)
		{
		default:
			return;
		case 1:
			displayStorage();
			break;
		case 2:
			queryStorage();
			break;
		case 3:
			inStorage();
			break;
		case 4:
			outStorage();
			break;
		}
	}
}

/**
*  @brief: 查询在售商品
*
*/
void queryStorage(void)
{
	unsigned int id;
	Storage_t* storage = NULL;
	printf("请输入待查询的商品 ID: ");
	scanf("%u", &id);
	if (findProduct_d(storageDat, id, &storage) != 0) {
		printProductInfo(storage);
	}
	else {
		printf("不存在 %d 号商品。\n", id);
	}
	system("pause");
	return;
}

/**
*  @brief: 入库
*
*/
void inStorage(void)
{
	unsigned int id = 0;
	unsigned int inStorageNumber; /* 入库数量 */
	Storage_t* storage = NULL;
	Supplier_t* supplier = NULL;
	Storage_t* newStorage = (Storage_t*)malloc(sizeof(Storage_t));

	if (NULL == newStorage)
	{
		printf("新库存节点初始化失败。");
		system("pause");
		exit(0);
	}

	while (1)
	{
		printf("请输入商品 ID: ");
		scanf("%u", &id);
		if (id > 1000000 || id < 100000)
		{
			printf("你输入的 ID 无效，请重新输入。\b\n");
			continue;
		}
		break;
	}
	
	if (0 != findProduct_d(storageDat, id, &storage)) { /* 如果库存内已记载了该商品的信息 */
		printf("仓库内已存在该商品。请填写入库数量: ");
		scanf("%u", &inStorageNumber);
		storage->allowance += inStorageNumber;
		printf("入库完毕。");
	}
	else { /* 新商品入库 */
		flush();
		printf("仓库内无该商品。新商品 ID 为 %u.\n请输入新商品名称: ", configDat.maxId_Product + 1);
		stringGet(newStorage->product.name, 48);
		printf("请输入供应商名称: ");
		stringGet(newStorage->product.supplier, 24);

		if (!findIndexByName_d(supplierDat, newStorage->product.supplier, OFFSET_SUPPLIER, &supplier)) /* 若新商品的供应商不存在，则把新供应商加入供应商目录 */
		{
			Supplier_t* newSupplier = (Supplier_t*)malloc(sizeof(Supplier_t));
			newSupplier->id = ++configDat.maxId_Supplier;
			strcpy(newSupplier->name, newStorage->product.supplier);
			insert(supplierDat, END, newSupplier);
		}
		newStorage->product.id = ++configDat.maxId_Product; /* 自动生成 ID */

		printf("请输入价格(￥/件): ");
		scanf("%f", &(newStorage->product.price));
		printf("请输入入库数量: ");
		scanf("%u", &(newStorage->allowance));
		insert(storageDat, END, newStorage);
		printf("添加完成。");
	}
	system("pause");
	return;
}

/**
*  @brief: 出库 / 上架销售
*/
void outStorage(void)
{
	unsigned int id, pos;
	unsigned int outStorageNumber;
	Storage_t* storage;

	printf("请输入待出库商品 ID: ");
	scanf("%u", &id);
	if (findProduct_d(storageDat, id, &storage) != 0) /* 如果要出库的商品在库存中 */
	{
		if (storage->allowance == 0) /* 但是这件商品已经没有了 */
		{
			printf("出库失败，仓库中已没有剩余的商品 %d", id);
			system("pause");
			return;
		}
		
		OnSale_t* tOnSale = NULL;
		if (findProduct_d(productDat, id, &tOnSale)) /* 要出库的商品已经在货架上了 */
		{
			printf("请填写出库数量: ");
			scanf("%u", &outStorageNumber);
			if (storage->allowance - outStorageNumber >= 0)
			{
				storage->allowance -= outStorageNumber;
				tOnSale->allowance += outStorageNumber;
				printf("出库成功。");
			}
			else
			{
				tOnSale->allowance += storage->allowance;
				printf("库存不足，已全部出库，共出库 %u 件商品\n", storage->allowance);
				storage->allowance = 0;
			}
		}
		else /* 要出库的商品还不在货架上 */
		{
			OnSale_t* newOnSale = (OnSale_t*)malloc(sizeof(OnSale_t));
			if (NULL == newOnSale)
			{
				printf("新商品节点初始化失败。");
				system("pause");
				return;
			}
		}
		/*
		// 补充取得对应的上架商品地址操作
		if (storage.allowance > 0) {
			printf("请填写出库数量: ");
			scanf("%u", &outStorageNumber);
			if (storage.allowance - outStorageNumber >= 0) {
				storage.allowance -= outStorageNumber;
				// 补充上架操作
				printf("出库成功\n");
			}else{
				// 补充上架操作
				storage.allowance = 0;
				printf("库存不足，已全部出库，共出库 %u 件商品。", storage.allowance);
			}
		}
		*/
	} else {
		printf("不存在 ID %u 的商品。", id);
	}
	system("pause");
	return;
}

/**
*  @brief: 显示所有待售商品信息
*
*/
void displayStorage(void)
{
	// 打印库存商品信息
	printList(storageDat, printStorageInfo, true);
	system("pause");
	return;
}

/* 局部函数实现 */
static int getChoice()
{
	int choice;
	showTitle(currentUser);
	do
	{
		showStorageBusinessMenu();
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);

	return choice;
}