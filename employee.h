#ifndef __EMPLOYEE_H_
#define __EMPLOYEE_H_

#include "typeCollection.h"


/**
* @brief 运行职工处理模块
*
*/
void runEmployeeManage(void);

/**
* @brief 显示单条员工信息
*
*/
void showSingleEmployee(Employee_t e);

/**
* @brief 显示所有员工信息
* 
*/
void showAllEmployees(void);

/**
* @brief 添加新员工
*/
void addEmployee(void);

/**
* @brief 删除员工
*/
void deleteEmployee(void);

/**
* @brief 查找员工
*/
void findEmployee(void);

/**
* @brief 修改员工信息
*/
void modifyEmployee(void);

#endif