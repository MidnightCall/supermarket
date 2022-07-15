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

extern Node_t* productDat;

/**
*  @brief: ����������Ʒ����
*
*/
void runOnSaleSystem();

/**
*  @brief: ��ѯ������Ʒ
*
*/
void queryOnSaleProduct();

/**
*  @brief: ��Ӵ�����Ʒ
*
*/
void addOnSaleProduct(Product_t product, int allowance);

/**
*  @brief: ɾ��������Ʒ
*
*/
void delOnSaleProduct();

/**
*  @brief: ��ʾ���д�����Ʒ��Ϣ
*
*/
void displayOnSaleProduct();

#endif // !__ONSALEPRODUCT_H_
