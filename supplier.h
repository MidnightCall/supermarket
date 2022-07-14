#ifndef __SUPPLIER_H_
#define __SUPPLIER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UI.h"
#include "files.h"
#include "linkList.h"
#include "helpfulFunction.h"

extern Node_t* supplierDat;

/**
*  @brief: 运行供应商操作
*
*/
void runSupplierSystem();

/**
*  @brief: 查找供应商信息
*
*/
void querySupplier();

/**
*  @brief: 添加供应商信息
*
*/
void addSupplier();

/**
*  @brief: 删除供应商信息
*
*/
void delSupplier();

/**
*  @brief: 显示所有供应商信息
*
*/
void displaySupplier();



#endif // !__ONSALEPRODUCT_H_