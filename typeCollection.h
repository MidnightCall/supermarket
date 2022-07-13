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

/* �û�Ȩ��ö�� */
typedef enum tagPermissionEnum
{
    USER, ADMIN, SU
} PermissionEnum;

/* ְ���Ա�ö�� */
typedef enum tagSexEnum
{
    FEMALE = 0, MALE = 1
} SexEnum;

/* ͨ������ڵ� */
typedef struct tagNode_t
{
    void* data;
    struct tagNode_t* next;
} Node_t;

/* �û���Ϣ */
typedef struct tagUser_t
{
    int id;
    char password[LEN_PWD];
    PermissionEnum permission;
} User_t;

/* ��Ʒ��Ϣ�ڵ� */
typedef struct tagProduct_t
{
    char name[48]; /* ��Ʒ�� */
    char supplier[24]; /* ��Ʒ������ */
    float price; /* ��Ʒ�۸� */
} Product_t;

/* ְ����Ϣ�ڵ� */
typedef struct tagEmployee_t
{
    unsigned int id;
    unsigned int age;
    SexEnum sex;
    char name[LEN_NAME];
    char position[LEN_POS];
} Employee_t;

/* ��Ӧ����Ϣ�ڵ� */
typedef struct tagSupplier_t
{
    unsigned int id;
    char name[21];
    char tel[12];
} Supplier_t;

/* �����Ϣ�ڵ� */
typedef struct tagStorage_t
{
    Product_t product;
    unsigned int allowance;
} Storage_t;

/* ������Ʒ��Ϣ�ڵ� */
typedef struct tagOrderItem_t
{
    Product_t product;
    unsigned int quantity;
} OrderItem_t;

/* ������Ϣ�ڵ� */
typedef struct tagOrder_t
{
    char customer[LEN_NAME];
    OrderItem_t items[100];
} Order_t;

#endif