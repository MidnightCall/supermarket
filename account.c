#include "account.h"


/* �ֲ�����ģ�� */
static char* stringGet(char *st, int n);

/*
* ���������е�¼/ע��ϵͳ
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
* ��������ʾ�����˵�����ȡ�û���ѡ��Ĳ���
* ������������ʾ�����˵�
*/
int getChoice()
{
	int choice;

	do
	{
		showLoginMessage();
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);

	return choice;
}

/*
* ������ע���˺� 12131213132311321132213
*/
void registration()
{
	User_t account;
	static int currentAccount = 10000;
	char * firstPassword[LEN_PWD];
	char * secondPassword[LEN_PWD];

	printf("����˺��� %d\n", currentAccount);
	account.id = currentAccount++;
	while (1)
	{
		while (getchar() != '\n')
			continue;
		printf("�������������:");
		stringGet(firstPassword, LEN_PWD);
		printf("��ȷ���������:");
		stringGet(secondPassword, LEN_PWD);
		if (strcmp(firstPassword, secondPassword) == 0) {
			strcpy(account.password, firstPassword);
			break;
		}
		else
		{
			printf("�������벻һ�£�����������\n");
		}
	}
	printf("ע��ɹ�,�����µ�¼\n");
}

/*
*  ����: ��¼�˺�
*/
void logIn()
{

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
		if (find){
			*find = '\0';
		}
		else {
			while (getchar() != '\n')
				continue;
		}
	}

	return ret_val;
}