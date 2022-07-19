/*****************************************************************//**
 * \file   files.c
 * \brief  对文件读写功能的实现
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

/* 文件名常量 */
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
* \brief 从文件中加载数据
*
* \param filename 文件名
* \param head 存放数据的链表头
* \param size 对应数据类型的大小，一般为 sizeof(xxx_t)
* \param curMaxId 用于回传链表中最大的 ID 值。若为 NULL 则不回传
*/
void loadFile(const char* filename, Node_t* head, size_t size, unsigned int* curMaxId)
{
	FILE* fp = fopen(filename, "ab+"); /* 如果文件不存在则自动创建 */
	if (NULL == fp)
	{
		printf("文件 %s 打开失败。\n", filename);
		exit(0);
	}
	Node_t* tHead = head;
	
	/* 规避使用 feof(fp) 导致的多读一组数据的问题 */
	fseek(fp, 0, SEEK_END);
	unsigned int length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	while (length != ftell(fp))
	{
		void* node = (void*)malloc(size); /* 创建新节点用于存储数据 */
		assert(node != NULL);

		fread(node, size, 1, fp);
		if (curMaxId != NULL)
			*curMaxId = *(unsigned int*)node; /* 由于默认插在链表尾，所以最大的 ID 应出现在最后一次插入的地方。故这里每次进行刷新 */
		insert(tHead, END, node);
	}

	fclose(fp);
	return;
}

/**
* \brief 将数据保存到文件中
*
* \param filename 文件名
* \param head 存放数据的链表头
* \param size 对应数据类型的大小，一般为 sizeof(xxx_t)
*/
void writeFile(const char* filename, Node_t* head, size_t size)
{
	FILE* fp = fopen(filename, "wb");
	Node_t* tHead = head;
	int count = *(int*)(head->data);

	if (NULL == tHead->next) /* 只有一个节点，说明没有实际数据，直接返回 */
	{
		return;
	}

	tHead = head->next; /* 跳过第一个存放节点数的节点 */

	if (NULL == fp)
	{
		printf("文件 %s 打开失败。\n", filename);
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
 * \brief 加载配置文件中记录的各个含 ID 的结构体类型的最大 ID 值
 */
void loadConfig()
{
	FILE* fp = fopen(FILE_CONFIG, "ab+"); /* 如果文件不存在则自动创建 */
	if (NULL == fp)
	{
		printf("文件 %s 打开失败。\n", FILE_CONFIG);
		exit(0);
	}
	fread(&configDat, sizeof(Config_t), 1, fp);

	/* 如果没有信息就先预设 */
	if (configDat.maxId_User < 10000)
		configDat.maxId_User = 10000; /* 因为默认超管的存在，这里就不用再减一了 */
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
 * \brief 保存配置文件中记录的各个含 ID 的结构体类型的最大 ID 值
 */
void saveConfig()
{
	FILE* fp = fopen(FILE_CONFIG, "wb");
	if (NULL == fp)
	{
		printf("文件 %s 打开失败。\n", FILE_CONFIG);
		exit(0);
	}
	fwrite(&configDat, sizeof(Config_t), 1, fp);
	fclose(fp);
	return;
}

/**
 * \brief 显示配置文件中记录的信息。仅供调试使用。
 */
void printConfig(void)
{
	printf("---<!!! 你正在调用一个仅供调试用的函数 !!!>---\a\n");
	printf("maxId_User: %7u\n", configDat.maxId_User);
	printf("maxId_Product: %7u\n", configDat.maxId_Product);
	printf("maxId_Employee: %7u\n", configDat.maxId_Employee);
	printf("maxId_Supplier: %7u\n", configDat.maxId_Supplier);
	printf("maxId_Order: %7u\n", configDat.maxId_Order);
	return;
}