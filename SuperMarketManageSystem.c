#include "SupermarketManageSystem.h"
#include "linkList.h"
#include "files.h"

Node_t* userDat, * employeeDat, * productDat, * storageDat, * supplierDat, * orderDat;
Config_t configDat;
User_t currentUser;

void systemStart()
{
	initData();
	showWelcomeMessage();
	runAdminSystem();
	saveData();
}

/**
 * @brief 登录/注册账号
 */
void logInStart()
{
	runLogIn();
}

void initData(void)
{
	userDat = newList();
	employeeDat = newList();
	productDat = newList();
	storageDat = newList();
	supplierDat = newList();
	orderDat = newList();

	loadFile(FILE_USER, userDat, sizeof(User_t), &configDat.maxId_User);
	loadFile(FILE_EMPLOYEE, employeeDat, sizeof(Employee_t), &configDat.maxId_Employee);
	loadFile(FILE_PRODUCT, productDat, sizeof(OnSale_t), &configDat.maxId_Product);
	loadFile(FILE_STORAGE, storageDat, sizeof(Storage_t), NULL);
	loadFile(FILE_SUPPLIER, supplierDat, sizeof(Supplier_t), &configDat.maxId_Supplier);
	loadFile(FILE_ORDER, orderDat, sizeof(Order_t), &configDat.maxId_Order);
	loadConfig();

	printConfig(); /* Debug */
	return;
}

void saveData(void)
{
	writeFile(FILE_USER, userDat, sizeof(User_t));
	writeFile(FILE_EMPLOYEE, employeeDat, sizeof(Employee_t));
	writeFile(FILE_PRODUCT, productDat, sizeof(OnSale_t));
	writeFile(FILE_STORAGE, storageDat, sizeof(Storage_t));
	writeFile(FILE_SUPPLIER, supplierDat, sizeof(Supplier_t));
	writeFile(FILE_ORDER, orderDat, sizeof(Order_t));
	saveConfig();

	freeList(userDat);
	freeList(employeeDat);
	freeList(productDat);
	freeList(storageDat);
	freeList(supplierDat);
	freeList(orderDat);
	return;
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