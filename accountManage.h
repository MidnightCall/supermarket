/*****************************************************************//**
 * \file   accountManage.h
 * \brief  �Գ�������Ա (SU Ȩ��) ���û������ܵ�ʵ��
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
 * @brief �����û�����ģ��
 */
void runAccountManage(void);

/**
 * @brief �����û���Ϣ
 */
void queryUser(void);

/**
 * @brief ɾ���û�
 */
void deleteUser(void);

/**
 * @brief �����û�Ȩ��
 */
void modifyUserPermission(void);

/**
 * @brief ��ʾ�����û���Ϣ
 */
void showSingleUser(User_t e);

/**
 * @brief ��ʾ�����û���Ϣ
 */
void showAllUsers(void);

#endif


