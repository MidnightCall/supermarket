/*****************************************************************//**
 * \file   employee.c
 * \brief  对超级管理员 (SU 权限) 的职工管理功能实现
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

/* 局部函数模型 */
static int getChoice();
static void showSingleEmployee(Employee_t e);
static void showAllEmployees(void);


/**
* \brief 运行职工管理模块
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
* \brief 添加新员工
*/
void addEmployee(void)
{
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));
	Employee_t* e = (Employee_t*)malloc(sizeof(Employee_t));
	assert(e != NULL);

	e->id = ++configDat.maxId_Employee; /* 自动赋予 ID */ /* checked */
	printf("═════════════════════添加员工═════════════════════\n");
	while (true)
	{
		printf("请输入员工姓名: ");
		stringGet(buffer, 250);
		if (strlen(buffer) > LEN_EMPLOYEE_NAME - 1 || strlen(buffer) < 4) /* 有一位要用来存放 '\0' 的，这里要减 1 */
		{
			printf("<!> 你输入的姓名无效，请重新输入。\a\n");
			continue;
		}
		memset(e->name, '\0', sizeof(e->name));
		strncpy(e->name, buffer, strlen(buffer));
		break;
	}
	
	while (true)
	{
		unsigned int tAge = 0;
		tAge = getNonNegativeNumber("请输入员工年龄: ");
		if (tAge < 16 || tAge > 70)
		{
			printf("<!> 你输入的年龄无效，请重新输入。\a\n");
			continue;
		}
		e->age = tAge;
		break;
	}

	while (true)
	{
		unsigned int tSex = 0;
		tSex = getNonNegativeNumber("请输入员工性别(0 为女，1 为男): ");
		if (tSex != 0 && tSex != 1)
		{
			printf("<!> 你输入的性别无效，请重新输入。\n");
			continue;
		}
		e->sex = tSex;
		break;
	}

	while (true)
	{
		printf("请输入员工职位: ");
		stringGet(buffer, 250);
		if (strlen(buffer) > LEN_EMPLOYEE_POS - 1 || 0 == strlen(buffer))
		{
			printf("<!> 你输入的职位无效，请重新输入。\a\n");
			continue;
		}
		memset(e->position, '\0', sizeof(e->position));
		strncpy(e->position, buffer, strlen(buffer));
		break;
	}

	insert(employeeDat, END, e);

	printf("员工增加成功！\n");
	PAUSE;
	return;
}

/**
* \brief 删除员工
*/
void deleteEmployee(void)
{
	Employee_t* tEmployee = NULL;
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("═════════════════════删除员工═════════════════════\n");
	unsigned int op = 0;
	while (true)
	{
		op = getNonNegativeNumber("输入查找条件[0: ID, 1: 姓名]: ");
		if (op != 0 && op != 1)
		{
			printf("<!> 你输入的操作无效，请重新输入。\a\n");
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
			tId = getNonNegativeNumber("请输入员工 ID: ");
			if (tId < 1000 || tId > 9999)
			{
				printf("<!> 你输入的 ID 无效，请重新输入。\a\n");
				continue;
			}
			index = findIndexByID_d(employeeDat, tId, &tEmployee);
			if (0 == index)
			{
				printf("<!> 没有符合条件的员工。\a");
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
			printf("请输入员工姓名: ");
			stringGet(buffer, 250);
			if (strlen(buffer) > LEN_EMPLOYEE_NAME - 1 || 0 == strlen(buffer))
			{
				printf("<!> 你输入的姓名无效，请重新输入。\a\n");
				continue;
			}
			index = findIndexByName_d(employeeDat, buffer, OFFSET_EMPLOYEE, &tEmployee);
			if (0 == index)
			{
				printf("<!> 没有符合条件的员工。\a");
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
		printf("确定要删除吗？[y/n]: ");
		char deleteOp = '\0';
		scanf("%c", &deleteOp);
		if (deleteOp != 'y' && deleteOp != 'n' && deleteOp != 'Y' && deleteOp != 'N')
		{
			printf("<!> 你输入的操作无效，请重新输入。\a\n");
			continue;
		}
		if (deleteOp == 'y' || deleteOp == 'Y')
		{
			del(employeeDat, index);
			printf("员工删除成功！");
			break;
		}
		if (deleteOp == 'n' || deleteOp == 'N')
			return;
	}

	PAUSE;
	return;
}

/**
* \brief 查找员工
*/
void findEmployee(void)
{
	Employee_t* tEmployee = NULL;
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("═════════════════════查找员工═════════════════════\n");
	unsigned int op = 0;
	while (true)
	{
		op = getNonNegativeNumber("选择操作条件 [0: ID, 1: 姓名]: ");
		if (op != 0 && op != 1)
		{
			printf("<!> 你输入的操作无效，请重新输入。\a\n");
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
			tId = getNonNegativeNumber("请输入员工 ID: ");
			if (tId < 1000 || tId > 9999)
			{
				printf("<!> 你输入的 ID 无效，请重新输入。\a\n");
				continue;
			}
			index = findIndexByID_d(employeeDat, tId, &tEmployee);
			if (0 == index)
			{
				printf("<!> 没有符合条件的员工。\a");
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
			printf("请输入员工姓名: ");
			stringGet(buffer, 250);
			if (strlen(buffer) > LEN_EMPLOYEE_NAME - 1 || 0 == strlen(buffer))
			{
				printf("<!> 你输入的姓名无效，请重新输入。\a\n");
				continue;
			}

			index = findIndexByName_d(employeeDat, buffer, OFFSET_EMPLOYEE, &tEmployee);
			if (0 == index)
			{
				printf("<!> 没有符合条件的员工。\a");
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
* \brief 修改员工信息
*/
void modifyEmployee(void)
{
	Employee_t* tEmployee = NULL;
	char buffer[250];
	memset(buffer, '\0', sizeof(buffer));

	printf("═══════════════════修改员工信息═══════════════════\n");
	unsigned int op = 0, index = 0;
	while (true)
	{
		unsigned int tId = 0;
		tId = getNonNegativeNumber("请输入员工 ID: ");
		if (tId < 1000 || tId > 9999)
		{
			printf("<!> 你输入的 ID 无效。\a");
			PAUSE;
			return;
		}
		index = findIndexByID_d(employeeDat, tId, &tEmployee);
		if (0 == index)
		{
			printf("<!> 没有符合条件的员工。\a");
			PAUSE;
			return;
		}
		showSingleEmployee(*tEmployee);
		break;
	}

	printf("════════════════════输入新信息════════════════════\n");
	while (true)
	{
		printf("请输入员工姓名: ");
		stringGet(buffer, 250);
		if (strlen(buffer) > LEN_EMPLOYEE_NAME - 1 || 0 == strlen(buffer))
		{
			printf("<!> 你输入的姓名无效，请重新输入。\a\n");
			continue;
		}
		memset(tEmployee->name, '\0', sizeof(tEmployee->name));
		strncpy(tEmployee->name, buffer, strlen(buffer));
		break;
	}

	while (true)
	{
		unsigned int tAge = 0;
		tAge = getNonNegativeNumber("请输入员工年龄: ");
		if (tAge < 16 || tAge > 70)
		{
			printf("<!> 你输入的年龄无效，请重新输入。\a\n");
			continue;
		}
		tEmployee->age = tAge;
		break;
	}

	while (true)
	{
		unsigned int tSex = 0;
		tSex = getNonNegativeNumber("请输入员工性别 (0 为女，1 为男): ");
		if (tSex != 0 && tSex != 1)
		{
			printf("<!> 你输入的性别无效，请重新输入。\a\n");
			continue;
		}
		tEmployee->sex = tSex;
		break;
	}

	while (true)
	{
		printf("请输入员工职位: ");
		stringGet(buffer, 250);

		if (strlen(buffer) > LEN_EMPLOYEE_POS - 1 || 0 == strlen(buffer))
		{
			printf("<!> 你输入的职位无效，请重新输入。\a\n");
			continue;
		}
		memset(tEmployee->position, '\0', sizeof(tEmployee->position));
		strncpy(tEmployee->position, buffer, strlen(buffer));
		break;
	}
	printf("员工信息修改成功！");

	PAUSE;
	return;
}

/**
* \brief 显示单条员工信息
*/
static void showSingleEmployee(Employee_t e)
{
	printf("┌──────┬─────────┬──员工信息────┬────────────────┐\n");
	printf("│ %5s│ %8s│ %6s│ %5s│ %15s│\n", "ID", "姓名", "性别", "年龄", "职位");
	printf("├──────┼─────────┼───────┼──────┼────────────────┤\n");
	printEmployeeInfo(&e);
	printf("└──────┴─────────┴───────┴──────┴────────────────┘\n");
}

/**
* \brief 显示所有员工信息
*/
static void showAllEmployees(void)
{
	if (0 == *(int*)employeeDat->data)
	{
		printf("<!> 没有员工信息。\a");
		return;
	}

	printf("┌──────┬─────────┬──员工信息────┬────────────────┐\n");
	printf("│ %5s│ %8s│ %6s│ %5s│ %15s│\n", "ID", "姓名", "性别", "年龄", "职位");
	printf("├──────┼─────────┼───────┼──────┼────────────────┤\n");
	printList(employeeDat, printEmployeeInfo, false);
	printf("└──────┴─────────┴───────┴──────┴────────────────┘\n");
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