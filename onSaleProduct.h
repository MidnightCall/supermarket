#ifndef __ONSALEPRODUCT_H_
#define __ONSALEPRODUCT_H

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
void runOnSaleProductSystem();

/**
*  @brief: 查询在售商品
*
*/
void queryOnSaleProduct();

/**
*  @brief: 显示所有代售商品信息
*
*/
void displayOnSaleProduct();



#endif // !__ONSALEPRODUCT_H_