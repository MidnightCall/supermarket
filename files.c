#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkList.h"
#include "typeCollection.h"
#include "files.h"

const char* FILE_USER     = "data/user.dat";
const char* FILE_EMPLOYEE = "data/employee.dat";
const char* FILE_PRODUCT  = "data/product.dat";
const char* FILE_STORAGE  = "data/storage.dat";
const char* FILE_SUPPLIER = "data/supplier.dat";
const char* FILE_ORDER    = "data/order.dat";

void loadFile(const char* filename, Node_t* head, size_t size)
{
	FILE* fp = fopen(filename, "ab+"); /* ����ļ����������Զ����� */
	if (NULL == fp)
	{
		printf("�ļ� %s ��ʧ�ܡ�\b\n", filename);
		exit(0);
	}
	Node_t* tHead = head;
	
	/* ���ʹ�� feof(fp) ���µĶ��һ�����ݵ����� */
	fseek(fp, 0, SEEK_END);
	unsigned int length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	while (length != ftell(fp))
	{
		User_t* node = (User_t*)malloc(sizeof(User_t));
		if (NULL == node)
		{
			printf("����ڵ��ʼ��ʧ�ܡ�\b\n");
			exit(0);
		}
		fread(node, size, 1, fp);
		insert(tHead, END, node);
	}

	fclose(fp);
	return;
}

void writeFile(const char* filename, Node_t* head, size_t size)
{
	FILE* fp = fopen(filename, "wb");
	Node_t* tHead = head;
	int count = *(int*)(head->data);

	if (NULL == tHead->next) /* ֻ��һ���ڵ㣬˵��û��ʵ�����ݣ�ֱ�ӷ��� */
	{
		return;
	}

	tHead = head->next; /* ������һ����Žڵ����Ľڵ� */

	if (NULL == fp)
	{
		printf("�ļ� %s ��ʧ�ܡ�\b\n", filename);
		exit(0);
	}
	
	for (int i = 0; i < count; ++i)
	{
		fwrite(tHead->data, size, 1, fp);
		tHead = tHead->next;
	}

	fclose(fp);
	return;
}
