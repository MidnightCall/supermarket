#ifndef __FILES_C_
#define __FILES_C_

#include "typeCollection.h"

/* 文件名常量，具体定义在 files.c 中 */

extern const char* FILE_USER;
extern const char* FILE_EMPLOYEE;
extern const char* FILE_PRODUCT;
extern const char* FILE_STORAGE;
extern const char* FILE_SUPPLIER;
extern const char* FILE_ORDER;

/**
* @brief 从文件中加载数据
* 
* @param filename 文件名
* @param head 存放数据的链表头
* @param size 对应数据类型的大小，一般为 sizeof(xxx_t)
*/
void loadFile(const char* filename, Node_t* head, size_t size);

/**
* @brief 将数据保存到文件中
* 
* @param filename 文件名
* @param head 存放数据的链表头
* @param size 对应数据类型的大小，一般为 sizeof(xxx_t)
*/
void writeFile(const char* filename, Node_t* head, size_t size);
#endif