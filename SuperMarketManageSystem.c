#include "SupermarketManageSystem.h"

void systemStart()
{
	showWelcomeMessage();
	logInStart();
}

/**
 * @brief 登录/注册账号
 */
void logInStart()
{
	runLogIn();
}


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