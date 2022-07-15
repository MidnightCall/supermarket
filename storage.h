#ifndef __STORAGE_H_
#define __STORAGE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UI.h"
#include "files.h"
#include "linkList.h"
#include "helpfulFunction.h"
#include "customLookup.h"

extern Node_t* storageDat, *supplierDat, *onSale;
extern Config_t configDat;

/**
*  @brief: ���п�����ϵͳ
*
*/
void runStorageSystem();

/**
*  @brief: ��ѯ�����Ʒ
*
*/
void queryStorage();

/**
*  @brief: ���
*
*/
void inStorage();

/**
*  @brief: ����
*/
void outStorage();

/**
*  @brief: ��ʾ���п����Ʒ��Ϣ
*
*/
void displayStorage();



#endif // !__STORAGE_H_