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
#include <stdbool.h>

static bool hasExcessiveDots(char* str);

 /**
 * \brief 刷新缓冲区
 */
void flush(void)
{
	while (getchar() != '\n')
		continue;
}

/**
* \brief 读取一个字符串
*
* \param st 字符串存储到的地址
* \param n 最大读取字符个数
* \return 返回字符串地址
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
* \brief 判断字符串是否含非数字字符
*
* \param str 需要检测的字符串
* \param omitDot 是否忽略小数点
*
* \return 如果含非数字字符，返回 false；如果不含，返回 true.
*/
bool hasNonNumerical(char* str, bool omitDot)
{
	for (int i = 0; i < strlen(str); ++i)
	{
		if ((!omitDot && !isdigit(str[i]) 
			|| (omitDot && (str[i] < '0' || str[i] > '9') && str[i] != '.')))
		{
			return true;
		}
	}
	return false;
}

/**
* \brief 把时间戳转换成标准格式时间
* \param time 时间戳
*
* \return 格式为 YY-MM-DD HH:MM:SS 的字符串
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
* \brief 读取一个非负整数
*
* \param hint 提示信息
*
* \return 返回读取到的结果
*/
int getNonNegativeNumber(char* hint)
{
	char temp[10];

	printf("%s", hint);
	stringGet(temp, 10);
	while (hasNonNumerical(temp, false))
	{
		printf("<!> 非法输入，请重新输入\a\n");
		printf("%s", hint);
		stringGet(temp, 10);
	}
	return atoi(temp);
}

/**
* \brief 读取一个非负浮点数
*
* \param hint 提示信息
*
* \return 返回转换后的浮点数
*/
float getNonNegativeFloat(char* hint)
{
	char temp[10];

	printf("%s", hint);
	stringGet(temp, 10);

	while (hasNonNumerical(temp, true) || hasExcessiveDots(temp))
	{
		printf("<!> 非法输入，请重新输入。\a\n");
		printf("%s", hint);
		stringGet(temp, 10);
	}
	
	return (float)atof(temp);	
}

/**
 * \brief 判断字符串是否有两个及以上的点
 * 
 * \param str
 * \return 若字符串有两个及以上的点，返回 true，否则返回 false.
 */
static bool hasExcessiveDots(char* str)
{
	short dotCount = 0;
	for (int i = 0; i < strlen(str); ++i)
	{
		if (str[i] == '.')
		{
			++dotCount;
			if (dotCount > 1)
				return true;
		}
	}

	return false;
}

/**
 * \brief 用于菜单界面选项数字的读入
 *
 * \return 一个选项数字对应的整数
 */
int getMenuChoice()
{
	char temp[10];

	HINT;
	stringGet(temp, 10);
	if (hasNonNumerical(temp, false))
		return 0;
	else
		return atoi(temp);
}
