#ifndef __HELPFULFUNCTION_H_
#define __HELPFULFUNCTION_H_

#include <stdio.h>
#include <string.h>

/**
* @brief 刷新缓冲区
*
*/
void flush();

/**
* @brief 读取一个字符串
* @param st 字符串读取到的地址
* @param n 最大读取字符个数
* @return 返回字符串地址
*/
char* stringGet(char* st, int n);

#endif 