/**
* typeCollection.h
* 用于对程序中使用到的自定义类型进行归纳
*/

#ifndef __TYPECOLLECTION_H_
#define __TYPECOLLECTION_H_

#define LEN_PWD 12  /* 账户密码最大长度 */
#define LEN_NAME 9  /* 职工名字最大长度 */
#define LEN_POS 11  /* 职工职位最大长度 */

#define END 2147483647

/* 用户权限枚举 */
typedef enum tagPermissionEnum
{
    USER, ADMIN, SU
} PermissionEnum;

/* 职工性别枚举 */
typedef enum tagSexEnum
{
    FEMALE = 0, MALE = 1
} SexEnum;

/* 通用链表节点 */
typedef struct tagNode_t
{
    void* data;
    struct tagNode_t* next;
} Node_t;

/* 用户信息 */
typedef struct tagUser_t
{
    int id;
    char password[LEN_PWD];
    PermissionEnum permission;
} User_t;

/* 商品信息节点 */
typedef struct tagProduct_t
{
    char name[48]; /* 商品名 */
    char supplier[24]; /* 商品供货商 */
    float price; /* 商品价格 */
} Product_t;

/* 职工信息节点 */
typedef struct tagEmployee_t
{
    unsigned int id;
    unsigned int age;
    SexEnum sex;
    char name[LEN_NAME];
    char position[LEN_POS];
} Employee_t;

/* 供应商信息节点 */
typedef struct tagSupplier_t
{
    unsigned int id;
    char name[21];
    char tel[12];
} Supplier_t;

/* 库存信息节点 */
typedef struct tagStorage_t
{
    Product_t product;
    unsigned int allowance;
} Storage_t;

/* 订单商品信息节点 */
typedef struct tagOrderItem_t
{
    Product_t product;
    unsigned int quantity;
} OrderItem_t;

/* 订单信息节点 */
typedef struct tagOrder_t
{
    char customer[LEN_NAME];
    OrderItem_t items[100];
} Order_t;

#endif