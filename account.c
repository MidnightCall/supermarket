#include "account.h"
#include "helpfulFunction.h"

/* �ֲ�����ģ�� */
static char* stringGet(char* st, int n);

/*
* @brief�����е�¼/ע��ϵͳ
*/
void runLogIn()
{
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
	int choice;
	User_t* account = (User_t*) malloc(sizeof(User_t));
	static int currentAccount = 10000;
	char firstPassword[LEN_PWD];
	char secondPassword[LEN_PWD];

	/* �˺���ʾ */
	printf("����˺��� %d\n", currentAccount);
	account->id = currentAccount++;

	/* �˺�Ȩ�޷��� */
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

	/* ȷ������ */
	while (1)
	{
		printf("�������������:");
		stringGet(firstPassword, LEN_PWD);
		if (strlen(firstPassword) < 6) {
			printf("����������λ,����������\n");
			continue;
		}
		printf("��ȷ���������:");
		stringGet(secondPassword, LEN_PWD);
		if (strcmp(firstPassword, secondPassword) == 0) {
			strcpy(account->password, firstPassword);
			insert(userDat, END, account);
			break;
		}else{
			printf("�������벻һ�£�����������\n");
		}
	}
	printf("ע��ɹ�,�����µ�¼\n");
}

/*
*  @brief: ��¼�˺�
*/
void logIn()
{
	int id;
	char password[LEN_PWD];

	while (true)
	{
		printf("�������˺�:");
		scanf("%d", &id);
		User_t account;
		if (findIndexByID_d(userDat, id, &account, sizeof(User_t)) != 0) {
			printf("���,id%d���û�\n", id);
			flush();
			printf("����������:");
			stringGet(password, LEN_PWD);
			if (strcmp(password, account.password) == 0) {
				printf("��½�ɹ�\n");
				currentUser.id = account.id;
				currentUser.permission = account.permission;
				strcpy(currentUser.password, account.password);
				break;
			}else{
				printf("�������,�����������˺ź�����\n");
				continue;
			}
		}
		else {
			printf("�˺Ų�����,������ȷ�Ϻ�����\n");
			continue;
		}
	}
	
}

/* �ֲ��������� */
static char* stringGet(char* st, int n)
{
	char* ret_val;
	char* find;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');
		if (find) {
			*find = '\0';
		}
		else {
			while (getchar() != '\n')
				continue;
		}
	}

	return ret_val;
}