/*****************************************************************//**
 * \file   account.c
 * \brief  ���û���¼��ע�Ṧ�ܵ�ʵ��
 * 
 * \author praist
 * \date   July 2022
 *********************************************************************/

#include "account.h"
#include "helpfulFunction.h"
#include "SupermarketManageSystem.h"
#include <stdbool.h>

static int getChoice(void);

extern Node_t* userDat;
extern User_t currentUser;
extern Config_t configDat;

/**
 * \brief �����¼��ע���ѡ��˵�
 */
void runLogIn(void)
{
	if (0 == *(int*)userDat->data) /* ����ļ���һ���˻���û�У����Զ�����һ������ (SU) */
	{
		User_t Su = { 10000, "admin", SU }; /* ����Ĭ������ */
		User_t* newSu = (User_t*)malloc(sizeof(User_t));
		assert(newSu != NULL);

		memcpy(newSu, &Su, sizeof(User_t));
		insert(userDat, END, newSu);
	}

	int choice = getChoice();

	switch (choice)
	{
	default:
		system("cls");
		showExitMessage();
		PAUSE;
		saveData();
		exit(0);
		return;
	case 1:
		logIn();
		return;
	case 2:
		registration();
		currentUser.permission = -1; /* �ص���ʼ���� */
		return;
	}
}

/*
* \brief��ע���˺�
*/
void registration(void)
{
	int choice = 0;
	char firstPassword[LEN_PWD];
	char secondPassword[LEN_PWD];
	User_t* account = (User_t*)malloc(sizeof(User_t));
	assert(account != NULL);

	printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�û�ע��T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
	/* �˺���ʾ */
	printf("����˺��� %d.\n", ++configDat.maxId_User); /* ��ע���겻�ó�ȥ���������ֱ������ */
	account->id = configDat.maxId_User;
	/* ȷ������ */
	while (1)
	{
		printf("�������������: ");
		stringGet(firstPassword, LEN_PWD);
		if (strlen(firstPassword) < 6) {
			printf("<!> ���볤������Ϊ��λ�����������롣\a\n");
			continue;
		}

		printf("��ȷ���������: ");
		stringGet(secondPassword, LEN_PWD);
		if (strcmp(firstPassword, secondPassword) == 0) {
			strcpy(account->password, firstPassword);
			account->permission = COMMON; /* Ĭ��Ϊ��ͨ�û� */
			insert(userDat, END, account);
			break;
		} else {
			printf("<!> �����������벻һ�£����������롣\a\n");
		}
	}
	printf("ע��ɹ��������µ�¼��\n");
	PAUSE;
	return;
}

/**
 * \brief ��¼�˺�
 */
void logIn(void)
{
	int id;
	char rawId[10]; /* ID ԭʼ�ַ��� */
	char password[LEN_PWD];

	printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�û���¼�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
	while (true)
	{
		printf("�������˺�: ");
		stringGet(rawId, 10);
		if (strlen(rawId) > 5)
		{
			printf("<!> ������� ID ���������������롣\a\n");
			continue;
		}

		if (hasNonNumerical(rawId, false))
		{
			printf("<!> ������� ID ��ʽ�������������롣\a\n");
			continue;
		}

		id = atoi(rawId);

		User_t* account = NULL;
		if (findIndexByID_d(userDat, id, &account) != 0) {
			printf("���ã�ID %d ���û�\n", id);
			printf("����������: ");
			stringGet(password, LEN_PWD);
			if (strcmp(password, account->password) == 0) {
				printf("��¼�ɹ���");
				memcpy(&currentUser, account, sizeof(User_t));
				PAUSE;
				break;
			} else {
				printf("<!> ������������������˺ź����롣\a\n");
				continue;
			}
		} else {
			printf("<!> �˺Ų����ڣ���ȷ�Ϻ��������롣\a\n");
			continue;
		}
	}
}

static int getChoice(void)
{
	int choice = 0;
	do
	{
		showWelcomeMessage();
		showLoginMessage();
		choice = getMenuChoice();
	} while (choice > 3 || choice < 1);

	return choice;
}