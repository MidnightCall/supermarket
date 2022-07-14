#ifndef __STORAGE_H_
#define __STORAGE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UI.h"
#include "files.h"
#include "linkList.h"
#include "helpfulFunction.h"
#include "customLookup.h"

extern Node_t* storageDat, *supplierDat, *onSale;

/**
*  @brief: 运行库存管理系统
*
*/
void runStorageSystem();

/**
*  @brief: 查询库存商品
*
*/
void queryStorage();

/**
*  @brief: 入库
*
*/
void inStorage();

/**
*  @brief: 出库
*
*/
void outStorage();

/**
*  @brief: 显示所有库存商品信息
*
*/
void displayStorage();



#endif // !__STORAGE_H_