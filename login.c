#include <stdio.h>
#include <stdlib.h>
#include "login.h"

/* �ֲ�����ģ�� */
static void showMenu();
static void showChar(char ch, int n);

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
	showMenu();
	return 0;
}

/* �ֲ��������� */
static void showMenu()
{
	showChar('-', 45);
	printf("��ӭ�������й���ϵͳ����ѡ����Ҫ���еĲ���:\n");
	printf("1.��¼\n");
	printf("2.ע��\n");
	printf("3.�˳�\n");
	showChar('-', 45);
}

static void showChar(char ch, int n)
{
	for (int i = 0; i < n; i++)
		printf(ch);
}