#ifndef __EMPLOYEE_H_
#define __EMPLOYEE_H_

#include "typeCollection.h"


/**
* @brief ����ְ������ģ��
*
*/
void runEmployeeManage(void);

/**
* @brief ��ʾ����Ա����Ϣ
*
*/
void showSingleEmployee(Employee_t e);

/**
* @brief ��ʾ����Ա����Ϣ
* 
*/
void showAllEmployees(void);

/**
* @brief �����Ա��
*/
void addEmployee(void);

/**
* @brief ɾ��Ա��
*/
void deleteEmployee(void);

/**
* @brief ����Ա��
*/
void findEmployee(void);

/**
* @brief �޸�Ա����Ϣ
*/
void modifyEmployee(void);

#endif