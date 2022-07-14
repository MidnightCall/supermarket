#ifndef __PRODUCT_H_
#define __PRODUCT_H

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
*  @brief: ������Ʒ����
*
*/
void runProductSystem();

/**
*  @brief: ��ѯ��Ʒ
*
*/
void queryProduct();

/**
*  @brief: ��Ӵ�����Ʒ
*
*/
void addProduct();

/**
*  @brief: ɾ����Ʒ
*
*/
void delProduct();

/**
*  @brief: ��ʾ���д�����Ʒ��Ϣ
*
*/
void displayProduct();



#endif // !__ONSALEPRODUCT_H_