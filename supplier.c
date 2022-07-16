#include "supplier.h"
#include "typeCollection.h"


extern Config_t configDat;
extern User_t currentUser;
/* 局部函数模型 */
static int getChoice();

/**
*  @brief: 运行供应商
*
*/
void runSupplierSystem()
{
	while (1)
	{
		int choice = getChoice();

		switch (choice)
		{
		default:
			return;
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
}

/**
*  @brief: 查询供应商信息
*
*/
void querySupplier()
{
	if (0 == *(int*)supplierDat->data)
	{
		printf("目前没有供应商。");
		PAUSE;
		return;
	}

	unsigned int id;
	Supplier_t* supplier = NULL;;
	id = getAnNonNegativeDigit("待查询供货商 ID");

	if (0 != findIndexByID_d(supplierDat, id, &supplier)) {
		printSupplierInfo(supplier);
	} else {
		printf("不存在编号为 %d 的供货商。", id);
	}

	PAUSE;
	return;
}

/**
*  @brief: 添加供应商信息
*
*/
void addSupplier()
{
	Supplier_t* newSupplier = (Supplier_t*)malloc(sizeof(Supplier_t));
	//assert_null(newSupplier);

	printf("新供货商 ID 是 %d\n", ++configDat.maxId_Supplier);
	newSupplier->id = configDat.maxId_Supplier;
	flush();
	printf("请输入供货商名称: ");
	stringGet(newSupplier->name, 21);

	Supplier_t* tSupplier = NULL; 
	if (findIndexByName_d(supplierDat, newSupplier->name, OFFSET_SUPPLIER, &tSupplier)) /* 判断是否有重复供应商 */
	{
		printf("此供应商已存在，ID 为 %u.\n添加失败。", tSupplier->id);
		PAUSE;
		return;
	}

	insert(supplierDat, END, newSupplier);
	printf("添加完成。");
	PAUSE;
	return;
}

/**
*  @brief: 删除供应商信息
*
*/
void delSupplier(void)
{
	if (0 == *(int*)supplierDat->data)
	{
		printf("目前没有供应商。");
		PAUSE;
		return;
	}

	unsigned int id, pos;
	id = getAnNonNegativeDigit("待删除供应商 ID");
	if ((pos = findIndexByID(supplierDat, id)) != 0) {
		del(supplierDat, pos);
		printf("删除成功。\n");
	}
	else {
		printf("不存在 ID %d 的供应商。", id);
	}

	PAUSE;
	return;
}

/**
*  @brief: 显示所有供应商信息
*
*/
void displaySupplier(void)
{
	if (0 == *(int*)supplierDat->data)
	{
		printf("目前没有供应商。");
		PAUSE;
		return;
	}

	printf("┌──────┬────────────供应商信息───────────────────┐\n");
	printf("│ %5s│ %40s│\n", "ID", "名称");
	printf("├──────┼─────────────────────────────────────────┤\n");
	printList(supplierDat, printSupplierInfo, false);
	printf("└──────┴─────────────────────────────────────────┘\n");

	PAUSE;
	return;
}

/* 局部函数实现 */
static int getChoice(void)
{
	int choice;
	showTitle(currentUser);
	do
	{
		showSupplierBusinessMenu();
		printf(">>> ");
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);
	flush();

	return choice;
}