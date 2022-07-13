#include "account.h"


/* �ֲ�����ģ�� */
static char* stringGet(char *st, int n);

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
		case 2:
			registration();
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
	User_t account;
	static int currentAccount = 10000;
	char * firstPassword[LEN_PWD];
	char * secondPassword[LEN_PWD];

	/* �˺���ʾ */
	printf("����˺��� %d\n", currentAccount);
	account.id = currentAccount++;

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
			account.permission = USER;
			break;
		case 2:
			account.permission = ADMIN;
			break;
		case 3:
			account.permission = SU;
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
			strcpy(account.password, firstPassword);
			insert(userDat, END, FILE_USER);
			writeFile(FILE_USER, userDat, sizeof(User_t));
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
	char* password[LEN_PWD];

	do {
		printf("�������˺�:");
		scanf("%d", &id);
	} while (1);


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
