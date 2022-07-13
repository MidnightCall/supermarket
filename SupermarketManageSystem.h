/**
 * @file SupermarketManageSystem.h
 * @brief 超市管理系统相关函数
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef __SUPERMARKETMANAGESYSTEM_H_
#define __SUPERMARKETMANAGESYSTEM_H_

#include <stdlib.h>
#include "account.h"
#include "UI.h"
#include "superAdminSystem.h"

 /**
  * @brief 启动超市管理系统
  */
void systemStart(void);

/**
 * @brief 登录/注册账号
 */
void logInStart(void);

/**
* @brief 从文件中加载数据
*/
void initData(void);

/**
* @brief 将数据保存到文件中并释放链表使用的内存
*/
void saveData(void);

/**
 * @brief 启动员工管理模块
 *
 */
void employeeModuleStart();

/**
 * @brief 启动供应商管理模块
 *
 */
void supplierModuleStart();

/**
 * @brief 启动库存管理模块
 *
 */
void storageModuleStart();

/**
 * @brief 启动订单管理模块
 *
 */
void orderModuleStart();

#endif 