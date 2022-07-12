#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"

/* �ֲ�����ģ�� */
static void showMenu();
static void showChar(char ch, int n);
static char* stringGet(char *st,int n);

/*
* ���������е�¼/ע��ϵͳ
*/
void runLogIn()
{
	int choice = getChoice();
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
		showMenu();
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);

	return choice;
}

/*
* ������ע���˺�
*/
void registration()
{
	UI account;
	static int currentAccount = 10000;
	int firstPassword;
	int secondPassword;

	printf("����˺���%d\n", currentAccount);
	account.id = currentAccount++;
	do {
		printf("�������������:");
		stringGet(firstPassword, PSIZE);
		printf("��ȷ���������:");
		stringGet(secondPassword, PSIZE);
		if (firstPassword == secondPassword) {
			strcpy(account.password, firstPassword);
			break;
		}
	} while (1);
	printf("ע��ɹ�!\n");
	fwrite()
}

/* �ֲ��������� */
static void showMenu()
{
	showChar('-', 45);
	putchar('\n');
	printf("��ӭ�������й���ϵͳ����ѡ����Ҫ���еĲ���:\n");
	printf("1.��¼\n");
	printf("2.ע��\n");
	printf("3.�˳�\n");
	showChar('-', 45);
	putchar('\n');
}

static void showChar(char ch, int n)
{
	for (int i = 0; i < n; i++)
		putchar(ch);
}

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
			FLUSH;
		}
	}

	return ret_val;
}