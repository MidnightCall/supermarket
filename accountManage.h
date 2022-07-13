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
*  @brief: �����û�Ȩ��
* 
*/
void modifyUserPermission();

/**
*  @brief: ɾ���û��˻�
*
*/
void deleteUserInfo();

/**
*  @brief: ����û�
*
*/
void addUserInfo();

#endif