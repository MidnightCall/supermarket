#ifndef __ORDER_H_
#define __ORDER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UI.h"
#include "linkList.h"
#include "files.h"
#include "customLookup.h"
#include "typeCollection.h"

extern Node_t* orderDat, *productDat;
Order_t currentOrder;
int currentIndex = 0;

/**
*  @brief: ���ж������ģ��(������Աʹ��)
*
*/
void runOrderSystem();

/**
*  @brief: ���е�ǰ��������ģ��(������Աʹ��)
*
*/
void runNormalUserOrderSystem();

/**
*  @brief: ��ʾ���ж�����Ϣ
*
*/
void displayOrder();

/**
*  @brief: ��ѯ������Ϣ
*
*/
void queryOrder();

/**
*  @brief: ������Ӫҵ��
*
*/
void calTurnover();

/**
*  @brief: ��ǰ����������Ʒ
*
*/
void addProductToCurrentOrder();

/**
*  @brief: ɾ����ǰ��������Ʒ
*
*/
void delProductFromCurrentOrder();

/**
*  @brief: ���ĵ�ǰ��������Ʒ����
*
*/
void modifyProductFromCurrentOrder();

/**
*  @brief: �����ܼ�
*
*/
void calTurnOverInCurrentOrder();

/**
*  @brief: ��������
*
*/
void submitCurrentOrder();

#endif // !__ORDER_H_