/*****************************************************************//**
 * \file   customLookup.h
 * \brief  对特定结构体类型信息的打印和按条件查询函数的集中实现
 * 
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#ifndef __CUSTOM_LOOKUP_H_
#define __CUSTOM_LOOKUP_H_

/* 结构体内部内存偏移值 */
extern const int OFFSET_PRODUCT;
extern const int OFFSET_EMPLOYEE;
extern const int OFFSET_SUPPLIER;
extern const int OFFSET_PRODUCT_TYPE;
extern const int OFFSET_PRODUCT_SUPPLIER;

/**
 * @brief 输出单条用户 (User_t) 信息
 *
 * @param node 要输出的用户信息节点
 */
void printUserInfo(User_t* node);

/**
 * @brief 输出单条商品 (Product_t) 信息
 *
 * @param node 要输出的商品信息节点
 */
void printProductInfo(Product_t* node);

/**
 * @brief 输出单条在售商品 (OnSale_t) 信息
 *
 * @param node 要输出的在售商品节点
 */
void printOnSaleInfo(OnSale_t* node);

/**
 * @brief 输出单条库存商品 (Storage_t) 信息
 *
 * @param node 要输出的库存商品节点
 */
void printStorageInfo(Storage_t* node);

/**
 * @brief 输出单条员工 (Employee_t) 信息
 *
 * @param node 要输出的员工信息节点
 */
void printEmployeeInfo(Employee_t* node);

/**
 * @brief 输出单条供货商 (Supplier_t) 信息
 *
 * @param node 要输出的供货商信息节点
 */
void printSupplierInfo(Supplier_t* node);

/**
 * @brief 输出单条订单 (Order_t) 的粗略信息
 *
 * @param node 要输出的订单信息节点
 */
void printOrderInfo(Order_t* node);

/**
 * @brief 输出单条订单 (Order_t) 的详细信息
 *
 * @param node 要输出的订单信息节点
 */
void printOrderDetail(Order_t* node);

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

/**
* @brief 获取商品所在节点的位置
*
* @param head 要查找的链表头
* @param id 查找条件 (ID)
* 
* @return 节点在链表中的位置。若不存在，则返回 0.
*/
int findProduct(Node_t* head, unsigned int id);

/**
* @brief 获取商品所在节点的位置
*
* @param head 要查找的链表头
* @param id 查找条件 (ID)
* @param dest 回传查找到的商品所在库存或货架节点的实际地址
*
* @return 节点在链表中的位置。若不存在，则返回 0.
*/
int findProduct_d(Node_t* head, unsigned int id, void** dest);

/**
* @brief 获取商品所在节点的位置
*
* @param head 要查找的链表头
* @param id 查找条件 (商品名)
*
* @return 节点在链表中的位置。若不存在，则返回 0.
*/
int findProductByName(Node_t* head, char* name);

/**
* @brief 获取商品所在节点的位置
*
* @param head 要查找的链表头
* @param id 查找条件 (商品名)
* @param dest 回传查找到的商品所在库存或货架节点的实际地址
*
* @return 节点在链表中的位置。若不存在，则返回 0.
*/
int findProductByName_d(Node_t* head, char* name, void** dest);

/**
* @brief 获取商品所在节点的位置
*
* @param head 要查找的链表头
* @param id 查找条件 (商品类型)
* @param dest 回传查找到的商品所在库存或货架节点的实际地址
*
* @return 节点在链表中的位置。若不存在，则返回 0.
*/
int findProductByType(Node_t* head, ProductTypeEnum type, void** dest);

/**
* @brief 获取商品所在节点的位置
*
* @param head 要查找的链表头
* @param id 查找条件 (供应商名)
* @param dest 回传查找到的商品所在库存或货架节点的实际地址
*
* @return 节点在链表中的位置。若不存在，则返回 0.
*/
int findProductBySupplier(Node_t* head, const char* supplier, void** dest);
#endif