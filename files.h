#ifndef __FILES_C_
#define __FILES_C_

#include "typeCollection.h"

/* �ļ������������嶨���� files.c �� */

extern const char* FILE_USER;
extern const char* FILE_EMPLOYEE;
extern const char* FILE_PRODUCT;
extern const char* FILE_ONSALE;
extern const char* FILE_STORAGE;
extern const char* FILE_SUPPLIER;
extern const char* FILE_ORDER;


/**
* @brief ���ļ��м�������
* 
* @param filename �ļ���
* @param head ������ݵ�����ͷ
* @param size ��Ӧ�������͵Ĵ�С��һ��Ϊ sizeof(xxx_t)
* @param curMaxId ���ڻش����������� ID ֵ����Ϊ NULL �򲻻ش�
*/
void loadFile(const char* filename, Node_t* head, size_t size, unsigned int* curMaxId);

/**
* @brief �����ݱ��浽�ļ���
* 
* @param filename �ļ���
* @param head ������ݵ�����ͷ
* @param size ��Ӧ�������͵Ĵ�С��һ��Ϊ sizeof(xxx_t)
*/
void writeFile(const char* filename, Node_t* head, size_t size);

void loadConfig(void);

void saveConfig(void);

/* --! ��������ʹ�� --! */
void printConfig(void);
#endif