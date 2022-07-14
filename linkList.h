#ifndef __LINKLIST_H_
#define __LINKLIST_H_

#include "typeCollection.h"
#include "customLookup.h"
#include <stdbool.h>

/**
* @brief 新建一个链表
*
* @return 新链表的表头指针
*/
Node_t* newList(void);

/**
* @brief 链表插入操作
*
* @param head 要插入到的链表的头指针
* @param pos 插入到链表中的位置 (以 1 为起始)
* @param val 指向插入内容的指针
*/
void insert(Node_t* head, int pos, void* data);

/**
* @brief 链表删除操作
* 
* @param head 要插入到的链表的头指针
* @param pos 需要删除的内容位置 (以 1 为起始)
* @param val 指向插入内容的指针
*/
void del(Node_t* head, int pos);

/**
* @brief 打印链表内数据
*
* @param head 要遍历的链表头指针
* @param type 指定内容输出格式
* @param count 是否显示节点计数 (应使用 false, 仅作测试用途)
*/
void printList(Node_t* head, void (*type)(void*), bool count);

/**
* @brief 对链表进行遍历查找操作
*
* @param head 要遍历的链表头指针
* @param operation 要对链表数据进行的操作
*/
void retrieveList(Node_t* head, bool(*operation)(Node_t*, void* data));


/**
* @brief 链表释放操作
* 
* @param head 要释放的链表的头指针
*/
void freeList(Node_t* head);

#endif