/**
 * @file SupermarketManageSystem.h
 * @brief ���й���ϵͳ��غ���
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef __SUPERMARKETMANAGESYSTEM_H_
#define __SUPERMARKETMANAGESYSTEM_H_

#include <stdlib.h>
#include "account.h"
#include "UI.h"
#include "superAdminSystem.h"

 /**
  * @brief �������й���ϵͳ
  */
void systemStart(void);

/**
 * @brief ��¼/ע���˺�
 */
void logInStart(void);

/**
* @brief ���ļ��м�������
*/
void initData(void);

/**
* @brief �����ݱ��浽�ļ��в��ͷ�����ʹ�õ��ڴ�
*/
void saveData(void);

/**
 * @brief ����Ա������ģ��
 *
 */
void employeeModuleStart();

/**
 * @brief ������Ӧ�̹���ģ��
 *
 */
void supplierModuleStart();

/**
 * @brief ����������ģ��
 *
 */
void storageModuleStart();

/**
 * @brief ������������ģ��
 *
 */
void orderModuleStart();

#endif 