#include "storage.h"
#include "typeCollection.h"
#include "helpfulFunction.h"

extern User_t currentUser;
extern Node_t* productDat, * storageDat;
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
			if (0 == *(int*)storageDat->data)
			{
				printf("目前没有任何库存。");
				PAUSE;
				return;
			}
			displayStorage();
			PAUSE;
			break;
		case 2:
			queryStorage();
			break;
		case 3:
			modifyProductInfo();
			break;
		case 4:
			inStorage();
			break;
		case 5:
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
	if (0 == *(int*)storageDat->data)
	{
		printf("目前没有任何库存。");
		PAUSE;
		return;
	}

	displayStorage();
	unsigned int id;
	Storage_t* storage = NULL;

	id = getNonNegativeNumber("待查询的商品 ID");
	if (findProduct_d(storageDat, id, &storage) != 0) {
		printf("┌────────┬──────────────────────────────────────库存详细信息───────────┬───────────┬─────────────────────────┬─────────┐\n");
		printf("│ %7s│ %48s│ %10s│ %10s│ %24s│ %8s│\n", "商品 ID", "商品名", "单价", "进价", "供应商", "库存余量");
		printf("├────────┼─────────────────────────────────────────────────┼───────────┼───────────┼─────────────────────────┼─────────┤\n");
		printStorageInfo(storage);
		printf("└────────┴─────────────────────────────────────────────────┴───────────┴───────────┴─────────────────────────┴─────────┘\n");
	}
	else {
		printf("不存在 %d 号商品。\n", id);
	}
	PAUSE;
	return;
}

void modifyProductInfo()
{
	if (0 == *(int*)storageDat->data)
	{
		printf("目前没有任何库存。");
		PAUSE;
		return;
	}

	displayStorage();
	unsigned int id;
	Storage_t* storage = NULL;
	Storage_t* newStorage = (Storage_t*)malloc(sizeof(Storage_t)); /* 用来装新信息的临时载体。记得 free */
	assert(newStorage != NULL);

	id = getNonNegativeNumber("待修改的商品 ID");

	if (id > 1000000 || id < 100000)
	{
		printf("你输入的 ID 无效。");
		PAUSE;
		return;
	}

	if (findProduct_d(storageDat, id, &storage) != 0) /* 在库存中找商品。因为库存中的记录删不掉 */
	{
		memcpy(newStorage, storage, sizeof(Storage_t)); /* 先把原商品的信息复制到临时载体中 */

		/* 下边的流程与入库类似，只是是在现有记录基础上修改 */
		printf("请输入新商品名：");
		stringGet(newStorage->product.name, 48);

		printf("请输入供应商名称: ");
		stringGet(newStorage->product.supplier, 24);

		if (!findIndexByName(supplierDat, newStorage->product.supplier, OFFSET_SUPPLIER)) /* 若新商品的供应商不存在，则把新供应商加入供应商目录 */ // UNDONE(CHECK)
		{
			Supplier_t* newSupplier = (Supplier_t*)malloc(sizeof(Supplier_t));
			assert(newSupplier != NULL);

			newSupplier->id = ++configDat.maxId_Supplier;
			strcpy(newSupplier->name, newStorage->product.supplier);
			insert(supplierDat, END, newSupplier);
		}

		if (findProductByName_d(storageDat, newStorage->product.name, &newStorage)) /* 判断仓库内是否有名字相同，供应商也相同的商品记录 */
		{
			if (0 == strcmp(newStorage->product.supplier, newStorage->product.supplier))
			{
				printf("仓库内已存在该商品。信息修改失败。");
				free(newStorage); /* free ok */
				PAUSE;
				return;
			}
		}

		printf("请输入进价 (￥/件): "); // UNDONE (大小检查)
		scanf("%f", &(newStorage->product.purchase));

		printf("请输入价格 (￥/件): ");
		scanf("%f", &(newStorage->product.price));
		getchar();

		int type = 0;
		while (1)
		{
			type = getNonNegativeNumber("商品种类\n[0. 果蔬, 1. 日用品]\n[2. getNonNegativeNumber, 3. 食品]\n[4. 酒水饮料, 5. 家用电器]\n>>> ");
			if (type < 0 || type > 5)
			{
				printf("你输入的类型有误，请重新输入。");
				continue;
			}
			break;
		}
		newStorage->product.type = type;

		OnSale_t* targetOnSale = NULL;
		if (findProduct_d(productDat, storage->product.id, &targetOnSale))
		{
			memcpy(&targetOnSale->product, &newStorage->product, sizeof(Product_t)); /* 把货架上对应的商品信息也进行修改 (如果有的话) */
		}

		memcpy(storage, newStorage, sizeof(Storage_t)); /* 把新信息复制到原商品中。这个过程中，余量是没有变化的。 */
	}
	else
	{
		printf("你输入的商品不存在。");
	}

	free(newStorage); /* free ok */
	PAUSE;
	return;
}

/**
*  @brief: 入库
*/
void inStorage(void)
{
	displayStorage();
	unsigned int id = 0;
	unsigned int inStorageNumber; /* 入库数量 */
	unsigned int type = 0; /* 商品种类 */
	Storage_t* storage = NULL;
	Supplier_t* tsupplier = NULL;
	Storage_t* newStorage = (Storage_t*)malloc(sizeof(Storage_t));

	assert(NULL != newStorage);

	id = getNonNegativeNumber("商品 ID");
	if (id > 1000000 || id < 100000)
	{
		printf("你输入的 ID 无效。");
		PAUSE;
		return;
	}
	
	if (findProduct_d(storageDat, id, &storage) != 0) /* 如果库存内已记载了该商品的信息 */
	{ 
		printf("仓库内已存在该商品。");
		inStorageNumber = getNonNegativeNumber("入库数量");
		storage->allowance += inStorageNumber;
		printf("入库完毕。");
	} 
	else /* 新商品入库 */
	{ 
		//flush();
		printf("仓库内无该商品。新商品 ID 为 %u.\n请输入新商品名称: ", configDat.maxId_Product + 1);
		stringGet(newStorage->product.name, 48);
		printf("请输入供应商名称: ");
		stringGet(newStorage->product.supplier, 24);

		if (!findIndexByName(supplierDat, newStorage->product.supplier, OFFSET_SUPPLIER)) /* 若新商品的供应商不存在，则把新供应商加入供应商目录 */ // UNDONE (CHANGED)
		{
			Supplier_t* newSupplier = (Supplier_t*)malloc(sizeof(Supplier_t));
			newSupplier->id = ++configDat.maxId_Supplier;
			strcpy(newSupplier->name, newStorage->product.supplier);
			insert(supplierDat, END, newSupplier);
		}

		if (findProductByName_d(storageDat, newStorage->product.name, &storage)) /* 判断仓库内是否有名字相同，供应商也相同的商品记录 */
		{
			if (0 == strcmp(storage->product.supplier, newStorage->product.supplier))
			{
				printf("仓库内已存在该商品。");
				inStorageNumber = getNonNegativeNumber("入库数量");
				storage->allowance += inStorageNumber;
				printf("入库完毕。");
			}
		}
		else
		{
			newStorage->product.id = ++configDat.maxId_Product; /* 自动生成 ID */

			printf("请输入进价 (￥/件): "); // UNDONE (大小检查)
			scanf("%f", &(newStorage->product.purchase));
			printf("请输入价格 (￥/件): ");
			scanf("%f", &(newStorage->product.price));
			getchar();
			while (1)
			{
				type = getNonNegativeNumber("商品种类\n[0. 果蔬    , 1. 日用品  ]\n[2. 办公用品, 3. 食品    ]\n[4. 酒水饮料, 5. 家用电器]\n>>> ");
				if (type < 0 || type > 5)
				{
					printf("你输入的类型有误，请重新输入。\n");
					continue;
				}
				break;
			}
			newStorage->product.type = type;
			newStorage->allowance = getNonNegativeNumber("入库数量");
			insert(storageDat, END, newStorage);
			printf("添加完成。");
		}
	}
	PAUSE;
	return;
}

/**
*  @brief: 出库 / 上架销售
*/
void outStorage(void)
{
	if (0 == *(int*)storageDat->data)
	{
		printf("目前没有任何库存。");
		PAUSE;
		return;
	}

	displayStorage();
	unsigned int id;
	unsigned int outStorageNumber = 0;
	Storage_t* storage = NULL;

	id = getNonNegativeNumber("待出库商品 ID");
	if (findProduct_d(storageDat, id, &storage) != 0) /* 如果要出库的商品在库存中 */
	{
		if (storage->allowance == 0) /* 但是这件商品已经没有了 */
		{
			printf("出库失败，仓库中已没有剩余的商品 %d.\n", id);
			system("pause");
			return;
		}
		
		OnSale_t* tOnSale = NULL;
		if (findProduct_d(productDat, id, &tOnSale)) /* 要出库的商品已经在货架上了 */
		{
			outStorageNumber = getNonNegativeNumber("出库数量");
			if (storage->allowance >= outStorageNumber)
			{
				storage->allowance -= outStorageNumber;
				tOnSale->allowance += outStorageNumber;
				printf("出库成功。");
			}
			else
			{
				tOnSale->allowance += storage->allowance;
				printf("库存不足，已全部出库，共出库 %u 件商品。\n", storage->allowance);
				storage->allowance = 0;
			}
		}
		else /* 要出库的商品还不在货架上 */
		{
			OnSale_t* newOnSale = (OnSale_t*)malloc(sizeof(OnSale_t)); /* 新的在售商品节点 */
			if (NULL == newOnSale)
			{
				printf("新商品节点初始化失败。");
				system("pause");
				return;
			}

			newOnSale->product = storage->product;
			outStorageNumber = getNonNegativeNumber("出库数量");
			if (storage->allowance >= outStorageNumber) /* 注意，两个 unsigned 变量相减出现负数时会溢出变成超大的正数 */
			{
				storage->allowance -= outStorageNumber;
				newOnSale->allowance = outStorageNumber;
				printf("出库成功。");
			}
			else
			{
				newOnSale->allowance = storage->allowance;
				printf("库存不足，已全部出库，共出库 %u 件商品。", storage->allowance);
				storage->allowance = 0;
			}

			insert(productDat, END, newOnSale);

		}
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
	printf("┌────────┬──────────────────────────────────────库存详细信息───────────┬───────────┬─────────────────────────┬─────────┐\n");
	printf("│ %7s│ %48s│ %10s│ %10s│ %24s│ %8s│\n", "商品 ID", "商品名", "单价", "进价", "供应商", "库存余量");
	printf("├────────┼─────────────────────────────────────────────────┼───────────┼───────────┼─────────────────────────┼─────────┤\n");
	printList(storageDat, printStorageInfo, false);
	printf("└────────┴─────────────────────────────────────────────────┴───────────┴───────────┴─────────────────────────┴─────────┘\n");
	return;
}

/* 局部函数实现 */
static int getChoice()
{
	int choice;
	do
	{
		showTitle(currentUser);
		showStorageBusinessMenu();
		HINT;
		scanf("%d", &choice);
	} while (choice > 6 || choice < 1);
	flush();

	return choice;
}