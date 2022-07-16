#ifndef __HELPFULFUNCTION_H_
#define __HELPFULFUNCTION_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

/* ����ռλ�� */
#define PASS printf("To be continued... [%s, %s(), LINE %d]", __FILE__, __FUNCTION__, __LINE__)
#define PAUSE system("pause")
#define HINT printf(">>> ")

/**
* @brief ˢ�»�����
*
*/
void flush();

/**
* @brief ��ȡһ���ַ���
* 
* @param st �ַ�����ȡ���ĵ�ַ
* @param n ����ȡ�ַ�����
* @return �����ַ�����ַ
*/
char* stringGet(char* st, int n);

/**
* @brief �ж��ַ����Ƿ񺬷������ַ�
* 
* @param str ��Ҫ�����ַ���
* 
* @return ������������ַ������� false��������������� true.
*/
bool hasNonNumerical(char* str);

/**
* @brief ��ʱ���ת���ɱ�׼��ʽʱ��
*
* @param time ʱ���
*
* @return ��ʽΪ YY-MM-DD HH:MM:SS ���ַ���
*/
char* timeConv(time_t time);
#endif 