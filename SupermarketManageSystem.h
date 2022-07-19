/*****************************************************************//**
 * \file   SuperMarketManageSystem.h
 * \brief  ϵͳ�����ͳ�ʼ����ʵ��
 *
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#ifndef __SUPERMARKETMANAGESYSTEM_H_
#define __SUPERMARKETMANAGESYSTEM_H_

#include <stdlib.h>
#include "account.h"
#include "UI.h"
#include "superAdminSystem.h"
#include "Admin.h"

/**
 * \brief �������й���ϵͳ
 */
void systemStart(void);

/**
 * \brief ��¼/ע���˺�
 */
void logInStart(void);

/**
* \brief ���ļ��м�������
*/
void initData(void);

/**
* \brief �����ݱ��浽�ļ��в��ͷ�����ʹ�õ��ڴ�
*/
void saveData(void);
#endif 