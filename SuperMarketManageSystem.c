#include "SupermarketManageSystem.h"
#include "linkList.h"
#include "files.h"

Node_t* userDat, * employeeDat, * productDat, * storageDat, * supplierDat, * orderDat;
User_t currentUser;

void systemStart()
{
	initData();
	showWelcomeMessage();
	runAdminSystem();
	saveData();
}

/**
 * @brief ��¼/ע���˺�
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

	loadFile(FILE_USER, userDat, sizeof(User_t));
	loadFile(FILE_EMPLOYEE, employeeDat, sizeof(Employee_t));
	loadFile(FILE_PRODUCT, productDat, sizeof(OnSale_t));
	loadFile(FILE_STORAGE, storageDat, sizeof(Storage_t));
	loadFile(FILE_SUPPLIER, supplierDat, sizeof(Supplier_t));
	loadFile(FILE_ORDER, orderDat, sizeof(Order_t));
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

	freeList(userDat);
	freeList(employeeDat);
	freeList(productDat);
	freeList(storageDat);
	freeList(supplierDat);
	freeList(orderDat);
	return;
}

/**
 * @brief ����Ա������ģ��
 *
 */
void employeeModuleStart();

/**
 * @brief ������Ӧ�̹���ģ��
 *
 */
void supplierModuleStart();

/**
 * @brief ����������ģ��
 *
 */
void storageModuleStart();

/**
 * @brief ������������ģ��
 *
 */
void orderModuleStart();