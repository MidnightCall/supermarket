#ifndef __SUPPLIER_H_
#define __SUPPLIER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UI.h"
#include "files.h"
#include "linkList.h"
#include "helpfulFunction.h"

extern Node_t* supplierDat;

/**
*  @brief: ���й�Ӧ�̲���
*
*/
void runSupplierSystem();

/**
*  @brief: ���ҹ�Ӧ����Ϣ
*
*/
void querySupplier();

/**
*  @brief: ��ӹ�Ӧ����Ϣ
*
*/
void addSupplier();

/**
*  @brief: ɾ����Ӧ����Ϣ
*
*/
void delSupplier();

/**
*  @brief: ��ʾ���й�Ӧ����Ϣ
*
*/
void displaySupplier();



#endif // !__ONSALEPRODUCT_H_