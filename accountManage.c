/*****************************************************************//**
 * \file   accountManage.c
 * \brief  �Գ�������Ա (SU Ȩ��) ���û������ܵ�ʵ��
 *
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#include "accountManage.h"
#include "helpfulFunction.h"
#include "customLookup.h"
#include "linkList.h"
#include "typeCollection.h"

extern Node_t* userDat;
extern User_t currentUser;

/* �ֲ�����ģ�� */
static int getChoice();

/**
 * \brief �����û�����ģ��
 */
void runAccountManage()
{
	while (1)
	{
		int choice = getChoice();

		switch (choice)
		{
		default:
			return;
		case 1:
			showAllUsers();
			PAUSE;
			break;
		case 2:
			queryUser();
			break;
		case 3:
			modifyUserPermission();
			break;
		case 4:
			deleteUser();
			break;
		}
	}
}

/**
 * \brief �����û���Ϣ
 */
void queryUser(void)
{
	User_t* tUser = NULL;
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T��ѯ�û��T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
	unsigned int tId = 0, index = 0;
	while (true)
	{
		tId = getNonNegativeNumber("�������˺� ID: ");
		if (tId < 10000 || tId > 99999)
		{
			printf("<!> ������� ID ��Ч�����������롣\a\n");
			continue;
		}
		index = findIndexByID_d(userDat, tId, &tUser);
		if (0 == index)
		{
			printf("<!> û�з����������û���\n");
			PAUSE;
			return;
		}
		showSingleUser(*tUser);
		break;
	}

	PAUSE;
	return;
}

/**
 * \brief �����û�Ȩ��
 */
void modifyUserPermission(void)
{
	User_t* tUser = NULL;
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�޸�Ȩ�ިT�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
	unsigned int tId = 0, index = 0;
	while (true)
	{
		tId = getNonNegativeNumber("�������˺� ID: ");

		if (tId < 10000 || tId > 99999)
		{
			printf("<!> ������� ID ��Ч�����������롣\a\n");
			continue;
		}

		if (tId == 10000)
		{
			printf("<!> ���޷��޸ĳ�������Ա [10000] ��Ȩ�ޡ�\a\n");
			PAUSE;
			return;
		}

		index = findIndexByID_d(userDat, tId, &tUser);
		if (0 == index)
		{
			printf("<!> û�з����������û���\a");
			PAUSE;
			return;
		}
		showSingleUser(*tUser);
		break;
	}

	unsigned int op = 0;
	while (true)
	{
		op = getNonNegativeNumber("��������Ҫ���ĵ���Ŀ��Ȩ��\n[0. ��ͨ�û�, 1. ����Ա]: ");
		if (op < 0 || op > 1)
		{
			printf("<!> �������Ȩ�޵ȼ���Ч�����������롣\a\n");
			continue;
		}
		User_t* tUsr = (User_t*)getData(userDat, index);
		tUsr->permission = op;
		break;
	}
	showSingleUser(*tUser);
	printf("Ȩ���޸ĳɹ���");
	PAUSE;
	return;

}

/**
 * \brief ɾ���û�
 */
void deleteUser(void)
{
	showAllUsers();

	User_t* tUser = NULL;

	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�Tɾ���û��T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
	unsigned int index = 0;
	while (true)
	{
		unsigned int tId = 0;
		tId = getNonNegativeNumber("�������˻� ID: ");
		if (tId < 10000 || tId > 99999)
		{
			printf("<!> ������� ID ��Ч��\a");
			PAUSE;
			return;
		}

		if (tId == 10000)
		{
			printf("<!> ���޷�ɾ����������Ա [10000].\a\n");
			PAUSE;
			return;
		}

		index = findIndexByID_d(userDat, tId, &tUser);
		if (0 == index)
		{
			printf("<!> û�з����������û���\a");
			PAUSE;
			return;
		}
		showSingleUser(*tUser);
		break;
	}

	while (true)
	{
		printf("ȷ��Ҫɾ����[y/n]: ");
		char deleteOp = '\0';
		scanf("%c", &deleteOp);
		if (deleteOp != 'y' && deleteOp != 'n' && deleteOp != 'Y' && deleteOp != 'N')
		{
			printf("<!> ������Ĳ�����Ч�����������롣\a\n");
			continue;
		}
		if (deleteOp == 'y' || deleteOp == 'Y')
		{
			del(userDat, index);
			printf("�û�ɾ���ɹ���\n");
			showAllUsers();
			break;
		}
		if (deleteOp == 'n' || deleteOp == 'N')
			return;
	}

	PAUSE;
	return;
}

/**
 * \brief ��ʾ�����û���Ϣ
 */
void showSingleUser(User_t e)
{
	printf("�������������������Щ����������������������˺���Ϣ������������������������������������������\n");
	printf("�� %7s�� %12s�� %24s��\n", "ID", "����", "Ȩ�޵ȼ�");
	printf("�������������������੤�������������������������੤��������������������������������������������������\n");
	printUserInfo(&e);
	printf("�������������������ة��������������������������ة���������������������������������������������������\n");
}

/**
 * \brief ��ʾ�����û���Ϣ
 */
void showAllUsers(void)
{
	printf("�������������������Щ����������������������˺���Ϣ������������������������������������������\n");
	printf("�� %7s�� %12s�� %24s��\n", "ID", "����", "Ȩ�޵ȼ�");
	printf("�������������������੤�������������������������੤��������������������������������������������������\n");
	printList(userDat, printUserInfo, false);
	printf("�������������������ة��������������������������ة���������������������������������������������������\n");
	return;
}

/* �ֲ�����ʵ�� */
static int getChoice()
{
	int choice = 0;
	do
	{
		showTitle(currentUser);
		showAccountBusinessMenu();
		choice = getMenuChoice();
	} while (choice > 5 || choice < 1);

	return choice;
}
