/*****************************************************************//**
 * \file   accountManage.h
 * \brief  对超级管理员 (SU 权限) 的用户管理功能的实现
 * 
 * \author East Monster
 * \date   July 2022
 *********************************************************************/
#ifndef __ACCOUNTMANAGE_H_
#define __ACCOUNTMANAGE_H_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "files.h"
#include "UI.h"
#include "typeCollection.h"
#include "helpfulFunction.h"

/**
 * @brief 运行用户处理模块
 */
void runAccountManage(void);

/**
 * @brief 查找用户信息
 */
void queryUser(void);

/**
 * @brief 删除用户
 */
void deleteUser(void);

/**
 * @brief 更改用户权限
 */
void modifyUserPermission(void);

/**
 * @brief 显示单条用户信息
 */
void showSingleUser(User_t e);

/**
 * @brief 显示所有用户信息
 */
void showAllUsers(void);

#endif


