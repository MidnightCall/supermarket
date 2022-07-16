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

static char* sexConv[] = { "女", "男" };
static char* typeConv[] = { "果蔬","日用品","文具","食品","酒水","家用电器" };
static char* timeConv(time_t time);

void printUserInfo(User_t* node)
{
	static char* pmsConv[] = { "普通用户", "管理员", "超级管理员" };
	printf("| %7u| %12s| %22s|\n", node->id, node->password, pmsConv[node->permission]);
	return;
}

void printProductInfo(Product_t* node)
{
	printf("%d, %s, %s, %f\n",node->id, node->name, typeConv[node->type], node->price);
	return;
}

void printOnSaleInfo(OnSale_t* node)
{
	printf("%d, %s, %s, %f, %u\n", node->product.id, node->product.name, typeConv[node->product.type], node->product.price, node->allowance);
	return;
}

void printStorageInfo(Storage_t* node)
{
	printf("%u, %s, %s, %f, %u\n", node->product.id, node->product.name, node->product.supplier, node->product.price, node->allowance);
	return;
}

void printEmployeeInfo(Employee_t* node)
{
	printf("%5u| %8s| %4s| %5u| %11s|\n", node->id, node->name, sexConv[node->sex], node->age, node->position);
	return;
}

void printSupplierInfo(Supplier_t* node)
{
	printf("│ %5u│ %40s│\n", node->id, node->name);
	return;
}

void printOrderInfo(Order_t* node)
{
	printf("│ %7u│ %20s│ %6u│ %10.2f\n", node->id, timeConv(node->time), node->operatorId, node->total);
	return;
}

void printOrderDetail(Order_t* node)
{
	int i = 0;
	while (node->items->product.id != 0)
	{
		printf("%d\t%s\t%.2f\t%d\t%.2f\n", node->items[i].product.id,
			node->items[i].product.name, node->items[i].product.price,
			node->items[i].quantity, node->items[i].quantity * node->items[i].product.price);
	}
	PAUSE;
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

static char* timeConv(time_t time)
{
	char* nowTime = (char*)malloc(24);
	assert(nowTime != NULL);

	struct tm *stm = NULL;
	stm = localtime(&time);
	
	strftime(nowTime, 24, "%Y-%m-%d %H:%M:%S", stm);
	return nowTime;
}