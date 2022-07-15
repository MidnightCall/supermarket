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

extern Node_t* orderDat;

/**
*  @brief: ���ж������ģ��
*
*/
void runOrderSystem();

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

#endif // !__ORDER_H_
