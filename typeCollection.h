#ifndef __TYPECOLLECTION_H_
#define __TYPECOLLECTION_H_

/* 通用链表节点 */
typedef struct tagNode_t
{
    void *data;
    struct tagNode_t* next;
} Node_t;

/* 商品信息节点 */
typedef struct tagProduct_t
{
    char* name[48]; /* 商品名 */
    char* supplier[24]; /* 商品供货商 */
    float price; /* 商品价格 */
    unsigned int allowance; /* 商品余量 */
    unsigned long long barcode; /* 商品条形码 */
} Product_t;


#endif
