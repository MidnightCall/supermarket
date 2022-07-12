#ifndef __TYPECOLLECTION_H_
#define __TYPECOLLECTION_H_

/* ͨ������ڵ� */
typedef struct tagNode_t
{
    void *data;
    struct tagNode_t* next;
} Node_t;

/* ��Ʒ��Ϣ�ڵ� */
typedef struct tagProduct_t
{
    char* name[48]; /* ��Ʒ�� */
    char* supplier[24]; /* ��Ʒ������ */
    float price; /* ��Ʒ�۸� */
    unsigned int allowance; /* ��Ʒ���� */
    unsigned long long barcode; /* ��Ʒ������ */
} Product_t;


#endif
