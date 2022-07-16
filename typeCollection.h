/**
* typeCollection.h
* ���ڶԳ�����ʹ�õ����Զ������ͽ��й���
*/

#ifndef __TYPECOLLECTION_H_
#define __TYPECOLLECTION_H_

#define LEN_PWD 12  /* �˻�������󳤶� */
#define LEN_NAME 9  /* ְ��������󳤶� */
#define LEN_POS 11  /* ְ��ְλ��󳤶� */

#define END 2147483647

#include <time.h>

/* �û�Ȩ��ö�� */
typedef enum tagPermissionEnum
{
    COMMON, ADMIN, SU
} PermissionEnum;

/* ְ���Ա�ö�� */
typedef enum tagSexEnum
{
    FEMALE = 0, MALE = 1
} SexEnum;

typedef enum tagProductTypeEnum
{
    FRUIT, /* ���� */
    DAILY, /* ����Ʒ */
    STATIONERY, /* �칫��Ʒ */
    FOOD, /* ʳƷ */
    BEVERAGE, /* ��ˮ���� */
    APPLIANCE /* ���õ��� */
} ProductTypeEnum;

/* ͨ������ڵ� */
typedef struct tagNode_t
{
    void* data;
    struct tagNode_t* next;
} Node_t;

/* ����������Ϣ�ڵ� */
typedef struct tagConfig_t
{
    unsigned int maxId_User; /* 5 λ */
    unsigned int maxId_Product; /* 6 λ */
    unsigned int maxId_Employee; /* 4 λ */
    unsigned int maxId_Supplier; /* 3 λ */
    unsigned int maxId_Order; /* 7 λ */
} Config_t;

/* �û���Ϣ */ /* size: 20 */
typedef struct tagUser_t
{
    unsigned int id;
    char password[LEN_PWD];
    PermissionEnum permission;
} User_t;

/* ��Ʒ��Ϣ�ڵ� */ /* size: 80 */
typedef struct tagProduct_t
{
    unsigned int id;
    char name[48]; /* ��Ʒ�� */
    char supplier[24]; /* ��Ʒ������ */
    float price; /* ��Ʒ�۸� */
    ProductTypeEnum type; /* ��Ʒ��� */
} Product_t;


/* ְ����Ϣ�ڵ� */ /* size: 32 */
typedef struct tagEmployee_t
{
    unsigned int id;
    unsigned int age;
    SexEnum sex;
    char name[LEN_NAME];
    char position[LEN_POS];
} Employee_t;

/* ��Ӧ����Ϣ�ڵ� */ /* size: 28 */
typedef struct tagSupplier_t
{
    unsigned int id;
    char name[21];
} Supplier_t;

/* �ϼܵ���Ʒ��Ϣ�ڵ� */ /* size: 84 */
typedef struct tagOnSale_t 
{
    Product_t product;
    unsigned int allowance; /* ���� */
} OnSale_t;

/* �����Ϣ�ڵ� */ /* size: 84 */
typedef struct tagStorage_t
{
    Product_t product;
    unsigned int allowance; /* ���� */
} Storage_t;

/* ������Ʒ��Ϣ�ڵ� */ /* size: 84 */
typedef struct tagOrderItem_t
{
    Product_t product;
    unsigned int quantity;
} OrderItem_t;

/* ������Ϣ�ڵ� */ /* size: 8412 */
typedef struct tagOrder_t
{
    unsigned int id; /* ������� */
    OrderItem_t items[100]; /* ����*/
    float total;  /* �����ܶ� */
    time_t time;  /* ����ʱ�� */
    unsigned int operatorId; /* ����Ա ID */
} Order_t;

#endif