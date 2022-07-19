/*****************************************************************//**
 * \file   UI.h
 * \brief  对菜单界面显示的集中实现
 * 
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#ifndef __UI_H_
#define __UI_H_

#include "typeCollection.h"
#include <stdio.h>

/**
 * \brief 展示初始界面的欢迎信息
 *
 */
void showWelcomeMessage(void);

/**
 * \brief 展示登录与注册的菜单页面
 */
void showLoginMessage(void);

/**
 * \brief 展示超级管理员功能选择页面
 */
void showSuperAdminMenu(void);

/**
 * \brief 展示管理员功能选择页面
 *
 */
void showAdminMenu(void);

 /**
  * \brief 展示普通用户功能选择页面
  *
  */
void showUserMenu(void);

/**
 * \brief 展示员工管理页面
 */
void showEmployeeBusinessMenu(void);

/**
 * \brief 展示供应商管理页面
 *
 */
void showSupplierBusinessMenu(void);

/**
 * \brief 展示订单管理页面
 *
 */
void showOrderBusinessMenu(void);

/**
 * \brief 展示处理当前订单页面
 *
 */
void showCurrentOrderMenu(void);

/**
 * \brief 展示库存管理页面
 *
 */
void showStorageBusinessMenu(void);

/**
 * \brief 展示在售商品处理页面
 *
 */
void showOnSaleBusinessMenu(void);

/**
 * \brief 展示结束页面
 *
 */
void showExitMessage(void);

/**
 * \brief 展示账户管理界面
 *
 */
void showAccountBusinessMenu(void);

/**
 * \brief 展示商品管理界面
 *
 */
void showProductMenu(void);

/**
 * \brief 显示用户信息表头
 *
 * \param user 要显示对应信息的用户
 */
void showTitle(User_t user);

#endif