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
*  @brief ����������Ʒ����
*
*/
void runOnSaleProductSystem();

/**
*  @brief ��ѯ������Ʒ
*
*/
void queryOnSaleProduct();

/**
*  @brief ��ʾ���д�����Ʒ��Ϣ
*
*/
void displayOnSaleProduct(void);

/**
 * @brief ����Ʒ�¼�
 */
void offshelfOnSaleProduct();

#endif // !__ONSALEPRODUCT_H_


