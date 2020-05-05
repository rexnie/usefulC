#include<stdio.h>
static int g_var = 1;
extern int func_g2(void);

static void func_s()
{
	printf("in %s %d\n", __func__, __LINE__);
}

void func_g1()
{
	printf("in %s %d\n", __func__, __LINE__);
}

int main(void)
{
	static int g_var = 2;
	func_s();
	func_g1();
	func_g2();
	printf("in %s %d, g_var=%d\n", __func__, __LINE__, g_var);
	return 0;
}
