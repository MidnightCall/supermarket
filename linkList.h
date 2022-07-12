#ifndef __LINKLIST_H_
#define __LINKLIST_H_

#include <stdbool.h>
#include "typeCollection.h"

/**
* @brief 新建一个链表
*
* @return 新链表的表头指针 (void*)
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

void printList(Node_t* head, void (*type)(void*));

/**
* @brief 指定用户信息的输入格式
*
* @param node 要输出的用户信息节点
*/
void* printUserInfo(UserInfo_t* node);

/* 以下函数执行相似功能 */

void* printProductInfo(Product_t* node);

void* printEmployeeInfo(Employee_t* node);

void* printSupplierInfo(Supplier_t* node);

void* printStorageInfo(Storage_t* node);

void* printOrderInfo(Order_t* node);

/**
* @brief 链表释放操作
* 
* @param head 要释放的链表的头指针
*/
void freeList(Node_t* head);

#endif