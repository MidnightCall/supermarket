/*****************************************************************//**
 * \file   order.h
 * \brief  �Թ���Ա (ADMIN Ȩ��) �Ĳ�ѯ�ѽ����������ܺͶ���ͨ�û� (COMMON Ȩ��)
 *         �Ĳ�ѯ��Ʒ��Ϣ���Զ�������Ʒ������ɾ������ʵ��
 *
 * \author praist
 * \date   July 2022
 *********************************************************************/

#ifndef __ORDER_H_
#define __ORDER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "UI.h"
#include "linkList.h"
#include "files.h"
#include "customLookup.h"
#include "typeCollection.h"

/**
*  \brief ���ж������ģ�� (������Աʹ��)
*/
void runOrderSystem(void);

/**
*  \brief ���е�ǰ��������ģ�� (����ͨ�û�ʹ��)
*/
void runNormalUserOrderSystem(void);

/**
*  \brief ��ʾ���ж�����Ϣ
* 
*  \param showSum �Ƿ���ʾ�ܽ��
*/
void displayOrder(bool showSum);

/**
*  \brief ��ѯ������Ϣ
*/
void queryOrder(void);

/**
*  \brief ����ʱ���ѯ������Ϣ
*/
void queryOrderByTime(void);

/**
*  \brief ������Ӫҵ��
*/
float calTurnover(void);

/**
*  \brief ����������
*/
float calProfit(void);

/**
*  \brief ��ǰ���������Ʒ
*/
void addProductToCurrentOrder(void);

/**
*  \brief ɾ����ǰ��������Ʒ
*/
void delProductFromCurrentOrder(void);

/**
*  \brief ���ĵ�ǰ��������Ʒ����
*/
void modifyProductFromCurrentOrder(void);

/**
*  \brief ��ӡ��ǰ������Ϣ
*/
void showCurrentOrderInfo(void);

/**
*  \brief ��ʾ��ǰ�����ĺϼƽ��
*/
void showTurnOverInCurrentOrder(void);

/**
*  \brief: ��������
*/
void submitCurrentOrder(void);

#endif // !__ORDER_H_
