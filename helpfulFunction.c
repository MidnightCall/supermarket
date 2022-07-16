#include "helpfulFunction.h"
#include "SupermarketManageSystem.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void flush()
{
	while (getchar() != '\n')
		continue;
}

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

char* timeConv(time_t time)
{
	char* nowTime = (char*)malloc(24);
	assert(nowTime != NULL);

	struct tm* stm = NULL;
	stm = localtime(&time);

	strftime(nowTime, 24, "%Y-%m-%d %H:%M:%S", stm);
	return nowTime;
}

int getAnNonNegativeDigit(char hint[91])
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