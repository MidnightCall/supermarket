/*****************************************************************//**
 * \file   employee.h
 * \brief  对超级管理员 (SU 权限) 的职工管理功能实现
 * 
 * \author praist
 * \date   July 2022
 *********************************************************************/
#ifndef __EMPLOYEE_H_
#define __EMPLOYEE_H_

#include "typeCollection.h"

/**
* \brief 运行职工管理模块
*/
void runEmployeeManage(void);

/**
* \brief 添加新员工
*/
void addEmployee(void);

/**
* \brief 删除员工
*/
void deleteEmployee(void);

/**
* \brief 查找员工
*/
void findEmployee(void);

/**
* \brief 修改员工信息
*/
void modifyEmployee(void);

#endif