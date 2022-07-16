#include "account.h"
#include "helpfulFunction.h"
#include <stdbool.h>

extern Node_t* userDat;
extern User_t currentUser;
extern Config_t configDat;
/*
* @brief�����е�¼/ע��ϵͳ
*/
void runLogIn(void)
{
	if (0 == *(int*)userDat->data) /* ����ļ���һ���˻���û�У����Զ�����һ������ (SU) */ /* passed */
	{
		User_t Su = { 10000, "admin", SU }; /* ����Ĭ������ */
		User_t* newSu = (User_t*)malloc(sizeof(User_t));
		//assert_null(newSu);

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
* @brief����ʾ�����˵�����ȡ�û���ѡ��Ĳ���
*
*/
int getChoice(void)
{
	int choice = 0;
	do
	{
		showLoginMessage();
		HINT;
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);
	flush();

	return choice;
}

/*
* @brief��ע���˺�
*/
void registration(void)
{
	int choice = 0;
	char firstPassword[LEN_PWD];
	char secondPassword[LEN_PWD];
	User_t* account = (User_t*)malloc(sizeof(User_t));
	//assert_null(account);

	/* �˺���ʾ */
	printf("����˺��� %d\n", ++configDat.maxId_User);
	account->id = configDat.maxId_User;
	/* ȷ������ */
	while (1)
	{
		printf("�������������: ");
		stringGet(firstPassword, LEN_PWD);
		if (strlen(firstPassword) < 6) {
			printf("����������λ�����������롣\n");
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
			printf("�������벻һ�£����������롣\n");
		}
	}
	printf("ע��ɹ��������µ�¼��\n");
	PAUSE;
	return;
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

		User_t* account = NULL;
		if (findIndexByID_d(userDat, id, &account) != 0) {
			printf("���ã�ID %d ���û�\n", id);
			printf("����������: ");
			stringGet(password, LEN_PWD);
			if (strcmp(password, account->password) == 0) {
				printf("��½�ɹ���");
				currentUser.id = account->id;
				currentUser.permission = account->permission;
				strcpy(currentUser.password, account->password);
				system("pause");
				break;
			} else {
				printf("������������������˺ź����롣\n");
				flush();
				continue;
			}
		} else {
			printf("�˺Ų����ڣ�������ȷ�Ϻ����롣\n");
			continue;
		}
	}

}