#include <string.h>
#include "files.h"
#include "linkList.h"

extern Node_t* employeeDat;

void showAllEmployees()
{
	printf("================Ա����Ϣ==================\n");
	printf("%5s| %8s| %4s| %5s| %11s|\n", "ID", "����", "�Ա�", "����", "ְλ");
	printf("-----+---------+-----+------+------------+\n");
	printList(employeeDat, printEmployeeInfo, false);
	printf("==========================================\n");
	return;
}

void addEmployee(void)
{

}

