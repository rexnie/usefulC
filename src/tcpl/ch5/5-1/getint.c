#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int getch(void);
void ungetch(int c);

/**
 * 将输入中的下一个整形数赋值给*pn
 * 返回值：
 * 0 	不是数字
 * EOF	到达文件尾，输入结束
 * 其它	有效的数字，通过*pn返回
 *
 */
int getint(int *pn) {
	int c, sign;

	while (isspace(c = getch()))	/* 跳过空格 */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);	/*输入不是一个数字*/
		return 0;
	}

	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

int main(void) {
	int n;

#define N	5

	int array[N] = {0, };
	
	for (n = 0; n < N && getint(&array[n]) != EOF; n++)
		;
	
	for (n = 0; n < N; n++) {
		printf("array[%d]=%d\n", n, array[n]);
	}

	return EXIT_SUCCESS;
}
