#ifndef __LINKLIST_H_
#define __LINKLIST_H_

#include <stdbool.h>
#include "typeCollection.h"

/**
* @brief �½�һ������
*
* @return ������ı�ͷָ�� (void*)
*/
Node_t* newList(void);

/**
* @brief ����������
*
* @param head Ҫ���뵽�������ͷָ��
* @param pos ���뵽�����е�λ�� (�� 1 Ϊ��ʼ)
* @param val ָ��������ݵ�ָ��
*/
void insert(Node_t* head, int pos, void* data);

/**
* @brief ����ɾ������
* 
* @param head Ҫ���뵽�������ͷָ��
* @param pos ��Ҫɾ��������λ�� (�� 1 Ϊ��ʼ)
* @param val ָ��������ݵ�ָ��
*/
void del(Node_t* head, int pos);

void printList(Node_t* head, void (*type)(void*));

/**
* @brief ָ���û���Ϣ�������ʽ
*
* @param node Ҫ������û���Ϣ�ڵ�
*/
void* printUserInfo(UserInfo_t* node);

/* ���º���ִ�����ƹ��� */

void* printProductInfo(Product_t* node);

void* printEmployeeInfo(Employee_t* node);

void* printSupplierInfo(Supplier_t* node);

void* printStorageInfo(Storage_t* node);

void* printOrderInfo(Order_t* node);

/**
* @brief �����ͷŲ���
* 
* @param head Ҫ�ͷŵ������ͷָ��
*/
void freeList(Node_t* head);

#endif