/*****************************************************************//**
 * \file   helpfulFunction.c
 * \brief  一些程序中常用的函数的集中实现
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
 * @brief 刷新缓冲区
 */
void flush(void)
{
	while (getchar() != '\n')
		continue;
}

/**
* @brief 读取一个字符串
*
* @param st 字符串存储到的地址
* @param n 最大读取字符个数
* @return 返回字符串地址
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
* @brief 判断字符串是否含非数字字符
*
* @param str 需要检测的字符串
*
* @return 如果含非数字字符，返回 false；如果不含，返回 true.
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
* @brief 把时间戳转换成标准格式时间
* @param time 时间戳
*
* @return 格式为 YY-MM-DD HH:MM:SS 的字符串
*/
char* timeConv(time_t time)
{
	/* 注意，在使用结束后应当立即释放 nowTime 所在的内存空间，否则可能导致内存泄露。*/
	char* nowTime = (char*)malloc(24);
	assert(nowTime != NULL);

	struct tm* stm = NULL;
	stm = localtime(&time);

	strftime(nowTime, 24, "%Y-%m-%d %H:%M:%S", stm);
	return nowTime;
}

/**
* @brief 读取一个非负整数
*
* @param hint 提示信息
*
* @return 返回读取到的结果
*/
int getNonNegativeNumber(char* hint)
{
	char temp[10];

	printf("请输入%s: ", hint);
	stringGet(temp, 10);
	while (hasNonNumerical(temp))
	{
		printf("非法输入，请重新输入\n");
		printf("请输入%s: ", hint);
		stringGet(temp, 10);
	}
	return atoi(temp);
}