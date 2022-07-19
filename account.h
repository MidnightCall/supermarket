/*****************************************************************//**
 * \file   account.h
 * \brief  对用户登录和注册功能的实现
 * 
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#ifndef __ACCOUNT_H_
#define __ACCOUNT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "typeCollection.h"
#include "UI.h"
#include "helpfulFunction.h"
#include "linkList.h"
#include "files.h"
#include "helpfulFunction.h"
#include "customLookup.h"

extern Node_t* userDat;
extern User_t currentUser;


/**
 * \brief 进入登录和注册的选择菜单
 */
void runLogIn(void);

/** 
 * \brief 注册账号
 */
void registration(void);

/** 
 * \brief 登录账号
 */
void logIn(void);

#endif // !REGGISTER_H_

