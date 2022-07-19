/*****************************************************************//**
 * \file   SuperMarketManageSystem.c
 * \brief  ϵͳ�����ͳ�ʼ����ʵ��
 * 
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#include "SupermarketManageSystem.h"
#include "linkList.h"
#include "files.h"
#include "normalUser.h"

Node_t* userDat, * employeeDat, * productDat, * storageDat, * supplierDat, * orderDat;
Config_t configDat;
User_t currentUser = {99999, "DEBUG", -1};

/**
 * \brief �������й���ϵͳ
 */
void systemStart()
{
	initData();
	system("title ���й���ϵͳ v2.0");
	logInStart();
	saveData();
}

/**
 * \brief ��¼/ע���˺�
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
* \brief ���ļ��м�������
*/
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
	return;
}

/**
* \brief �����ݱ��浽�ļ��в��ͷ�����ʹ�õ��ڴ�
*/
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