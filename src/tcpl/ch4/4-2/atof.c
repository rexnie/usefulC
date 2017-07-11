/*
 * atof.c
 *
 *  Created on: Jun 12, 2017
 *      Author: niedaocai
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#ifndef TEST
#define TEST    0
#endif

/* 把字符串s转换为相应的双精度浮点数 */
double my_atof(char s[]) {
	double val, power;
	int i, sign;

	for (i = 0; isspace(s[i]); i++)
		/* 去掉前导空格 */
		;

	sign = (s[i] == '-') ? -1 : 1;

	if (s[i] == '+' || s[i] == '-')
		i++;

	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + s[i] - '0';

	if (s[i] == '.')
		i++;

	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + s[i] - '0';
		power *= 10.0;
	}

	return sign * val / power;
}

/* 把字符串s转换为相应的双精度浮点数
 * 扩展支持 3.14e-8
 */
double my_atof2(char s[]) {
	double val;
	int power;
	int i, sign, sign_e = 1;
	int val_e;

	for (i = 0; isspace(s[i]); i++)
		;

	sign = (s[i] == '-') ? -1 : 1;

	if (s[i] == '+' || s[i] == '-')
		i++;

	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + s[i] - '0';

	if (s[i] == '.')
		i++;

	for (power = 0; isdigit(s[i]); i++) {
		val = 10.0 * val + s[i] - '0';
		power -= 1; /* 只记录位数，不做实际的除法，是否会溢出?? */
	}

	if (s[i] == 'e' || s[i] == 'E')
		i++;

	if (s[i] == '-')
		sign_e = -1;

	if (s[i] == '+' || s[i] == '-')
		i++;

	for (val_e = 0; isdigit(s[i]); i++)
		val_e = 10 * val_e + s[i] - '0';

	if (sign_e < 0)
		val_e = -val_e;

	return sign * val * pow(10, val_e + power);
}
#if TEST
int main(void) {
	char s[100];
	scanf("%s", s);

	printf("%g\n", my_atof2(s));
	return EXIT_SUCCESS;
}
#endif
