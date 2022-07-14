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

/*
* 操作：运行登录/注册系统
*/
void runLogIn();

/*
* 操作：显示操作菜单、读取用户的选择的操作
* 后置条件：显示操作菜单
*/
int getChoice();

/*
* 操作：注册账号
*/
void registration();

/*
* 操作：登录账号
*/
void logIn();

#endif // !REGGISTER_H_
