/*****************************************************************//**
 * \file   supplier.h
 * \brief  �Թ�Ӧ�̹����ܵ�ʵ��
 * 
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#ifndef __SUPPLIER_H_
#define __SUPPLIER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UI.h"
#include "files.h"
#include "linkList.h"
#include "helpfulFunction.h"

extern Node_t* supplierDat,* productDat;

/**
*  \brief ���й�Ӧ�̹���ģ��
*/
void runSupplierSystem(void);

/**
*  \brief ���ҹ�Ӧ����Ϣ
*
*/
void querySupplier(void);

/**
*  \brief ��ӹ�Ӧ����Ϣ
*
*/
void addSupplier(void);

/**
*  \brief ɾ����Ӧ����Ϣ
*/
void delSupplier(void);

/**
 * \brief �޸Ĺ�Ӧ����Ϣ
 */
void modifySupplier(void);

/**
*  \brief ��ʾ���й�Ӧ����Ϣ
*/
void displaySupplier(void);

#endif // !__ONSALEPRODUCT_H_