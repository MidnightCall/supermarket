/*****************************************************************//**
 * \file   account.h
 * \brief  ���û���¼��ע�Ṧ�ܵ�ʵ��
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
 * \brief �����¼��ע���ѡ��˵�
 */
void runLogIn(void);

/** 
 * \brief ע���˺�
 */
void registration(void);

/** 
 * \brief ��¼�˺�
 */
void logIn(void);

#endif // !REGGISTER_H_

