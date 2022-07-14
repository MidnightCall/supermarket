#ifndef __PRODUCT_H_
#define __PRODUCT_H

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
*  @brief: 运行商品操作
*
*/
void runProductSystem();

/**
*  @brief: 查询商品
*
*/
void queryProduct();

/**
*  @brief: 添加代售商品
*
*/
void addProduct();

/**
*  @brief: 删除商品
*
*/
void delProduct();

/**
*  @brief: 显示所有代售商品信息
*
*/
void displayProduct();



#endif // !__ONSALEPRODUCT_H_