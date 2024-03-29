/*****************************************************************//**
 * \file   helpfulFunction.h
 * \brief  一些程序中常用的函数的集中实现
 * 
 * \author praist
 * \date   July 2022
 *********************************************************************/

#ifndef __HELPFULFUNCTION_H_
#define __HELPFULFUNCTION_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

/* 功能占位符 */
#define PASS printf("To be continued... [%s, %s(), LINE %d]", __FILE__, __FUNCTION__, __LINE__)
#define PAUSE system("pause")
#define HINT printf(">>> ")

/**
* \brief 刷新缓冲区
*/
void flush(void);

/**
* \brief 读取一个字符串
* 
* \param st 字符串存储到的地址
* \param n 最大读取字符个数
* \return 返回字符串地址
*/
char* stringGet(char* st, int n);

/**
* \brief 判断字符串是否含非数字字符
* 
* \param str 需要检测的字符串
* \param omitDot 是否忽略小数点
* 
* \return 如果含非数字字符，返回 false；如果不含，返回 true.
*/
bool hasNonNumerical(char* str, bool omitDot);

/**
* \brief 把时间戳转换成标准格式时间
*
* \param time 时间戳
*
* \return 格式为 YY-MM-DD HH:MM:SS 的字符串
*/
char* timeConv(time_t time);

/**
* \brief 读取一个非负整数
*
* \param hint 提示信息
*
* \return 返回读取到的结果
*/
int getNonNegativeNumber(char* hint);

/**
* \brief 读取一个非负浮点数
*
* \param hint 提示信息
*
* \return 返回转换后的浮点数
*/
float getNonNegativeFloat(char* hint);

/**
 * \brief 用于菜单界面选项数字的读入
 * 
 * \return 一个选项数字对应的整数
 */
int getMenuChoice();


#endif 