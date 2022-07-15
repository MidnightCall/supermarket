#ifndef __CUSTOM_LOOKUP_H_
#define __CUSTOM_LOOKUP_H_

/* 内存偏移值 */
extern const int OFFSET_PRODUCT;
extern const int OFFSET_EMPLOYEE;
extern const int OFFSET_SUPPLIER;

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
* @brief 根据 ID 查找节点在链表中的位置。适用于含 ID 的结构体类型。
*
* @param head 要查找的链表头
* @param id 查找条件 (ID)
* 
* @return 节点在链表中的位置。若不存在，则返回 0.
*/
int findIndexByID(Node_t* head, unsigned int id);

/**
* @brief 根据 ID 查找节点在链表中的位置。适用于含 ID 的结构体类型。
*
* @param head 要查找的链表头
* @param id 查找条件 (ID)
* @param dest 回传查找到的数据所在的实际地址
*
* @return 节点在链表中的位置。若不存在，则返回 0.
*/
int findIndexByID_d(Node_t* head, unsigned int id, void** dest);

/**
* @brief 根据名称查找节点在链表中的位置。适用于类型 Product_t, Employee_t 和 Supplier_t.
*
* @param head 要查找的链表头
* @param id 查找条件 (ID)
* @param offset 对应的数据类型所需要的偏移量 (OFFSET_XXX)
*
* @return 节点在链表中的位置。若不存在，则返回 0.
*/
int findIndexByName(Node_t* head, char* name, const int offset);

/**
* @brief 根据名称查找节点在链表中的位置。适用于类型 Product_t, Employee_t 和 Supplier_t.
*
* @param head 要查找的链表头
* @param id 查找条件 (ID)
* @param offset 对应的数据类型所需要的偏移量 (OFFSET_XXX)
* @param dest 回传查找到的数据所在的实际地址
*
* @return 节点在链表中的位置。若不存在，则返回 0.
*/
int findIndexByName_d(Node_t* head, char* name, const int offset, void** dest);

#endif