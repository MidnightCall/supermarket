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
 * @brief 展示功能选择页面
 *
 */
void showMainMenu();

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
 * @brief 展示结束页面
 *
 */
void showExitMessage();

#endif