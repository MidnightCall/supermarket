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

extern Node_t* productDat;

/**
*  @brief: 运行在售商品操作
*
*/
void runOnSaleSystem();

/**
*  @brief: 查询代售商品
*
*/
void queryOnSaleProduct();

/**
*  @brief: 添加代售商品
*
*/
void addOnSaleProduct(Product_t product, int allowance);

/**
*  @brief: 删除代售商品
*
*/
void delOnSaleProduct();

/**
*  @brief: 显示所有代售商品信息
*
*/
void displayOnSaleProduct();

#endif // !__ONSALEPRODUCT_H_
