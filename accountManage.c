/* ��������Ա��Ȩ���û����� */

#include "accountManage.h"
#include "helpfulFunction.h"
#include "customLookup.h"
#include "linkList.h"
#include "typeCollection.h"

extern Node_t* userDat;
extern User_t currentUser;

/* �ֲ�����ģ�� */
static int getChoice();

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

void queryUser(void)
{
	User_t* tUser = NULL;
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T��ѯ�û��T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
	unsigned int tId = 0, index = 0;
	while (true)
	{
		tId = getNonNegativeNumber("�˺� ID: ");
		if (tId < 10000 || tId > 99999)
		{
			printf("������� ID ��Ч�����������롣\b\n");
			continue;
		}
		index = findIndexByID_d(userDat, tId, &tUser);
		if (0 == index)
		{
			printf("û�з����������û���\b");
			system("pause");
			return;
		}
		showSingleUser(*tUser);
		break;
	}
	system("pause");
}

void modifyUserPermission(void)
{
	User_t* tUser;
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�޸�Ȩ�ިT�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
	unsigned int tId = 0, index = 0;
	while (true)
	{
		tId = getNonNegativeNumber("�˺� ID");

		if (tId < 10000 || tId > 99999)
		{
			printf("������� ID ��Ч�����������롣\b\n");
			continue;
		}

		if (tId == 10000)
		{
			printf("���޷��޸ĳ�������Ա [10000] ��Ȩ�ޡ�\n");
			system("pause");
			return;
		}

		index = findIndexByID_d(userDat, tId, &tUser);
		if (0 == index)
		{
			printf("û�з����������û���\b");
			PAUSE;
			return;
		}
		showSingleUser(*tUser);
		break;
	}

	unsigned int op = 0;
	while (true)
	{
		op = getNonNegativeNumber("��Ҫ���ĵ���Ŀ��Ȩ��\n[0. ��ͨ�û�, 1. ����Ա]");
		if (op < 0 || op > 1)
		{
			printf("�������Ȩ�޵ȼ���Ч�����������롣\b\n");
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
		tId = getNonNegativeNumber("�˻� ID");
		if (tId < 10000 || tId > 99999)
		{
			printf("������� ID ��Ч��");
			PAUSE;
			return;
		}

		if (tId == 10000)
		{
			printf("���޷�ɾ����������Ա [10000].\n");
			PAUSE;
			return;
		}

		index = findIndexByID_d(userDat, tId, &tUser);
		if (0 == index)
		{
			printf("û�з����������û���");
			PAUSE;
			return;
		}
		showSingleUser(*tUser);
		break;
	}

	while (true)
	{
		//getchar();
		printf("ȷ��Ҫɾ����[y/n]: ");
		char deleteOp = '\0';
		scanf("%c", &deleteOp);
		if (deleteOp != 'y' && deleteOp != 'n' && deleteOp != 'Y' && deleteOp != 'N')
		{
			printf("������Ĳ�����Ч�����������롣\b\n");
			continue;
		}
		if (deleteOp == 'y' || deleteOp == 'Y')
		{
			del(userDat, index);
			printf("�û�ɾ���ɹ���\n");
			showAllUsers(userDat);
			break;
		}
		if (deleteOp == 'n' || deleteOp == 'N')
			return;
	}
	system("pause");

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
		HINT;
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);
	flush();

	return choice;
}

void showSingleUser(User_t e)
{
	printf("�������������������Щ����������������������˺���Ϣ������������������������������������������\n");
	printf("�� %7s�� %12s�� %24s��\n", "ID", "����", "Ȩ�޵ȼ�");
	printf("�������������������੤�������������������������੤��������������������������������������������������\n");
	printUserInfo(&e);
	printf("�������������������ة��������������������������ة���������������������������������������������������\n");
}

void showAllUsers(void)
{
	printf("�������������������Щ����������������������˺���Ϣ������������������������������������������\n");
	printf("�� %7s�� %12s�� %24s��\n", "ID", "����", "Ȩ�޵ȼ�");
	printf("�������������������੤�������������������������੤��������������������������������������������������\n");
	printList(userDat, printUserInfo, false);
	printf("�������������������ة��������������������������ة���������������������������������������������������\n");
	return;
}