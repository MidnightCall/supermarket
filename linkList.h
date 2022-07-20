/*****************************************************************//**
 * \file   linkList.h
 * \brief  对链表的建立、释放、插入等功能的实现
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
* \brief 新建一个链表
*
* \return 新链表的表头指针
*/
Node_t* newList(void);

/**
* \brief 将数据插入到指定链表中
*
* \param head 要插入到的链表的头指针
* \param pos 插入到链表中的位置 (以 1 为起始)
* \param val 指向插入内容的指针
*/
void insert(Node_t* head, int pos, void* data);

/**
* \brief 链表删除操作
* 
* \param head 要插入到的链表的头指针
* \param pos 需要删除的内容位置 (以 1 为起始)
*/
void del(Node_t* head, int pos);

/**
* \brief 获取链表中位置在 index 处的数据
*
* \param head 内容所在的的链表头指针
* \param index 内容在链表中的位置 (索引)
*
* \return 目标数据的地址。若链表为空，则返回 NULL.
*/
void* getData(Node_t* head, int index);

/**
* \brief 打印链表内数据
*
* \param head 要遍历的链表头指针
* \param format 指定内容输出格式
* \param count 是否显示节点计数 (应使用 false, 仅作调试用途)
* 
* \see customLookup.h
*/
void printList(Node_t* head, void (*format)(void*), bool count);

/**
* \brief 链表释放操作
* 
* \param head 要释放的链表的头指针
*/
void freeList(Node_t* head);

#endif