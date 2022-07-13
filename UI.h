#ifndef __UI_H_
#define __UI_H_
/**
 * @file UI.h
 * @brief 功能面板的展示
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdio.h>

 /**
  * @brief 展示进入的菜单页面
  *
  */
void showWelcomeMessage();

/**
 * @brief 展示登录与注册的菜单页面
 *
 */
void showLoginMessage();

/**
 * @brief 展示超级管理员功能选择页面
 *
 */
void showSuperAdminMenu();

/**
 * @brief 展示管理员功能选择页面
 *
 */
void showAdminMenu();

 /**
  * @brief 展示普通用户功能选择页面
  *
  */
void showUserMenu();

/**
 * @brief 展示员工业务办理页面
 *
 */
void showEmployeeBusinessMenu();

/**
 * @brief 展示供应商业务办理页面
 *
 */
void showSupplierBusinessMenu();

/**
 * @brief 展示库存业务办理页面
 *
 */
void showStorageBusinessMenu();

/**
 * @brief 展示订单业务办理页面
 *
 */
void showOrderBusinessMenu();

/**
 * @brief 展示处理当前订单页面
 *
 */
void showCurrentOrderMenu();

/**
 * @brief 展示在售商品处理页面
 *
 */
void showOnSaleBusinessMenu();

/**
 * @brief 展示结束页面
 *
 */
void showExitMessage();

#endif