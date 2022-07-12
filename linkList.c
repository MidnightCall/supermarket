#include <stdio.h>
#include <stdlib.h>
#include "linkList.h"
#include "typeCollection.h"

Node_t* newList(void)
{
	Node_t* head = NULL;
	unsigned int* count = (unsigned int*)malloc(sizeof(unsigned int)); /* 头节点用于存储节点数的变量，这里给其分配内存 */
	if (NULL == count)
	{
		printf("链表初始化失败。\b\n");
		exit(0);
	}
	*count = 0;

	head = (Node_t*)malloc(sizeof(Node_t));
	if (head != NULL)
	{
		head->data = count;
		head->next = NULL;
	}
	else
	{
		printf("链表初始化失败。\b\n");
		exit(0);
	}
	return head;
}

void insert(Node_t* head, int pos, void* data)
{
	Node_t* tHead = head, *node;
	int* count = head->data, i = 1;
	while (tHead->next != NULL && i < pos)
	{
		tHead = tHead->next;
		++i;
	}
	node = (Node_t*)malloc(sizeof(Node_t));
	if (node != NULL)
	{
		node->data = data;
		node->next = NULL;
		if (tHead->next != NULL)
		{
			node->next = tHead->next;
		}
		tHead->next = node;
		++(*count);
	}
	else
	{
		printf("节点初始化失败。\n");
		exit(0);
	}
	return;
}

void del(Node_t* head, int pos)
{
	Node_t* tHead = head, * prev = NULL;
	int* count = &(head->data), i = 0;
	if (pos > *count || pos < 1)
	{
		printf("Error: invalid index.\n");
		return;
	}
	while (i != pos)
	{
		prev = tHead;
		tHead = tHead->next;
		i++;
	}

	if (tHead->next == NULL)
	{
		prev->next = NULL;
	}
	else
	{
		prev->next = tHead->next;
	}
	free(tHead);
	--(*count);
	return;
}

void* printUserInfo(UserInfo_t* node)
{
	printf("%d, %s, %d\n", node->id, node->password, node->permission);
	return 0;
}

void* printProductInfo(Product_t* node)
{
	printf("%s, %s, %f\n", node->name, node->supplier, node->price);
	return 0;
}

void* printEmployeeInfo(Employee_t* node)
{
	printf("%u, %u, %d, %s, %s\n", node->id, node->age, node->sex, node->name, node->position);
	return 0;
}

void* printSupplierInfo(Supplier_t* node)
{
	printf("%u, %s, %s\n", node->id, node->name, node->tel);
	return 0;
}

void* printStorageInfo(Storage_t* node)
{
	// TODO
	return 0;
}

void* printOrderInfo(Order_t* node)
{
	// TODO
	return 0;
}

void printList(Node_t* head, void (*type)(void*))
{
	Node_t* tHead = head;
	printf("COUNT = %d\n", *(int*)(head->data));
	tHead = tHead->next;
	while (tHead != NULL)
	{
		(*type)(tHead->data);
		tHead = tHead->next;
	}
}

void freeList(Node_t* head)
{
	Node_t* tHead = head, * next = head->next;
	while (tHead != NULL)
	{
		free(tHead->data);
		free(tHead);
		tHead = next;
		next = next->next;
	}
	return;
}