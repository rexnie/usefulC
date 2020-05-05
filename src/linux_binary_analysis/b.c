#include<stdio.h>

int g_var = 3;
int func_g2(void)
{
	printf("in %s %d, g_var=%d\n", __func__, __LINE__, g_var);
}
