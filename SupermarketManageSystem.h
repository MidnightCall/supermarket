/*****************************************************************//**
 * \file   SuperMarketManageSystem.h
 * \brief  系统启动和初始化的实现
 *
 * \author moonlightvigil
 * \date   July 2022
 *********************************************************************/

#ifndef __SUPERMARKETMANAGESYSTEM_H_
#define __SUPERMARKETMANAGESYSTEM_H_

#include <stdlib.h>
#include "account.h"
#include "UI.h"
#include "superAdminSystem.h"
#include "Admin.h"

/**
 * \brief 启动超市管理系统
 */
void systemStart(void);

/**
 * \brief 登录/注册账号
 */
void logInStart(void);

/**
* \brief 从文件中加载数据
*/
void initData(void);

/**
* \brief 将数据保存到文件中并释放链表使用的内存
*/
void saveData(void);
#endif 