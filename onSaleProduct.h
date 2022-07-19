/*****************************************************************//**
 * \file   onSaleProduct.h
 * \brief  对在售商品管理功能的实现
 * 
 * \author praist
 * \date   July 2022
 *********************************************************************/
#ifndef __ONSALEPRODUCT_H_
#define __ONSALEPRODUCT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UI.h"
#include "files.h"
#include "linkList.h"
#include "helpfulFunction.h"
#include "customLookup.h"

extern Node_t* storageDat, * productDat;

/**
*  \brief 运行在售商品操作
*/
void runOnSaleProductSystem(void);

/**
*  \brief 查询在售商品
*/
void queryOnSaleProduct();

/**
*  \brief 显示所有在售商品信息
*/
void displayOnSaleProduct(void);

/**
 * \brief 将在售商品下架
 */
void offshelfOnSaleProduct();

#endif // !__ONSALEPRODUCT_H_


