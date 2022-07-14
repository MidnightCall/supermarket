#ifndef __LINKLIST_H_
#define __LINKLIST_H_

#include "typeCollection.h"
#include "customLookup.h"
#include <stdbool.h>

/**
* @brief �½�һ������
*
* @return ������ı�ͷָ��
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

/**
* @brief ��ӡ����������
*
* @param head Ҫ����������ͷָ��
* @param type ָ�����������ʽ
* @param count �Ƿ���ʾ�ڵ���� (Ӧʹ�� false, ����������;)
*/
void printList(Node_t* head, void (*type)(void*), bool count);

/**
* @brief ��������б������Ҳ���
*
* @param head Ҫ����������ͷָ��
* @param operation Ҫ���������ݽ��еĲ���
*/
void retrieveList(Node_t* head, bool(*operation)(Node_t*, void* data));


/**
* @brief �����ͷŲ���
* 
* @param head Ҫ�ͷŵ������ͷָ��
*/
void freeList(Node_t* head);

#endif