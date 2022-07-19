/*****************************************************************//**
 * \file   employee.c
 * \brief  �Գ�������Ա (SU Ȩ��) ��ְ��������ʵ��
 *
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "files.h"
#include "linkList.h"
#include "helpfulFunction.h"
#include "employee.h"
#include "UI.h"

extern Node_t* employeeDat;
extern Config_t configDat;
extern User_t currentUser;

/* �ֲ�����ģ�� */
static int getChoice();
static void showSingleEmployee(Employee_t e);
static void showAllEmployees(void);


/**
* \brief ����ְ������ģ��
*/
void runEmployeeManage(void)
{
	while (1)
	{
		int choice = getChoice();

		switch (choice)
		{
		default:
			return;
		case 1:
			showAllEmployees();
			PAUSE;
			break;
		case 2:
			findEmployee();
			break;
		case 3:
			addEmployee();
			break;
		case 4:
			deleteEmployee();
			break;
		case 5:
			modifyEmployee();
			break;
		}
	}
}

/**
* \brief �����Ա��
*/
void addEmployee(void)
{
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));
	Employee_t* e = (Employee_t*)malloc(sizeof(Employee_t));
	assert(e != NULL);

	e->id = ++configDat.maxId_Employee; /* �Զ����� ID */ /* checked */
	printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T���Ա���T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
	while (true)
	{
		printf("������Ա������: ");
		stringGet(buffer, 250);
		if (strlen(buffer) > LEN_EMPLOYEE_NAME - 1 || strlen(buffer) < 4) /* ��һλҪ������� '\0' �ģ�����Ҫ�� 1 */
		{
			printf("<!> �������������Ч�����������롣\a\n");
			continue;
		}
		memset(e->name, '\0', sizeof(e->name));
		strncpy(e->name, buffer, strlen(buffer));
		break;
	}
	
	while (true)
	{
		unsigned int tAge = 0;
		tAge = getNonNegativeNumber("������Ա������: ");
		if (tAge < 16 || tAge > 70)
		{
			printf("<!> �������������Ч�����������롣\a\n");
			continue;
		}
		e->age = tAge;
		break;
	}

	while (true)
	{
		unsigned int tSex = 0;
		tSex = getNonNegativeNumber("������Ա���Ա�(0 ΪŮ��1 Ϊ��): ");
		if (tSex != 0 && tSex != 1)
		{
			printf("<!> ��������Ա���Ч�����������롣\n");
			continue;
		}
		e->sex = tSex;
		break;
	}

	while (true)
	{
		printf("������Ա��ְλ: ");
		stringGet(buffer, 250);
		if (strlen(buffer) > LEN_EMPLOYEE_POS - 1 || 0 == strlen(buffer))
		{
			printf("<!> �������ְλ��Ч�����������롣\a\n");
			continue;
		}
		memset(e->position, '\0', sizeof(e->position));
		strncpy(e->position, buffer, strlen(buffer));
		break;
	}

	insert(employeeDat, END, e);

	printf("Ա�����ӳɹ���\n");
	PAUSE;
	return;
}

/**
* \brief ɾ��Ա��
*/
void deleteEmployee(void)
{
	Employee_t* tEmployee = NULL;
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�Tɾ��Ա���T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
	unsigned int op = 0;
	while (true)
	{
		op = getNonNegativeNumber("�����������[0: ID, 1: ����]: ");
		if (op != 0 && op != 1)
		{
			printf("<!> ������Ĳ�����Ч�����������롣\a\n");
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
			unsigned int tId = 0;
			tId = getNonNegativeNumber("������Ա�� ID: ");
			if (tId < 1000 || tId > 9999)
			{
				printf("<!> ������� ID ��Ч�����������롣\a\n");
				continue;
			}
			index = findIndexByID_d(employeeDat, tId, &tEmployee);
			if (0 == index)
			{
				printf("<!> û�з���������Ա����\a");
				PAUSE;
				return;
			}
			showSingleEmployee(*tEmployee);
			break;
		}
		break;
	case 1:
		while (true)
		{
			printf("������Ա������: ");
			stringGet(buffer, 250);
			if (strlen(buffer) > LEN_EMPLOYEE_NAME - 1 || 0 == strlen(buffer))
			{
				printf("<!> �������������Ч�����������롣\a\n");
				continue;
			}
			index = findIndexByName_d(employeeDat, buffer, OFFSET_EMPLOYEE, &tEmployee);
			if (0 == index)
			{
				printf("<!> û�з���������Ա����\a");
				PAUSE;
				return;
			}
			showSingleEmployee(*tEmployee);
			break;
		}
		break;
	default:
		break;
	}

	while (true)
	{
		printf("ȷ��Ҫɾ����[y/n]: ");
		char deleteOp = '\0';
		scanf("%c", &deleteOp);
		if (deleteOp != 'y' && deleteOp != 'n' && deleteOp != 'Y' && deleteOp != 'N')
		{
			printf("<!> ������Ĳ�����Ч�����������롣\a\n");
			continue;
		}
		if (deleteOp == 'y' || deleteOp == 'Y')
		{
			del(employeeDat, index);
			printf("Ա��ɾ���ɹ���");
			break;
		}
		if (deleteOp == 'n' || deleteOp == 'N')
			return;
	}

	PAUSE;
	return;
}

/**
* \brief ����Ա��
*/
void findEmployee(void)
{
	Employee_t* tEmployee = NULL;
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T����Ա���T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
	unsigned int op = 0;
	while (true)
	{
		op = getNonNegativeNumber("ѡ��������� [0: ID, 1: ����]: ");
		if (op != 0 && op != 1)
		{
			printf("<!> ������Ĳ�����Ч�����������롣\a\n");
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
			unsigned int tId = 0;
			tId = getNonNegativeNumber("������Ա�� ID: ");
			if (tId < 1000 || tId > 9999)
			{
				printf("<!> ������� ID ��Ч�����������롣\a\n");
				continue;
			}
			index = findIndexByID_d(employeeDat, tId, &tEmployee);
			if (0 == index)
			{
				printf("<!> û�з���������Ա����\a");
				PAUSE;
				return;
			}
			showSingleEmployee(*tEmployee);
			break;
		}
		break;
	case 1:
		while (true)
		{
			printf("������Ա������: ");
			stringGet(buffer, 250);
			if (strlen(buffer) > LEN_EMPLOYEE_NAME - 1 || 0 == strlen(buffer))
			{
				printf("<!> �������������Ч�����������롣\a\n");
				continue;
			}

			index = findIndexByName_d(employeeDat, buffer, OFFSET_EMPLOYEE, &tEmployee);
			if (0 == index)
			{
				printf("<!> û�з���������Ա����\a");
				PAUSE;
				return;
			}
			showSingleEmployee(*tEmployee);
			break;
		}
		break;
	default:
		break;
	}

	PAUSE;
	return;
}

/**
* \brief �޸�Ա����Ϣ
*/
void modifyEmployee(void)
{
	Employee_t* tEmployee = NULL;
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�޸�Ա����Ϣ�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
	unsigned int op = 0, index = 0;
	while (true)
	{
		unsigned int tId = 0;
		tId = getNonNegativeNumber("������Ա�� ID: ");
		if (tId < 1000 || tId > 9999)
		{
			printf("<!> ������� ID ��Ч��\a");
			PAUSE;
			return;
		}
		index = findIndexByID_d(employeeDat, tId, &tEmployee);
		if (0 == index)
		{
			printf("<!> û�з���������Ա����\a");
			PAUSE;
			return;
		}
		showSingleEmployee(*tEmployee);
		break;
	}

	printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T��������Ϣ�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
	while (true)
	{
		printf("������Ա������: ");
		stringGet(buffer, 250);
		if (strlen(buffer) > LEN_EMPLOYEE_NAME - 1 || 0 == strlen(buffer))
		{
			printf("<!> �������������Ч�����������롣\a\n");
			continue;
		}
		memset(tEmployee->name, '\0', sizeof(tEmployee->name));
		strncpy(tEmployee->name, buffer, strlen(buffer));
		break;
	}

	while (true)
	{
		unsigned int tAge = 0;
		tAge = getNonNegativeNumber("������Ա������: ");
		if (tAge < 16 || tAge > 70)
		{
			printf("<!> �������������Ч�����������롣\a\n");
			continue;
		}
		tEmployee->age = tAge;
		break;
	}

	while (true)
	{
		unsigned int tSex = 0;
		tSex = getNonNegativeNumber("������Ա���Ա� (0 ΪŮ��1 Ϊ��): ");
		if (tSex != 0 && tSex != 1)
		{
			printf("<!> ��������Ա���Ч�����������롣\a\n");
			continue;
		}
		tEmployee->sex = tSex;
		break;
	}

	while (true)
	{
		printf("������Ա��ְλ: ");
		stringGet(buffer, 250);

		if (strlen(buffer) > LEN_EMPLOYEE_POS - 1 || 0 == strlen(buffer))
		{
			printf("<!> �������ְλ��Ч�����������롣\a\n");
			continue;
		}
		memset(tEmployee->position, '\0', sizeof(tEmployee->position));
		strncpy(tEmployee->position, buffer, strlen(buffer));
		break;
	}
	printf("Ա����Ϣ�޸ĳɹ���");

	PAUSE;
	return;
}

/**
* \brief ��ʾ����Ա����Ϣ
*/
static void showSingleEmployee(Employee_t e)
{
	printf("���������������Щ������������������Щ���Ա����Ϣ���������Щ���������������������������������\n");
	printf("�� %5s�� %8s�� %6s�� %5s�� %15s��\n", "ID", "����", "�Ա�", "����", "ְλ");
	printf("���������������੤�����������������੤�������������੤�����������੤��������������������������������\n");
	printEmployeeInfo(&e);
	printf("���������������ة������������������ة��������������ة������������ة���������������������������������\n");
}

/**
* \brief ��ʾ����Ա����Ϣ
*/
static void showAllEmployees(void)
{
	if (0 == *(int*)employeeDat->data)
	{
		printf("<!> û��Ա����Ϣ��\a");
		return;
	}

	printf("���������������Щ������������������Щ���Ա����Ϣ���������Щ���������������������������������\n");
	printf("�� %5s�� %8s�� %6s�� %5s�� %15s��\n", "ID", "����", "�Ա�", "����", "ְλ");
	printf("���������������੤�����������������੤�������������੤�����������੤��������������������������������\n");
	printList(employeeDat, printEmployeeInfo, false);
	printf("���������������ة������������������ة��������������ة������������ة���������������������������������\n");
	return;
}

static int getChoice()
{
	int choice = 0;
	do
	{
		showTitle(currentUser);
		showEmployeeBusinessMenu();
		choice = getMenuChoice();

	} while (choice > 6 || choice < 1);

	return choice;
}