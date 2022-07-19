/*****************************************************************//**
 * \file   files.c
 * \brief  ���ļ���д���ܵ�ʵ��
 *
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkList.h"
#include "helpfulFunction.h"
#include "typeCollection.h"
#include "files.h"

/* �ļ������� */
const char* FILE_USER     = "data/user.dat";
const char* FILE_EMPLOYEE = "data/employee.dat";
const char* FILE_PRODUCT  = "data/product.dat";
const char* FILE_ONSALE   = "data/onsale.dat";
const char* FILE_STORAGE  = "data/storage.dat";
const char* FILE_SUPPLIER = "data/supplier.dat";
const char* FILE_ORDER    = "data/order.dat";
const char* FILE_CONFIG   = "data/config.dat";

extern Config_t configDat;

/**
* \brief ���ļ��м�������
*
* \param filename �ļ���
* \param head ������ݵ�����ͷ
* \param size ��Ӧ�������͵Ĵ�С��һ��Ϊ sizeof(xxx_t)
* \param curMaxId ���ڻش����������� ID ֵ����Ϊ NULL �򲻻ش�
*/
void loadFile(const char* filename, Node_t* head, size_t size, unsigned int* curMaxId)
{
	FILE* fp = fopen(filename, "ab+"); /* ����ļ����������Զ����� */
	if (NULL == fp)
	{
		printf("�ļ� %s ��ʧ�ܡ�\n", filename);
		exit(0);
	}
	Node_t* tHead = head;
	
	/* ���ʹ�� feof(fp) ���µĶ��һ�����ݵ����� */
	fseek(fp, 0, SEEK_END);
	unsigned int length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	while (length != ftell(fp))
	{
		void* node = (void*)malloc(size); /* �����½ڵ����ڴ洢���� */
		assert(node != NULL);

		fread(node, size, 1, fp);
		if (curMaxId != NULL)
			*curMaxId = *(unsigned int*)node; /* ����Ĭ�ϲ�������β���������� ID Ӧ���������һ�β���ĵط���������ÿ�ν���ˢ�� */
		insert(tHead, END, node);
	}

	fclose(fp);
	return;
}

/**
* \brief �����ݱ��浽�ļ���
*
* \param filename �ļ���
* \param head ������ݵ�����ͷ
* \param size ��Ӧ�������͵Ĵ�С��һ��Ϊ sizeof(xxx_t)
*/
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
		printf("�ļ� %s ��ʧ�ܡ�\n", filename);
		PAUSE;
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

/**
 * \brief ���������ļ��м�¼�ĸ����� ID �Ľṹ�����͵���� ID ֵ
 */
void loadConfig()
{
	FILE* fp = fopen(FILE_CONFIG, "ab+"); /* ����ļ����������Զ����� */
	if (NULL == fp)
	{
		printf("�ļ� %s ��ʧ�ܡ�\n", FILE_CONFIG);
		exit(0);
	}
	fread(&configDat, sizeof(Config_t), 1, fp);

	/* ���û����Ϣ����Ԥ�� */
	if (configDat.maxId_User < 10000)
		configDat.maxId_User = 10000; /* ��ΪĬ�ϳ��ܵĴ��ڣ�����Ͳ����ټ�һ�� */
	if (configDat.maxId_Product < 100000)
		configDat.maxId_Product = 99999;
	if (configDat.maxId_Employee < 1000)
		configDat.maxId_Employee = 999;
	if (configDat.maxId_Supplier < 100)
		configDat.maxId_Supplier = 99;
	if (configDat.maxId_Order < 1000000)
		configDat.maxId_Order = 999999;

	fclose(fp);
	return;
}

/**
 * \brief ���������ļ��м�¼�ĸ����� ID �Ľṹ�����͵���� ID ֵ
 */
void saveConfig()
{
	FILE* fp = fopen(FILE_CONFIG, "wb");
	if (NULL == fp)
	{
		printf("�ļ� %s ��ʧ�ܡ�\n", FILE_CONFIG);
		exit(0);
	}
	fwrite(&configDat, sizeof(Config_t), 1, fp);
	fclose(fp);
	return;
}

/**
 * \brief ��ʾ�����ļ��м�¼����Ϣ����������ʹ�á�
 */
void printConfig(void)
{
	printf("---<!!! �����ڵ���һ�����������õĺ��� !!!>---\a\n");
	printf("maxId_User: %7u\n", configDat.maxId_User);
	printf("maxId_Product: %7u\n", configDat.maxId_Product);
	printf("maxId_Employee: %7u\n", configDat.maxId_Employee);
	printf("maxId_Supplier: %7u\n", configDat.maxId_Supplier);
	printf("maxId_Order: %7u\n", configDat.maxId_Order);
	return;
}