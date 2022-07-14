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
*  @brief: �����û�����ģ��
* 
*/
void runAccountManage();

/**
*  @brief: �����û��˻�
*
*/
void queryUser();

/**
*  @brief: ɾ���û��˻�
*
*/
void deleteUser();

/**
*  @brief: �����û�Ȩ��
*
*/
void modifyUserPermission();

void showSingleUser(User_t e);

void showAllUsers(void);

#endif