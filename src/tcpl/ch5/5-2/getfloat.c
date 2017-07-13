#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int getch(void);
void ungetch(int c);

/**
 * 将输入中的下一个浮点数赋值给*pn
 * 返回值：
 * 0 	不是数字
 * EOF	到达文件尾，输入结束
 * 其它	有效的数字，通过*pn返回
 *
 */
int getfloat(double *pn) {
	int c, sign;
	int shift;
	double frag;

	while (isspace(c = getch()))	/* 跳过空格 */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
		ungetch(c);	/*输入不是一个数字*/
		return 0;
	}

	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		int c_sign;

		c_sign = c;
		c = getch();
		if (!isdigit(c)) {	/* 符号位后面没有紧跟着数字 */
			while (isspace(c = getch())) /* 去掉符号位后面的空格 */
				;
			ungetch(c);
			ungetch(c_sign);
			return 0;
		}
	}

	if (isdigit(c))
		for (*pn = 0; isdigit(c); c = getch())	/*整数部分*/
			*pn = 10 * *pn + (c - '0');
	frag = 0.0;
	if (c == '.') {		/*处理小数部分*/
		c = getch();
		for (shift = 0; isdigit(c); c = getch()) {
			frag = 10 * frag + (c - '0');
			shift++; /*记录小数点的位置*/
		}
	}

	if (frag)
		*pn += frag / pow(10.0, shift);

	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

int main(void) {
	int n;

#define N	5

	double array[N] = {0, };

	for (n = 0; n < N && getfloat(&array[n]) != EOF; n++)
		;

	for (n = 0; n < N; n++) {
		printf("array[%d]=%g\n", n, array[n]);
	}

	return EXIT_SUCCESS;
}
