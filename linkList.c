#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkList.h"
#include "typeCollection.h"

/* newList: 已检查 */

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

/* insert: 已检查 */

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

/* del: 已检查 */

void del(Node_t* head, int pos)
{
	Node_t* tHead = head, * prev = NULL;
	int* count = head->data, i = 0;
	if (pos > *count || pos < 1)
	{
		printf("错误：无效的索引。\n");
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

/* getData: 已检查 */

void* getData(Node_t* head, int index)
{
	Node_t* tHead = head;
	if (NULL == tHead->next)
		return NULL;
	
	int count = 1;
	tHead = head->next;
	while (tHead->next != NULL && count < index)
	{
		tHead = tHead->next;
		++count;
	}
	return tHead->data;
}

/* printList: 已检查 */

void printList(Node_t* head, void (*type)(void*), bool count)
{
	Node_t* tHead = head;
	if (count) /* 仅作调试用途 */
	{
		printf("[COUNT = %d, %s: %d]\n", *(int*)(head->data), __FILE__, __LINE__);
	}

	tHead = tHead->next;
	while (tHead != NULL)
	{
		(*type)(tHead->data);
		tHead = tHead->next;
	}
}

/* freeList: 已检查 */

void freeList(Node_t* head)
{
	Node_t* tHead = head, * next;

	if (tHead->next == NULL)
	{
		free(tHead->data);
		free(tHead);
		return;
	}

	next = tHead->next;
	while (tHead->next != NULL)
	{
		next = tHead->next;
		free(tHead->data);
		free(tHead);
		tHead = next;
	}
	free(tHead->data);
	free(tHead);
	return;
}