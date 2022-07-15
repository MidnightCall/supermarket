#ifndef __ORDER_H_
#define __ORDER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "UI.h"
#include "linkList.h"
#include "files.h"
#include "customLookup.h"
#include "typeCollection.h"




/**
*  @brief: 运行订单审核模块(供管理员使用)
*
*/
void runOrderSystem();

/**
*  @brief: 运行当前订单管理模块(供收银员使用)
*
*/
void runNormalUserOrderSystem();

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

/**
*  @brief: 向当前订单添加商品
*
*/
void addProductToCurrentOrder();

/**
*  @brief: 删除当前订单的商品
*
*/
void delProductFromCurrentOrder();

/**
*  @brief: 更改当前订单的商品数量
*
*/
void modifyProductFromCurrentOrder();

/**
*  @brief: 打印当前订单信息
*
*/
void showCurrentOrderInfo();

/**
*  @brief: 计算总价
*
*/
void calTurnOverInCurrentOrder();

/**
*  @brief: 交付订单
*
*/
void submitCurrentOrder();

#endif // !__ORDER_H_
