#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkList.h"
#include "typeCollection.h"

Node_t* newList(void)
{
	Node_t* head = NULL;
	unsigned int* count = (unsigned int*)malloc(sizeof(unsigned int)); /* ͷ�ڵ����ڴ洢�ڵ����ı����������������ڴ� */
	if (NULL == count)
	{
		printf("�����ʼ��ʧ�ܡ�\b\n");
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
		printf("�����ʼ��ʧ�ܡ�\b\n");
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
		printf("�ڵ��ʼ��ʧ�ܡ�\n");
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

void retrieveList(Node_t* head, bool(*matching)(int* count, void* data))
{
	Node_t* tHead = head;
	int* count = &(head->data), i = 1;

	if (tHead->next == NULL)
	{
		return;
	}

	tHead = head->next;

	while (tHead->next != NULL && i < *count)
	{
		//(*operation)(count, tHead->data);
		tHead = tHead->next;
	}
	return;
}

void printList(Node_t* head, void (*type)(void*), bool count)
{
	Node_t* tHead = head;
	if (count)
	{
		printf("COUNT = %d\n", *(int*)(head->data));
	}

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