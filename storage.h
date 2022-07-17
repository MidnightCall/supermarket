#ifndef __STORAGE_H_
#define __STORAGE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UI.h"
#include "files.h"
#include "linkList.h"
#include "helpfulFunction.h"
#include "customLookup.h"

extern Node_t* storageDat, *supplierDat, *onSale;
extern Config_t configDat;

/**
*  @brief: 运行库存管理系统
*
*/
void runStorageSystem();

/**
*  @brief 查询库存商品
*
*/
void queryStorage();

/**
 * @brief 修改商品属性
 */
void modifyProductInfo();

/**
*  @brief: 入库
*
*/
void inStorage(void);

/**
*  @brief: 出库
*/
void outStorage();

/**
*  @brief: 显示所有库存商品信息
*
*/
void displayStorage();



#endif // !__STORAGE_H_