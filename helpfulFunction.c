/*****************************************************************//**
 * \file   helpfulFunction.c
 * \brief  һЩ�����г��õĺ����ļ���ʵ��
 *
 * \author praist
 * \date   July 2022
 *********************************************************************/

#include "helpfulFunction.h"
#include "SupermarketManageSystem.h"
#include "customLookup.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

 /**
 * @brief ˢ�»�����
 */
void flush(void)
{
	while (getchar() != '\n')
		continue;
}

/**
* @brief ��ȡһ���ַ���
*
* @param st �ַ����洢���ĵ�ַ
* @param n ����ȡ�ַ�����
* @return �����ַ�����ַ
*/
char* stringGet(char* st, int n)
{
	char* ret_val = NULL;
	char* find = NULL;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');
		if (find) {
			*find = '\0';
		}
		else {
			while (getchar() != '\n')
				continue;
		}
	}
	return ret_val;
}

/**
* @brief �ж��ַ����Ƿ񺬷������ַ�
*
* @param str ��Ҫ�����ַ���
*
* @return ������������ַ������� false��������������� true.
*/
bool hasNonNumerical(char* str)
{
	for (int i = 0; i < strlen(str); ++i)
	{
		if (!isdigit(str[i]))
		{
			return true;
		}
	}
	return false;
}

/**
* @brief ��ʱ���ת���ɱ�׼��ʽʱ��
* @param time ʱ���
*
* @return ��ʽΪ YY-MM-DD HH:MM:SS ���ַ���
*/
char* timeConv(time_t time)
{
	/* ע�⣬��ʹ�ý�����Ӧ�������ͷ� nowTime ���ڵ��ڴ�ռ䣬������ܵ����ڴ�й¶��*/
	char* nowTime = (char*)malloc(24);
	assert(nowTime != NULL);

	struct tm* stm = NULL;
	stm = localtime(&time);

	strftime(nowTime, 24, "%Y-%m-%d %H:%M:%S", stm);
	return nowTime;
}

/**
* @brief ��ȡһ���Ǹ�����
*
* @param hint ��ʾ��Ϣ
*
* @return ���ض�ȡ���Ľ��
*/
int getNonNegativeNumber(char* hint)
{
	char temp[10];

	printf("������%s: ", hint);
	stringGet(temp, 10);
	while (hasNonNumerical(temp))
	{
		printf("�Ƿ����룬����������\n");
		printf("������%s: ", hint);
		stringGet(temp, 10);
	}
	return atoi(temp);
}