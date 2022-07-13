#include "typeCollection.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "customLookup.h"

void printUserInfo(User_t* node)
{
	printf("%d, %s, %d\n", node->id, node->password, node->permission);
	return;
}

void printProductInfo(Product_t* node)
{
	printf("%s, %s, %f\n", node->name, node->supplier, node->price);
	return;
}

void printEmployeeInfo(Employee_t* node)
{
	static char* sexConv[] = { "Å®", "ÄÐ" };
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

int findIndexByName(Node_t* head, char* name, RequiredTypeEnum type)
{
	int count = 1;
	bool flag = false;

	if (NULL == head->next)
		return 0;

	Node_t* tHead = head->next;

	switch (type)
	{
	case PRODUCT:
		while (tHead != NULL)
		{
			if (0 == strcmp((char*)tHead->data, name))
			{
				flag = true;
				break;
			}
			tHead = tHead->next;
			++count;
		}
		break;
	case EMPLOYEE:
		while (tHead != NULL)
		{
			if (0 == strcmp((char*)tHead->data + 12, name))
			{
				flag = true;
				break;
			}
			tHead = tHead->next;
			++count;
		}
		break;
	case SUPPLIER:
		while (tHead != NULL)
		{
			if (0 == strcmp((char*)tHead->data + 4, name))
			{
				flag = true;
				break;
			}
			tHead = tHead->next;
			++count;
		}
		break;
	default:
		return 0;
	}

	if (flag)
		return count;
	else
		return 0;

}
