/*****************************************************************//**
 * \file   linkList.c
 * \brief  对链表的建立、释放、插入等功能的实现
 *
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "linkList.h"
#include "typeCollection.h"

/* 本程序链表的实现：含头节点 (存储节点数)，插入为尾插法 */

 /**
 * \brief 新建一个链表
 *
 * \return 新链表的表头指针
 */
Node_t* newList(void)
{
	Node_t* head = NULL;
	unsigned int* count = (unsigned int*)malloc(sizeof(unsigned int)); /* 头节点用于存储节点数的变量，这里给其分配内存 */
	assert(count != NULL);

	*count = 0;

	head = (Node_t*)malloc(sizeof(Node_t));
	assert(head != NULL);

	head->data = count;
	head->next = NULL;

	return head;
}

/**
* \brief 将数据插入到指定链表中
*
* \param head 要插入到的链表的头指针
* \param pos 插入到链表中的位置 (以 1 为起始)
* \param val 指向插入内容的指针
*/
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
	assert(node != NULL);

	node->data = data;
	node->next = NULL;
	if (tHead->next != NULL)
	{
		node->next = tHead->next;
	}
	tHead->next = node;
	++(*count);

	return;
}

/**
* \brief 链表删除操作
*
* \param head 要插入到的链表的头指针
* \param pos 需要删除的内容位置 (以 1 为起始)
*/
void del(Node_t* head, int pos)
{
	Node_t* tHead = head, * prev = NULL;
	int* count = head->data, i = 0;
	if (pos > *count || pos < 1)
	{
		printf("<!> 错误：无效的索引。\a\n");
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

/**
* \brief 获取链表中位置在 index 处的数据
*
* \param head 内容所在的的链表头指针
* \param index 内容在链表中的位置 (索引)
*
* \return 目标数据的地址。若链表为空，则返回 NULL.
*/
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

/**
* \brief 打印链表内数据
*
* \param head 要遍历的链表头指针
* \param format 指定内容输出格式
* \param count 是否显示节点计数 (应使用 false, 仅作调试用途)
* 
* \see customLookup.h
*/
void printList(Node_t* head, void (*format)(void*), bool count)
{
	Node_t* tHead = head;
	if (count) /* 仅作调试用途 */
	{
		printf("[COUNT = %d, %s: %d]\n", *(int*)(head->data), __FILE__, __LINE__);
	}

	tHead = tHead->next;
	while (tHead != NULL)
	{
		(*format)(tHead->data);
		tHead = tHead->next;
	}
}

/**
* \brief 链表释放操作
*
* \param head 要释放的链表的头指针
*/
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