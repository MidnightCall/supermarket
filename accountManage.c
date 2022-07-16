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
			break;
		case 1:
			showAllUsers();
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
		case 5:
			return;
		}
	}
}

void queryUser(void)
{
	User_t* tUser = NULL;
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("====================��ѯ�˻�======================\n");
	unsigned int tId = 0, index = 0;
	while (true)
	{
		printf("�����˺� ID: ");
		scanf("%u", &tId);
		if (tId < 10000 || tId > 99999)
		{
			printf("������� ID ��Ч�����������롣\b\n");
			continue;
		}
		index = findIndexByID_d(userDat, tId, &tUser);
		if (0 == index)
		{
			printf("û�з���������Ա����\b");
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

	printf("====================�޸�Ȩ��======================\n");
	unsigned int tId = 0, index = 0;
	while (true)
	{
		printf("�����˺� ID: ");
		scanf("%u", &tId);

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
			printf("û�з���������Ա����\b");
			system("pause");
			return;
		}
		showSingleUser(*tUser);
		break;
	}

	unsigned int op = 0;
	while (true)
	{
		printf("������Ҫ���ĵ���Ŀ��Ȩ��\n[0. ��ͨ�û�, 1. ����Ա]: ");
		scanf("%u", &op);
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
	system("pause");
	return;

}

void deleteUser(void)
{
	User_t* tUser = NULL;

	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("====================ɾ���˻�======================\n");
	unsigned int index = 0;
	while (true)
	{
		printf("�������˻� ID: ");
		unsigned int tId = 0;
		scanf("%u", &tId);
		if (tId < 10000 || tId > 99999)
		{
			printf("������� ID ��Ч�����������롣\n");
			system("pause");
			continue;
		}

		if (tId == 10000)
		{
			printf("���޷�ɾ����������Ա [10000]��\n");
			system("pause");
			return;
		}

		index = findIndexByID_d(userDat, tId, &tUser);
		if (0 == index)
		{
			printf("û�з����������˻���");
			system("pause");
			return;
		}
		showSingleUser(*tUser);
		break;
	}

	while (true)
	{
		getchar();
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
			printf("Ա��ɾ���ɹ���\n");
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
	showTitle(currentUser);
	do
	{
		showAccountBusinessMenu();
		printf(">>> ");
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);
	flush();

	return choice;
}

void showSingleUser(User_t e)
{
	printf("--------------------�˺���Ϣ--------------------\n");
	printf("| %7s| %12s| %22s|\n", "ID", "����", "Ȩ�޵ȼ�");
	printf("|--------+-------------+-----------------------|\n");
	printUserInfo(&e);
	printf("------------------------------------------------\n");
}

void showAllUsers(void)
{
	printf("--------------------�˺���Ϣ--------------------\n");
	printf("| %7s| %12s| %22s|\n", "ID", "����", "Ȩ�޵ȼ�");
	printf("|--------+-------------+-----------------------|\n");
	printList(userDat, printUserInfo, false);
	printf("------------------------------------------------\n");
	system("pause");
	return;
}