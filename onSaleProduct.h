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
*  @brief 运行在售商品操作
*
*/
void runOnSaleProductSystem();

/**
*  @brief 查询在售商品
*
*/
void queryOnSaleProduct();

/**
*  @brief 显示所有待售商品信息
*
*/
void displayOnSaleProduct(void);

/**
 * @brief 将商品下架
 */
void offshelfOnSaleProduct();

#endif // !__ONSALEPRODUCT_H_


