#ifndef __ONSALEPRODUCT_H_
#define __ONSALEPRODUCT_H

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
void runOnSaleProductSystem();

/**
*  @brief: ��ѯ������Ʒ
*
*/
void queryOnSaleProduct();

/**
*  @brief: ��ʾ���д�����Ʒ��Ϣ
*
*/
void displayOnSaleProduct();



#endif // !__ONSALEPRODUCT_H_