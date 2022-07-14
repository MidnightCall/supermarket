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
*  @brief: 运行用户处理模块
* 
*/
void runAccountManage();

/**
*  @brief: 查找用户账户
*
*/
void queryUser();

/**
*  @brief: 删除用户账户
*
*/
void deleteUser();

/**
*  @brief: 更改用户权限
*
*/
void modifyUserPermission();

void showSingleUser(User_t e);

void showAllUsers(void);

#endif