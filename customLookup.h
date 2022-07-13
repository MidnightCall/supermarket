#ifndef __CUSTOM_LOOKUP_H_
#define __CUSTOM_LOOKUP_H_

/**
* @brief 指定用户信息的输入格式
*
* @param node 要输出的用户信息节点
*/
void printUserInfo(User_t* node);

/* 以下函数执行相似功能 */

void printProductInfo(Product_t* node);

void printEmployeeInfo(Employee_t* node);

void printSupplierInfo(Supplier_t* node);

void printStorageInfo(Storage_t* node);

void printOrderInfo(Order_t* node);

/**
* @brief 根据 ID 查找节点在链表中的位置。适用于类型 User_t 和 Employee_t.
*
* @param head 要查找的链表头
* @param id 查找条件 (ID)
* 
* @return 节点在链表中的位置。若不存在，则返回 0.
*/
int findIndexByID(Node_t* head, unsigned int id);

#endif