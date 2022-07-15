#ifndef __ORDER_H_
#define __ORDER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UI.h"
#include "linkList.h"
#include "files.h"
#include "customLookup.h"
#include "typeCollection.h"

extern Node_t* orderDat;

/**
*  @brief: 运行订单审核模块
*
*/
void runOrderSystem();

/**
*  @brief: 显示所有订单信息
*
*/
void displayOrder();

/**
*  @brief: 查询订单信息
*
*/
void queryOrder();

/**
*  @brief: 计算总营业额
*
*/
void calTurnover();

#endif // !__ORDER_H_
