#include "account.h"
#include "helpfulFunction.h"
#include <stdbool.h>

/* �ֲ�����ģ�� */
//static char* stringGet(char* st, int n);

extern Node_t* userDat;

/*
* @brief�����е�¼/ע��ϵͳ
*/
void runLogIn()
{
	if (0 == *(int*)userDat->data) /* ����ļ���һ���˻���û�У����Զ�����һ������ (SU) */ /* passed */
	{
		User_t Su = { 10000, "nE0ntLUlE", SU }; /* ����Ĭ������ */
		User_t* newSu = (User_t*)malloc(sizeof(User_t));

		if (NULL == newSu)
		{
			printf("��������Ա�˻���ʼ��ʧ�ܡ�\b\n");
			exit(0);
		}
		memcpy(newSu, &Su, sizeof(User_t));
		insert(userDat, END, newSu);
	}

	int choice = getChoice();
	switch (choice)
	{
		default:
			break;
		case 1:
			logIn();
			break;
		case 2:
			registration();
			break;
		case 3:
			system("cls");
			showExitMessage();
			break;
	}
}

/*
* @brief����ʾ�����˵�����ȡ�û���ѡ��Ĳ���
* 
*/
int getChoice()
{
	int choice;

	do
	{
		showLoginMessage();
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);
	flush();

	return choice;
}

/*
* @brief��ע���˺�
*/
void registration()
{
	printList(userDat, printUserInfo, false);
	int choice;
	User_t* account = (User_t*) malloc(sizeof(User_t));
	static int currentAccount = 10000;
	char firstPassword[LEN_PWD];
	char secondPassword[LEN_PWD];

	/* �˺���ʾ */
	printf("����˺��� %d\n", currentAccount);
	account->id = currentAccount++;

	/* �˺�Ȩ�޷���
	do
	{
		printf("��ѡ����Ҫע���Ȩ������:\n");
		printf("1.��ͨ�û�\n2.����Ա\n3.��������Ա\n");
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);
	
	flush();
	switch (choice)
	{
		default:
			break;
		case 1:
			account->permission = COMMON;
			break;
		case 2:
			account->permission = ADMIN;
			break;
		case 3:
			account->permission = SU;
			break;
	}
	*/

	/* ȷ������ */
	while (1)
	{
		printf("�������������: ");
		stringGet(firstPassword, LEN_PWD);
		if (strlen(firstPassword) < 6) {
			printf("����������λ������������\n");
			continue;
		}
		printf("��ȷ���������:");
		stringGet(secondPassword, LEN_PWD);
		if (strcmp(firstPassword, secondPassword) == 0) {
			strcpy(account->password, firstPassword);
			account->permission = COMMON; /* Ĭ��Ϊ��ͨ�û� */
			insert(userDat, END, account);
			break;
		}else{
			printf("�������벻һ�£�����������\n");
		}
	}
	printf("ע��ɹ��������µ�¼��\n");
}

/*
*  @brief: ��¼�˺�
*/
void logIn()
{
	int id;
	char rawId[10]; /* ID ԭʼ�ַ��� */
	char password[LEN_PWD];

	while (true)
	{
		printf("�������˺�: ");
		stringGet(rawId, 10);
		if (strlen(rawId) > 5)
		{
			printf("������� ID ���������������롣\n");
			continue;
		}

		if (hasNonNumerical(rawId))
		{
			printf("������� ID ��ʽ�������������롣\n");
			continue;
		}

		id = atoi(rawId);

		User_t account;
		if (findIndexByID_d(userDat, id, &account, sizeof(User_t)) != 0) {
			printf("��ã�ID %d ���û�\n", id);
			flush();
			printf("����������:");
			stringGet(password, LEN_PWD);
			if (strcmp(password, account.password) == 0) {
				printf("��½�ɹ�\n");
				currentUser.id = account.id;
				currentUser.permission = account.permission;
				strcpy(currentUser.password, account.password);
				break;
			} else {
				printf("�������,�����������˺ź�����\n");
				flush();
				continue;
			}
		}
		else {
			printf("�˺Ų����ڣ�������ȷ�Ϻ�����\n");
			continue;
		}
	}
	
}