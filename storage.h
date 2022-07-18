/*****************************************************************//**
 * \file   storage.h
 * \brief  �Կ������ܵ�ʵ��
 * 
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#ifndef __STORAGE_H_
#define __STORAGE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UI.h"
#include "files.h"
#include "linkList.h"
#include "helpfulFunction.h"
#include "customLookup.h"

extern Node_t* storageDat, *supplierDat, *onSaleDat, *productDat;
extern Config_t configDat;
extern User_t currentUser;

/**
*  @brief ���п�����ϵͳ
*/
void runStorageSystem(void);

/**
*  @brief ��ѯ�����Ʒ
*
*/
void queryStorage(void);

/**
 * @brief �޸���Ʒ����
 */
void modifyProductInfo(void);

/**
*  @brief ��Ʒ���
*
*/
void inStorage(void);

/**
*  @brief ��Ʒ����
*/
void outStorage(void);

/**
*  @brief ��ʾ���п����Ʒ��Ϣ
*/
void displayStorage(void);

#endif // !__STORAGE_H_