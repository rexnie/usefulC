#include<stdio.h>

#define LEN 1024

int g_array[LEN];
int g_int;
char g_charp[LEN];

int main(void)
{
	printf("sizeof(g_array,g_int,g_charp)=%d %d %d\n",
			sizeof(g_array), sizeof(g_int), sizeof(g_charp));
	return 0;
}
