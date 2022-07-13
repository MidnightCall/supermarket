#include <string.h>
#include "files.h"
#include "linkList.h"

extern Node_t* employeeDat;

void showAllEmployees()
{
	printf("================员工信息==================\n");
	printf("%5s| %8s| %4s| %5s| %11s|\n", "ID", "姓名", "性别", "年龄", "职位");
	printf("-----+---------+-----+------+------------+\n");
	printList(employeeDat, printEmployeeInfo, false);
	printf("==========================================\n");
	return;
}

void addEmployee(void)
{

}

