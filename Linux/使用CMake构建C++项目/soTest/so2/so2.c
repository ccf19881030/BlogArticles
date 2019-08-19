// so2/so2.c
#include <stdio.h>
#include <stdlib.h>
#include "so1.h"

int fun_test(int a)
{
	int i;
	for(i=0; i<a; ++i)
	{
		printf("add_fun(%d+%d)=%d\n", i, i, add_fun(i,i));
	}

	return 0;
}
