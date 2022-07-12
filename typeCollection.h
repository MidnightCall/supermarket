#ifndef __TYPECOLLECTION_H_
#define __TYPECOLLECTION_H_

const int LEN_PWD = 12;
const int LEN_NAME = 9;
const int LEN_POS = 11;

/* �û�Ȩ��ö�� */
typedef enum tagPermissionEnum
{
    USER, ADMIN, SU
} PermissionEnum;

typedef enum tagSexEnum
{
    MALE, FEMALE
} SexEnum;


/* ͨ������ڵ� */
typedef struct tagNode_t
{
    void* data;
    struct tagNode_t* next;
} Node_t;

/* �û���Ϣ */
typedef struct tagUserInfo_t
{
    int id;
    char* password[LEN_PWD];
    PermissionEnum permission;
};

/* ��Ʒ��Ϣ�ڵ� */
typedef struct tagProduct_t
{
    char* name[48]; /* ��Ʒ�� */
    char* supplier[24]; /* ��Ʒ������ */
    float price; /* ��Ʒ�۸� */
} Product_t;

typedef struct tagEmployee_t
{
    unsigned int id;
    unsigned int age;
    SexEnum sex;
    char* name[LEN_NAME];
    char* position[LEN_POS];
} Employee_t;

typedef struct tagSupplier_t
{
    unsigned int id;
    char* name[21];
    char* tel[12];
} Supplier_t;

typedef struct tagStorage_t
{
    Product_t product;
    unsigned int allowance;
};

typedef struct tagOrderItem_t
{
    Product_t product;
    unsigned int quantity;
} OrderItem_t;

typedef struct tagOrder_t
{
    char* customer[LEN_NAME];
    OrderItem_t items[100];
};

#endif
