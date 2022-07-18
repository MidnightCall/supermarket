/**
* typeCollection.h
* 用于对程序中使用到的自定义类型进行归纳
*/

#ifndef __TYPECOLLECTION_H_
#define __TYPECOLLECTION_H_

#define LEN_PWD 12  /* 账户密码最大长度 */
#define LEN_NAME 9  /* 职工名字最大长度 */
#define LEN_POS 15  /* 职工职位最大长度 */

#define END 2147483647

#include <time.h>

/* 用户权限枚举 */
typedef enum tagPermissionEnum
{
    COMMON, ADMIN, SU
} PermissionEnum;

/* 职工性别枚举 */
typedef enum tagSexEnum
{
    FEMALE = 0, MALE = 1
} SexEnum;

typedef enum tagProductTypeEnum
{
    FRUIT, /* 果蔬 */
    DAILY, /* 日用品 */
    STATIONERY, /* 办公用品 */
    FOOD, /* 食品 */
    BEVERAGE, /* 酒水饮料 */
    APPLIANCE /* 家用电器 */
} ProductTypeEnum;

/* 通用链表节点 */
typedef struct tagNode_t
{
    void* data;
    struct tagNode_t* next;
} Node_t;

/* 程序设置信息节点 */
typedef struct tagConfig_t
{
    unsigned int maxId_User; /* 5 位 */
    unsigned int maxId_Product; /* 6 位 */
    unsigned int maxId_Employee; /* 4 位 */
    unsigned int maxId_Supplier; /* 3 位 */
    unsigned int maxId_Order; /* 7 位 */
} Config_t;

/* 用户信息 */ /* size: 20 */
typedef struct tagUser_t
{
    unsigned int id;
    char password[LEN_PWD];
    PermissionEnum permission;
} User_t;

/* 商品信息节点 */ /* size: 88 */
typedef struct tagProduct_t
{
    unsigned int id;
    char name[48]; /* 商品名 */
    char supplier[24]; /* 商品供货商 */
    float price; /* 商品售价 */
    float purchase; /* 商品进价 */
    ProductTypeEnum type; /* 商品类别 */
} Product_t;


/* 职工信息节点 */ /* size: 36 */
typedef struct tagEmployee_t
{
    unsigned int id;
    unsigned int age;
    SexEnum sex;
    char name[LEN_NAME];
    char position[LEN_POS]; /* 11 -> 15 */
} Employee_t;

/* 供应商信息节点 */ /* size: 28 */
typedef struct tagSupplier_t
{
    unsigned int id;
    char name[21];
} Supplier_t;

/* 上架的商品信息节点 */ /* size: 92 */
typedef struct tagOnSale_t 
{
    Product_t product;
    unsigned int allowance; /* 余量 */
} OnSale_t;

/* 库存信息节点 */ /* size: 92 */
typedef struct tagStorage_t
{
    Product_t product;
    unsigned int allowance; /* 余量 */
} Storage_t;

/* 订单商品信息节点 */ /* size: 92 */
typedef struct tagOrderItem_t
{
    Product_t product;
    unsigned int quantity;
} OrderItem_t;

/* 订单信息节点 */ /* size: 4632 */
typedef struct tagOrder_t
{
    unsigned int id; /* 订单编号 */
    OrderItem_t items[50]; /* 订单 */
    float total;  /* 订单总额 */
    float profit; /* 订单利润 */
    time_t time;  /* 交付时间 */
    unsigned int operatorId; /* 操作员 ID */
} Order_t;

#endif