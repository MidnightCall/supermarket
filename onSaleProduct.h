/*****************************************************************//**
 * \file   onSaleProduct.h
 * \brief  ��������Ʒ�����ܵ�ʵ��
 * 
 * \author praist
 * \date   July 2022
 *********************************************************************/
#ifndef __ONSALEPRODUCT_H_
#define __ONSALEPRODUCT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UI.h"
#include "files.h"
#include "linkList.h"
#include "helpfulFunction.h"
#include "customLookup.h"

extern Node_t* storageDat, * productDat;

/**
*  \brief ����������Ʒ����
*/
void runOnSaleProductSystem(void);

/**
*  \brief ��ѯ������Ʒ
*/
void queryOnSaleProduct();

/**
*  \brief ��ʾ����������Ʒ��Ϣ
*/
void displayOnSaleProduct(void);

/**
 * \brief ��������Ʒ�¼�
 */
void offshelfOnSaleProduct();

#endif // !__ONSALEPRODUCT_H_


