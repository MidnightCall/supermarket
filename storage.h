/*****************************************************************//**
 * \file   storage.h
 * \brief  对库存管理功能的实现
 * 
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

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

extern Node_t* storageDat, *supplierDat, *onSaleDat, *productDat;
extern Config_t configDat;
extern User_t currentUser;

/**
*  @brief 运行库存管理系统
*/
void runStorageSystem(void);

/**
*  @brief 查询库存商品
*
*/
void queryStorage(void);

/**
 * @brief 修改商品属性
 */
void modifyProductInfo(void);

/**
*  @brief 商品入库
*
*/
void inStorage(void);

/**
*  @brief 商品出库
*/
void outStorage(void);

/**
*  @brief 显示所有库存商品信息
*/
void displayStorage(void);

#endif // !__STORAGE_H_