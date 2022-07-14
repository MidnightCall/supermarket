#include "accountManage.h"
#include "helpfulFunction.h"
#include "customLookup.h"
#include "linkList.h"

extern Node_t* userDat;

/* �ֲ�����ģ�� */
static int getChoice();

void runAccountManage()
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
	}
}

void queryUser(void)
{
	User_t tUser;
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("================��ѯ�˻�==================\n");
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
		index = findIndexByID_d(userDat, tId, &tUser, sizeof(User_t));
		if (0 == index)
		{
			printf("û�з���������Ա����\b");
			system("pause");
			return;
		}
		showSingleUser(tUser);
		break;
	}
}

void modifyUserPermission(void)
{
	User_t tUser;
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("================�޸�Ȩ��==================\n");
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
			printf("���޷��޸ĳ�������Ա [10000] ��Ȩ��.\b\n");
			return;
		}

		index = findIndexByID_d(userDat, tId, &tUser, sizeof(User_t));
		if (0 == index)
		{
			printf("û�з���������Ա����\b");
			system("pause");
			return;
		}
		showSingleUser(tUser);
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
	showSingleUser(tUser);
	printf("Ȩ���޸ĳɹ���\n");
	return;

}

void deleteUser(void)
{
	User_t tUser;

	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("================ɾ���˻�==================\n");
	unsigned int index = 0;
	while (true)
	{
		printf("�������˻� ID: ");
		unsigned int tId = 0;
		scanf("%u", &tId);
		if (tId < 10000 || tId > 99999)
		{
			printf("������� ID ��Ч�����������롣\b\n");
			continue;
		}

		if (tId == 10000)
		{
			printf("���޷�ɾ����������Ա [10000].\b\n");
			return;
		}

		index = findIndexByID_d(userDat, tId, &tUser, sizeof(User_t));
		if (0 == index)
		{
			printf("û�з����������˻����� Enter ��������\b");
			return;
		}
		showSingleUser(tUser);
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
	return;
}

/* �ֲ�����ʵ�� */
static int getChoice()
{
	int choice;

	do
	{
		showAccountBusinessMenu();
		scanf("%d", &choice);
	} while (choice > 4 || choice < 1);

	return choice;
}

void showSingleUser(User_t e)
{
	printf("================�˺���Ϣ==================\n");
	printf("%5s| %12s| %20s|\n", "ID", "����", "Ȩ�޵ȼ�");
	printf("-----+-------------+---------------------+\n");
	printUserInfo(&e);
	printf("==========================================\n");
}

void showAllUsers(void)
{
	printf("================�˺���Ϣ==================\n");
	printf("%5s| %12s| %20s|\n", "ID", "����", "Ȩ�޵ȼ�");
	printf("-----+-------------+---------------------+\n");
	printList(userDat, printUserInfo, false);
	printf("==========================================\n");
	return;
}