/*****************************************************************//**
 * \file   linkList.c
 * \brief  ������Ľ������ͷš�����ȹ��ܵ�ʵ��
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

/* �����������ʵ�֣���ͷ�ڵ� (�洢�ڵ���)������Ϊβ�巨 */

 /**
 * \brief �½�һ������
 *
 * \return ������ı�ͷָ��
 */
Node_t* newList(void)
{
	Node_t* head = NULL;
	unsigned int* count = (unsigned int*)malloc(sizeof(unsigned int)); /* ͷ�ڵ����ڴ洢�ڵ����ı����������������ڴ� */
	assert(count != NULL);

	*count = 0;

	head = (Node_t*)malloc(sizeof(Node_t));
	assert(head != NULL);

	head->data = count;
	head->next = NULL;

	return head;
}

/**
* \brief �����ݲ��뵽ָ��������
*
* \param head Ҫ���뵽�������ͷָ��
* \param pos ���뵽�����е�λ�� (�� 1 Ϊ��ʼ)
* \param val ָ��������ݵ�ָ��
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
* \brief ����ɾ������
*
* \param head Ҫ���뵽�������ͷָ��
* \param pos ��Ҫɾ��������λ�� (�� 1 Ϊ��ʼ)
*/
void del(Node_t* head, int pos)
{
	Node_t* tHead = head, * prev = NULL;
	int* count = head->data, i = 0;
	if (pos > *count || pos < 1)
	{
		printf("<!> ������Ч��������\a\n");
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
* \brief ��ȡ������λ���� index ��������
*
* \param head �������ڵĵ�����ͷָ��
* \param index �����������е�λ�� (����)
*
* \return Ŀ�����ݵĵ�ַ��������Ϊ�գ��򷵻� NULL.
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
* \brief ��ӡ����������
*
* \param head Ҫ����������ͷָ��
* \param format ָ�����������ʽ
* \param count �Ƿ���ʾ�ڵ���� (Ӧʹ�� false, ����������;)
* 
* \see customLookup.h
*/
void printList(Node_t* head, void (*format)(void*), bool count)
{
	Node_t* tHead = head;
	if (count) /* ����������; */
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
* \brief �����ͷŲ���
*
* \param head Ҫ�ͷŵ������ͷָ��
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