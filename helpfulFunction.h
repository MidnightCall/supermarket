#ifndef __HELPFULFUNCTION_H_
#define __HELPFULFUNCTION_H_

#include <stdio.h>
#include <stdbool.h>

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

#endif 