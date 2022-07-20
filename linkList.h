/*****************************************************************//**
 * \file   linkList.h
 * \brief  ������Ľ������ͷš�����ȹ��ܵ�ʵ��
 * 
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#ifndef __LINKLIST_H_
#define __LINKLIST_H_

#include "typeCollection.h"
#include "customLookup.h"
#include <stdbool.h>

/**
* \brief �½�һ������
*
* \return ������ı�ͷָ��
*/
Node_t* newList(void);

/**
* \brief �����ݲ��뵽ָ��������
*
* \param head Ҫ���뵽�������ͷָ��
* \param pos ���뵽�����е�λ�� (�� 1 Ϊ��ʼ)
* \param val ָ��������ݵ�ָ��
*/
void insert(Node_t* head, int pos, void* data);

/**
* \brief ����ɾ������
* 
* \param head Ҫ���뵽�������ͷָ��
* \param pos ��Ҫɾ��������λ�� (�� 1 Ϊ��ʼ)
*/
void del(Node_t* head, int pos);

/**
* \brief ��ȡ������λ���� index ��������
*
* \param head �������ڵĵ�����ͷָ��
* \param index �����������е�λ�� (����)
*
* \return Ŀ�����ݵĵ�ַ��������Ϊ�գ��򷵻� NULL.
*/
void* getData(Node_t* head, int index);

/**
* \brief ��ӡ����������
*
* \param head Ҫ����������ͷָ��
* \param format ָ�����������ʽ
* \param count �Ƿ���ʾ�ڵ���� (Ӧʹ�� false, ����������;)
* 
* \see customLookup.h
*/
void printList(Node_t* head, void (*format)(void*), bool count);

/**
* \brief �����ͷŲ���
* 
* \param head Ҫ�ͷŵ������ͷָ��
*/
void freeList(Node_t* head);

#endif