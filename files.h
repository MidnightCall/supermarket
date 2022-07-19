/*****************************************************************//**
 * \file   files.h
 * \brief  对文件读写功能的实现
 * 
 * \author East Monster
 * \date   July 2022
 *********************************************************************/
#ifndef __FILES_H_
#define __FILES_H_

#include "typeCollection.h"

/* 文件名常量，具体定义在 files.c 中 */
extern const char* FILE_USER;
extern const char* FILE_EMPLOYEE;
extern const char* FILE_PRODUCT;
extern const char* FILE_STORAGE;
extern const char* FILE_SUPPLIER;
extern const char* FILE_ORDER;

/**
* \brief 从文件中加载数据
* 
* \param filename 文件名
* \param head 存放数据的链表头
* \param size 对应数据类型的大小，一般为 sizeof(xxx_t)
* \param curMaxId 用于回传链表中最大的 ID 值。若为 NULL 则不回传
*/
void loadFile(const char* filename, Node_t* head, size_t size, unsigned int* curMaxId);

/**
* \brief 将数据保存到文件中
* 
* \param filename 文件名
* \param head 存放数据的链表头
* \param size 对应数据类型的大小，一般为 sizeof(xxx_t)
*/
void writeFile(const char* filename, Node_t* head, size_t size);

/**
 * \brief 初始化各个含 ID 的结构体类型的最大 ID 值
 */
void initConfig(void);

///**
// * \brief 保存配置文件中记录的各个含 ID 的结构体类型的最大 ID 值
// */
//void saveConfig(void);

/**
 * \brief 显示配置文件中记录的信息。仅供调试使用。
 */
void printConfig(void);
#endif



