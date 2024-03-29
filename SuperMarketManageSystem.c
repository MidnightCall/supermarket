/*****************************************************************//**
 * \file   SuperMarketManageSystem.c
 * \brief  系统启动和初始化的实现
 * 
 * \author moonlightvigil
 * \date   July 2022
 *********************************************************************/

#include "SupermarketManageSystem.h"
#include "linkList.h"
#include "files.h"
#include "normalUser.h"
#include <io.h>
#include <direct.h>

Node_t* userDat, * employeeDat, * productDat, * storageDat, * supplierDat, * orderDat;
Config_t configDat;
User_t currentUser = {99999, "DEBUG", -1};

/**
 * \brief 启动超市管理系统
 */
void systemStart()
{
	initData();
	system("color 70");
	system("title 超市管理系统 v2.0");
	logInStart();
	saveData();
}

/**
 * \brief 登录/注册账号
 */
void logInStart()
{
	while (1)
	{
		runLogIn();

		switch (currentUser.permission)
		{
		case COMMON:
			runNormalUserSystem();
			break;
		case ADMIN:
			runAdminSystem();
			break;
		case SU:
			runSuperAdminSystem();
			break;
		default:
			continue;
		}
	}
}

/**
* \brief 从文件中加载数据
*/
void initData(void)
{
	userDat = newList();
	employeeDat = newList();
	productDat = newList();
	storageDat = newList();
	supplierDat = newList();
	orderDat = newList();

	if (-1 == _access("data", 0)) /* 文件夹不存在就先新建文件夹 */
	{
		_mkdir("data");
	}

	loadFile(FILE_USER, userDat, sizeof(User_t), &configDat.maxId_User);
	loadFile(FILE_EMPLOYEE, employeeDat, sizeof(Employee_t), &configDat.maxId_Employee);
	loadFile(FILE_PRODUCT, productDat, sizeof(OnSale_t), NULL);
	loadFile(FILE_STORAGE, storageDat, sizeof(Storage_t), &configDat.maxId_Product);
	loadFile(FILE_SUPPLIER, supplierDat, sizeof(Supplier_t), &configDat.maxId_Supplier);
	loadFile(FILE_ORDER, orderDat, sizeof(Order_t), &configDat.maxId_Order);
	initConfig();
	return;
}

/**
* \brief 将数据保存到文件中并释放链表使用的内存
*/
void saveData(void)
{
	writeFile(FILE_USER, userDat, sizeof(User_t));
	writeFile(FILE_EMPLOYEE, employeeDat, sizeof(Employee_t));
	writeFile(FILE_PRODUCT, productDat, sizeof(OnSale_t));
	writeFile(FILE_STORAGE, storageDat, sizeof(Storage_t));
	writeFile(FILE_SUPPLIER, supplierDat, sizeof(Supplier_t));
	writeFile(FILE_ORDER, orderDat, sizeof(Order_t));

	freeList(userDat);
	freeList(employeeDat);
	freeList(productDat);
	freeList(storageDat);
	freeList(supplierDat);
	freeList(orderDat);
	return;
}