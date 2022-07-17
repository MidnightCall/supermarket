#include "typeCollection.h"
#include "customLookup.h"
#include "helpfulFunction.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int OFFSET_PRODUCT = 4;
const int OFFSET_EMPLOYEE = 12;
const int OFFSET_SUPPLIER = 4;
const int OFFSET_PRODUCT_TYPE = 80;
const int OFFSET_PRODUCT_SUPPLIER = 52;

static char* sexConv[] = { "女", "男" };
static char* typeConv[] = { "果蔬", "日用品", "文具", "食品", "酒水", "家用电器" };

void printUserInfo(User_t* node)
{
	static char* pmsConv[] = { "普通用户", "管理员", "超级管理员" };
	printf("│ %7u│ %12s│ %24s│\n", node->id, node->password, pmsConv[node->permission]);
	return;
}

void printProductInfo(Product_t* node)
{
	printf("%d, %s, %s, %f\n",node->id, node->name, typeConv[node->type], node->price);
	return;
}

void printOnSaleInfo(OnSale_t* node)
{
	if (0 == node->allowance)
		return;
	printf("│ %7u│ %48s│ %10.2f│ %10s│ %6u│\n", node->product.id, node->product.name, node->product.price, typeConv[node->product.type], node->allowance);
	return;
}

void printStorageInfo(Storage_t* node)
{
	printf("│ %7u│ %48s│ %10.2f│ %10.2f│ %24s│ %8u│\n", node->product.id, node->product.name, node->product.price, node->product.purchase, node->product.supplier, node->allowance);
	return;
}

void printEmployeeInfo(Employee_t* node)
{
	printf("│ %5u│ %8s│ %6s│ %5u│ %15s│\n", node->id, node->name, sexConv[node->sex], node->age, node->position);
	return;
}

void printSupplierInfo(Supplier_t* node)
{
	printf("│ %5u│ %40s│\n", node->id, node->name);
	return;
}

void printOrderInfo(Order_t* node)
{
	char* timeStr = timeConv(node->time);
	printf("│ %7u│ %20s│ %6u│ %12.2f│\n", node->id, timeStr, node->operatorId, node->total);
	free(timeStr); /* timeConv 返回的是申请的一块临时内存空间，用完了就释放。经过测试，不这样写的话会导致内存泄露 (占用以每秒 400K 左右的速度增长)。 */
	return;
}

void printOrderDetail(Order_t* node)
{
	int i = 0;
	while (node->items[i].product.id != 0)
	{
		printf("│ %7u│ %48s│ %10.2f│ %6d│ %12.2f│\n", node->items[i].product.id,
			node->items[i].product.name, node->items[i].product.price,
			node->items[i].quantity, node->items[i].quantity * node->items[i].product.price);
		++i;
	}
	return;
}

int findIndexByID(Node_t* head, unsigned int id)
{
	int count = 1;
	bool flag = false;

	if (NULL == head->next)
		return 0;

	Node_t* tHead = head->next;

	while (tHead != NULL)
	{
		if (*(unsigned int*)(tHead->data) == id)
		{
			flag = true;
			break;
		}
		tHead = tHead->next;
		++count;
	}

	if (flag)
		return count;
	else
		return 0;
}

int findIndexByID_d(Node_t* head, unsigned int id, void** dest)
{
	int count = 1;
	bool flag = false;

	if (NULL == head->next)
		return 0;

	Node_t* tHead = head->next;

	while (tHead != NULL)
	{
		if (*(unsigned int*)(tHead->data) == id)
		{
			flag = true;
			*dest = tHead->data;
			break;
		}
		tHead = tHead->next;
		++count;
	}

	if (flag)
		return count;
	else
		return 0;
}

int findIndexByName(Node_t* head, char* name, const int offset)
{
	int count = 1;
	bool flag = false;

	if (NULL == head->next)
		return 0;

	Node_t* tHead = head->next;

	while (tHead != NULL)
	{
		if (0 == strcmp((char*)tHead->data + offset, name))
		{
			flag = true;
			break;
		}
		tHead = tHead->next;
		++count;
	}

	if (flag)
		return count;
	else
		return 0;
}

int findIndexByName_d(Node_t* head, char* name, const int offset, void** dest)
{
	int count = 1;
	bool flag = false;

	if (NULL == head->next)
		return 0;

	Node_t* tHead = head->next;

	while (tHead != NULL)
	{
		if (0 == strcmp((char*)tHead->data + offset, name))
		{
			flag = true;
			*dest = tHead->data;
			break;
		}
		tHead = tHead->next;
		++count;
	}

	if (flag)
		return count;
	else
		return 0;
}

Product_t* getProduct(void* src)
{
	return (Product_t*)src;
}

int findProduct(Node_t* head, unsigned int id)
{
	int count = 1;
	bool flag = false;

	if (NULL == head->next)
		return 0;

	Node_t* tHead = head->next;

	while (tHead != NULL)
	{
		/* OnSale_t 和 Storage_t 的结构是一样的 */
		if ((*(Storage_t*)tHead->data).product.id == id)
		{
			flag = true;
			break;
		}
		tHead = tHead->next;
		++count;
	}

	if (flag)
		return count;
	else
		return 0;
}

int findProduct_d(Node_t* head, unsigned int id, void** dest)
{
	int count = 1;
	bool flag = false;

	if (NULL == head->next)
		return 0;

	Node_t* tHead = head->next;

	while (tHead != NULL)
	{
		/* OnSale_t 和 Storage_t 的结构是一样的 */
		if ((*(Storage_t*)tHead->data).product.id == id)
		{
			flag = true;
			*dest = tHead->data;
			break;
		}
		tHead = tHead->next;
		++count;
	}

	if (flag)
		return count;
	else
		return 0;
}

int findProductByName(Node_t* head, char* name)
{
	int count = 1;
	bool flag = false;

	if (NULL == head->next)
		return 0;

	Node_t* tHead = head->next;

	while (tHead != NULL)
	{
		if (0 == strcmp((char*)tHead->data + OFFSET_PRODUCT, name))
		{
			flag = true;
			break;
		}
		tHead = tHead->next;
		++count;
	}

	if (flag)
		return count;
	else
		return 0;
}

int findProductByName_d(Node_t* head, char* name, void** dest)
{
	int count = 1;
	bool flag = false;

	if (NULL == head->next)
		return 0;

	Node_t* tHead = head->next;

	while (tHead != NULL)
	{
		if (0 == strcmp((char*)tHead->data + OFFSET_PRODUCT, name))
		{
			flag = true;
			*dest = tHead->data;
			break;
		}
		tHead = tHead->next;
		++count;
	}

	if (flag)
		return count;
	else
		return 0;
}

int findProductByType(Node_t* head, ProductTypeEnum type, void** dest)
{
	int count = 1;
	bool flag = false;

	if (NULL == head->next)
		return 0;

	Node_t* tHead = head->next;

	while (tHead != NULL)
	{
		if (*(ProductTypeEnum*)((char*)tHead->data + OFFSET_PRODUCT_TYPE) == type)
		{
			flag = true;
			*dest = tHead->data;
			break;
		}
		tHead = tHead->next;
		++count;
	}

	if (flag)
		return count;
	else
		return 0;
}

int findProductBySupplier(Node_t* head, const char* supplier, void** dest)
{
	int count = 1;
	bool flag = false;

	if (NULL == head->next)
		return 0;

	Node_t* tHead = head->next;

	while (tHead != NULL)
	{
		if (0 == strcmp((char*)tHead->data + OFFSET_PRODUCT_SUPPLIER, supplier))
		{
			flag = true;
			*dest = tHead->data;
			break;
		}
		tHead = tHead->next;
		++count;
	}

	if (flag)
		return count;
	else
		return 0;
}