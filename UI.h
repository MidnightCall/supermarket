/*****************************************************************//**
 * \file   UI.h
 * \brief  �Բ˵�������ʾ�ļ���ʵ��
 * 
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#ifndef __UI_H_
#define __UI_H_

#include "typeCollection.h"
#include <stdio.h>

/**
 * \brief չʾ��ʼ����Ļ�ӭ��Ϣ
 *
 */
void showWelcomeMessage(void);

/**
 * \brief չʾ��¼��ע��Ĳ˵�ҳ��
 */
void showLoginMessage(void);

/**
 * \brief չʾ��������Ա����ѡ��ҳ��
 */
void showSuperAdminMenu(void);

/**
 * \brief չʾ����Ա����ѡ��ҳ��
 *
 */
void showAdminMenu(void);

 /**
  * \brief չʾ��ͨ�û�����ѡ��ҳ��
  *
  */
void showUserMenu(void);

/**
 * \brief չʾԱ������ҳ��
 */
void showEmployeeBusinessMenu(void);

/**
 * \brief չʾ��Ӧ�̹���ҳ��
 *
 */
void showSupplierBusinessMenu(void);

/**
 * \brief չʾ��������ҳ��
 *
 */
void showOrderBusinessMenu(void);

/**
 * \brief չʾ����ǰ����ҳ��
 *
 */
void showCurrentOrderMenu(void);

/**
 * \brief չʾ������ҳ��
 *
 */
void showStorageBusinessMenu(void);

/**
 * \brief չʾ������Ʒ����ҳ��
 *
 */
void showOnSaleBusinessMenu(void);

/**
 * \brief չʾ����ҳ��
 *
 */
void showExitMessage(void);

/**
 * \brief չʾ�˻��������
 *
 */
void showAccountBusinessMenu(void);

/**
 * \brief չʾ��Ʒ�������
 *
 */
void showProductMenu(void);

/**
 * \brief ��ʾ�û���Ϣ��ͷ
 *
 * \param user Ҫ��ʾ��Ӧ��Ϣ���û�
 */
void showTitle(User_t user);

#endif