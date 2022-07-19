/*****************************************************************//**
 * \file   order.h
 * \brief  对管理员 (ADMIN 权限) 的查询已交付订单功能和对普通用户 (COMMON 权限)
 *         的查询商品信息、对订单内商品进行增删操作的实现
 *
 * \author praist
 * \date   July 2022
 *********************************************************************/

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
*  \brief 运行订单审核模块 (供管理员使用)
*/
void runOrderSystem(void);

/**
*  \brief 运行当前订单管理模块 (供普通用户使用)
*/
void runNormalUserOrderSystem(void);

/**
*  \brief 显示所有订单信息
* 
*  \param showSum 是否显示总金额
*/
void displayOrder(bool showSum);

/**
*  \brief 查询订单信息
*/
void queryOrder(void);

/**
*  \brief 根据时间查询订单信息
*/
void queryOrderByTime(void);

/**
*  \brief 计算总营业额
*/
float calTurnover(void);

/**
*  \brief 计算总利润
*/
float calProfit(void);

/**
*  \brief 向当前订单添加商品
*/
void addProductToCurrentOrder(void);

/**
*  \brief 删除当前订单的商品
*/
void delProductFromCurrentOrder(void);

/**
*  \brief 更改当前订单的商品数量
*/
void modifyProductFromCurrentOrder(void);

/**
*  \brief 打印当前订单信息
*/
void showCurrentOrderInfo(void);

/**
*  \brief 显示当前订单的合计金额
*/
void showTurnOverInCurrentOrder(void);

/**
*  \brief: 交付订单
*/
void submitCurrentOrder(void);

#endif // !__ORDER_H_
