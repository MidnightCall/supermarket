#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "files.h"
#include "linkList.h"
#include "helpfulFunction.h"
#include "employee.h"

extern Node_t* employeeDat;
extern Config_t configDat;

void showSingleEmployee(Employee_t e)
{
	printf("================Ա����Ϣ==================\n");
	printf("%5s| %8s| %4s| %5s| %11s|\n", "ID", "����", "�Ա�", "����", "ְλ");
	printf("-----+---------+-----+------+------------+\n");
	printEmployeeInfo(&e);
	printf("==========================================\n");
}

void showAllEmployees(void)
{
	if (0 == *(int*)employeeDat->data)
	{
		printf("û��Ա����Ϣ��\b\n");
		return;
	}
	printf("================Ա����Ϣ==================\n");
	printf("%5s| %8s| %4s| %5s| %11s|\n", "ID", "����", "�Ա�", "����", "ְλ");
	printf("-----+---------+-----+------+------------+\n");
	printList(employeeDat, printEmployeeInfo, false);
	printf("==========================================\n");
	return;
}

void addEmployee(void)
{
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));
	Employee_t* e = (Employee_t*)malloc(sizeof(Employee_t));
	if (NULL == e)
	{
		printf("��ʼ���ڵ�ʧ�ܡ�\b\n");
		exit(0);
	}

	e->id = ++configDat.maxId_Employee; /* �Զ����� ID */
	printf("================���Ա��==================\n");
	while (true)
	{
		printf("������Ա������: ");
		scanf("%[^\n]", &buffer);
		if (strlen(buffer) > LEN_NAME - 1) /* ��һλҪ������� '\0' �ģ�����Ҫ�� 1 */
		{
			printf("��������������������������롣\b\n");
			flush();
			continue;
		}
		memset(e->name, '\0', sizeof(e->name));
		strncpy(e->name, buffer, strlen(buffer));
		break;
	}
	
	while (true)
	{
		printf("������Ա������: ");
		unsigned int tAge = 0;
		scanf("%u", &tAge);
		if (tAge < 0 || tAge > 70)
		{
			printf("�������������Ч�����������롣\b\n");
			continue;
		}
		e->age = tAge;
		break;
	}

	while (true)
	{
		printf("������Ա���Ա� (0 ΪŮ��1 Ϊ��): ");
		unsigned int tSex = 0;
		scanf("%u", &tSex);
		if (tSex != 0 && tSex != 1)
		{
			printf("��������Ա���Ч�����������롣\b\n");
			continue;
		}
		e->sex = tSex;
		break;
	}

	while (true)
	{
		printf("������Ա��ְλ: ");
		getchar(); /* �����ո� */
		scanf_s("%[^\n]", &buffer, LEN_POS);
		if (strlen(buffer) > LEN_POS - 1)
		{
			printf("�������ְλ���������������롣\b\n");
			continue;
		}
		memset(e->position, '\0', sizeof(e->position));
		strncpy(e->position, buffer, strlen(buffer));
		break;
	}

	insert(employeeDat, END, e);

	printf("Ա�����ӳɹ���\n");
	return;
}

void deleteEmployee(void)
{
	Employee_t tEmployee;
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("================ɾ��Ա��==================\n");
	unsigned int op = 0;
	while (true)
	{
		printf("ѡ��������� [0: ID, 1: ����]: ");
		scanf("%u", &op);
		if (op != 0 && op != 1)
		{
			printf("������Ĳ�����Ч�����������롣\b\n");
			flush();
			continue;
		}
		break;
	}

	unsigned int index = 0;
	switch (op)
	{
	case 0:
		while (true)
		{
			printf("������Ա�� ID: ");
			unsigned int tId = 0;
			scanf("%u", &tId);
			if (tId < 1000 || tId > 9999)
			{
				printf("������� ID ��Ч�����������롣\b\n");
				continue;
			}
			index = findIndexByID_d(employeeDat, tId, &tEmployee, sizeof(Employee_t));
			if (0 == index)
			{
				printf("û�з���������Ա������ Enter ��������\b");
				return;
			}
			showSingleEmployee(tEmployee);
			break;
		}
		break;
	case 1:
		while (true)
		{
			getchar();
			printf("������Ա������: ");
			scanf("%[^\n]", &buffer);
			if (strlen(buffer) > LEN_NAME - 1)
			{
				printf("�������������Ч�����������롣\b\n");
				continue;
			}
			index = findIndexByName_d(employeeDat, buffer, OFFSET_EMPLOYEE, &tEmployee, sizeof(Employee_t));
			if (0 == index)
			{
				printf("û�з���������Ա������ Enter ��������\b");
				return;
			}
			showSingleEmployee(tEmployee);
			break;
		}
		break;
	default:
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
			del(employeeDat, index);
			printf("Ա��ɾ���ɹ���\n");
			showAllEmployees(employeeDat);
			break;
		}
		if (deleteOp == 'n' || deleteOp == 'N')
			return;
	}
	return;
}

void findEmployee(void)
{
	Employee_t tEmployee;
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("================����Ա��==================\n");
	unsigned int op = 0;
	while (true)
	{
		printf("ѡ��������� [0: ID, 1: ����]: ");
		scanf("%u", &op);
		if (op != 0 && op != 1)
		{
			printf("������Ĳ�����Ч�����������롣\b\n");
			flush();
			continue;
		}
		break;
	}

	unsigned int index = 0;
	switch (op)
	{
	case 0:
		while (true)
		{
			printf("������Ա�� ID: ");
			unsigned int tId = 0;
			scanf("%u", &tId);
			if (tId < 1000 || tId > 9999)
			{
				printf("������� ID ��Ч�����������롣\b\n");
				continue;
			}
			index = findIndexByID_d(employeeDat, tId, &tEmployee, sizeof(Employee_t));
			if (0 == index)
			{
				printf("û�з���������Ա����\b");
				system("pause");
				return;
			}
			showSingleEmployee(tEmployee);
			break;
		}
		break;
	case 1:
		while (true)
		{
			getchar();
			printf("������Ա������: ");
			scanf("%[^\n]", &buffer);
			if (strlen(buffer) > LEN_NAME - 1)
			{
				printf("�������������Ч�����������롣\b\n");
				continue;
			}
			index = findIndexByName_d(employeeDat, buffer, OFFSET_EMPLOYEE, &tEmployee, sizeof(Employee_t));
			if (0 == index)
			{
				printf("û�з���������Ա������ Enter ��������\b");
				return;
			}
			showSingleEmployee(tEmployee);
			break;
		}
		break;
	default:
		break;
	}

	system("pause");
	return;
}

