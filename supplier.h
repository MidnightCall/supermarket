/*****************************************************************//**
 * \file   supplier.h
 * \brief  对供应商管理功能的实现
 * 
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#ifndef __SUPPLIER_H_
#define __SUPPLIER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UI.h"
#include "files.h"
#include "linkList.h"
#include "helpfulFunction.h"

extern Node_t* supplierDat,* productDat;

/**
*  \brief 运行供应商管理模块
*/
void runSupplierSystem(void);

/**
*  \brief 查找供应商信息
*
*/
void querySupplier(void);

/**
*  \brief 添加供应商信息
*
*/
void addSupplier(void);

/**
*  \brief 删除供应商信息
*/
void delSupplier(void);

/**
 * \brief 修改供应商信息
 */
void modifySupplier(void);

/**
*  \brief 显示所有供应商信息
*/
void displaySupplier(void);

#endif // !__ONSALEPRODUCT_H_