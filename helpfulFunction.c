#include "helpfulFunction.h"
#include <stdio.h>

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