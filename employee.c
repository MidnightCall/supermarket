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
	printf("================员工信息==================\n");
	printf("%5s| %8s| %4s| %5s| %11s|\n", "ID", "姓名", "性别", "年龄", "职位");
	printf("-----+---------+-----+------+------------+\n");
	printEmployeeInfo(&e);
	printf("==========================================\n");
}

void showAllEmployees(void)
{
	if (0 == *(int*)employeeDat->data)
	{
		printf("没有员工信息。\b\n");
		return;
	}
	printf("================员工信息==================\n");
	printf("%5s| %8s| %4s| %5s| %11s|\n", "ID", "姓名", "性别", "年龄", "职位");
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
		printf("初始化节点失败。\b\n");
		exit(0);
	}

	e->id = ++configDat.maxId_Employee; /* 自动赋予 ID */
	printf("================添加员工==================\n");
	while (true)
	{
		printf("请输入员工姓名: ");
		scanf("%[^\n]", &buffer);
		if (strlen(buffer) > LEN_NAME - 1) /* 有一位要用来存放 '\0' 的，这里要减 1 */
		{
			printf("你输入的姓名过长，请重新输入。\b\n");
			flush();
			continue;
		}
		memset(e->name, '\0', sizeof(e->name));
		strncpy(e->name, buffer, strlen(buffer));
		break;
	}
	
	while (true)
	{
		printf("请输入员工年龄: ");
		unsigned int tAge = 0;
		scanf("%u", &tAge);
		if (tAge < 0 || tAge > 70)
		{
			printf("你输入的年龄无效，请重新输入。\b\n");
			continue;
		}
		e->age = tAge;
		break;
	}

	while (true)
	{
		printf("请输入员工性别 (0 为女，1 为男): ");
		unsigned int tSex = 0;
		scanf("%u", &tSex);
		if (tSex != 0 && tSex != 1)
		{
			printf("你输入的性别无效，请重新输入。\b\n");
			continue;
		}
		e->sex = tSex;
		break;
	}

	while (true)
	{
		printf("请输入员工职位: ");
		getchar(); /* 读掉空格 */
		scanf_s("%[^\n]", &buffer, LEN_POS);
		if (strlen(buffer) > LEN_POS - 1)
		{
			printf("你输入的职位过长，请重新输入。\b\n");
			continue;
		}
		memset(e->position, '\0', sizeof(e->position));
		strncpy(e->position, buffer, strlen(buffer));
		break;
	}

	insert(employeeDat, END, e);

	printf("员工增加成功！\n");
	return;
}

void deleteEmployee(void)
{
	Employee_t tEmployee;
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("================删除员工==================\n");
	unsigned int op = 0;
	while (true)
	{
		printf("选择查找条件 [0: ID, 1: 姓名]: ");
		scanf("%u", &op);
		if (op != 0 && op != 1)
		{
			printf("你输入的操作无效，请重新输入。\b\n");
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
			printf("请输入员工 ID: ");
			unsigned int tId = 0;
			scanf("%u", &tId);
			if (tId < 1000 || tId > 9999)
			{
				printf("你输入的 ID 无效，请重新输入。\b\n");
				continue;
			}
			index = findIndexByID_d(employeeDat, tId, &tEmployee, sizeof(Employee_t));
			if (0 == index)
			{
				printf("没有符合条件的员工。按 Enter 键继续。\b");
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
			printf("请输入员工姓名: ");
			scanf("%[^\n]", &buffer);
			if (strlen(buffer) > LEN_NAME - 1)
			{
				printf("你输入的姓名无效，请重新输入。\b\n");
				continue;
			}
			index = findIndexByName_d(employeeDat, buffer, OFFSET_EMPLOYEE, &tEmployee, sizeof(Employee_t));
			if (0 == index)
			{
				printf("没有符合条件的员工。按 Enter 键继续。\b");
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
		printf("确定要删除吗？[y/n]: ");
		char deleteOp = '\0';
		scanf("%c", &deleteOp);
		if (deleteOp != 'y' && deleteOp != 'n' && deleteOp != 'Y' && deleteOp != 'N')
		{
			printf("你输入的操作无效，请重新输入。\b\n");
			continue;
		}
		if (deleteOp == 'y' || deleteOp == 'Y')
		{
			del(employeeDat, index);
			printf("员工删除成功！\n");
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

	printf("================查找员工==================\n");
	unsigned int op = 0;
	while (true)
	{
		printf("选择操作条件 [0: ID, 1: 姓名]: ");
		scanf("%u", &op);
		if (op != 0 && op != 1)
		{
			printf("你输入的操作无效，请重新输入。\b\n");
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
			printf("请输入员工 ID: ");
			unsigned int tId = 0;
			scanf("%u", &tId);
			if (tId < 1000 || tId > 9999)
			{
				printf("你输入的 ID 无效，请重新输入。\b\n");
				continue;
			}
			index = findIndexByID_d(employeeDat, tId, &tEmployee, sizeof(Employee_t));
			if (0 == index)
			{
				printf("没有符合条件的员工。\b");
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
			printf("请输入员工姓名: ");
			scanf("%[^\n]", &buffer);
			if (strlen(buffer) > LEN_NAME - 1)
			{
				printf("你输入的姓名无效，请重新输入。\b\n");
				continue;
			}
			index = findIndexByName_d(employeeDat, buffer, OFFSET_EMPLOYEE, &tEmployee, sizeof(Employee_t));
			if (0 == index)
			{
				printf("没有符合条件的员工。按 Enter 键继续。\b");
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

