#include "typeCollection.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "customLookup.h"

const int OFFSET_PRODUCT = 4;
const int OFFSET_EMPLOYEE = 12;
const int OFFSET_SUPPLIER = 4;

void printUserInfo(User_t* node)
{
	static char* pmsConv[] = { "普通用户", "管理员", "超级管理员" };
	printf("%5u| %12s| %20s|\n", node->id, node->password, pmsConv[node->permission]);
	return;
}

void printProductInfo(Product_t* node)
{
	printf("%d, %s, %s, %f\n",node->id, node->name, node->supplier, node->price);
	return;
}

void printEmployeeInfo(Employee_t* node)
{
	static char* sexConv[] = { "女", "男" };
	printf("%5u| %8s| %4s| %5u| %11s|\n", node->id, node->name, sexConv[node->sex], node->age, node->position);
	return;
}

void printSupplierInfo(Supplier_t* node)
{
	printf("%u, %s\n", node->id, node->name);
	return;
}

void printStorageInfo(Storage_t* node)
{
	// TODO
	return;
}

void printOrderInfo(Order_t* node)
{
	// TODO
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

int findIndexByID_d(Node_t* head, unsigned int id, void* dest, size_t size)
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
			if (dest != NULL)
				memcpy(dest, tHead->data, size);
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

int findIndexByName_d(Node_t* head, char* name, const int offset, void* dest, size_t size)
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
			if (dest != NULL)
				memcpy(dest, tHead->data, size);
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