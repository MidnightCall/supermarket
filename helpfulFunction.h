#ifndef __HELPFULFUNCTION_H_
#define __HELPFULFUNCTION_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* 功能占位符 */
#define PASS printf("To be continued... [%s, %s(), LINE %d]", __FILE__, __FUNCTION__, __LINE__)

/**
* @brief 刷新缓冲区
*
*/
void flush();

/**
* @brief 读取一个字符串
* 
* @param st 字符串读取到的地址
* @param n 最大读取字符个数
* @return 返回字符串地址
*/
char* stringGet(char* st, int n);

/**
* @brief 判断字符串是否含非数字字符
* 
* @param str 需要检测的字符串
* 
* @return 如果含非数字字符，返回 false；如果不含，返回 true.
*/
bool hasNonNumerical(char* str);

#endif 