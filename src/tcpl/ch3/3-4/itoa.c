/*
 * itoa.c
 *
 *  Created on: Jun 12, 2017
 *      Author: niedaocai
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define TEST    0

/* 反转字符串s */
static void reverse(char s[]) {
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/* 将数字n转换为字符串并保存到s中
 * 支持 INT_MIN
 */
void itoa2(int n, char s[]) {
	int i;
	unsigned int un;

	if (n < 0) {
		un = (unsigned int) -n;
	} else {
		un = (unsigned int) n;
	}

	i = 0;
	do {
		s[i++] = un % 10 + '0';
	} while ((un /= 10) > 0);

	if (n < 0)
		s[i++] = '-';

	s[i] = '\0';
	reverse(s);
}

/* 将数字n转换为字符串并保存到s中
 * 不支持 INT_MIN
 */
void itoa(int n, char s[]) {
	int i, sign;

	if ((sign = n) < 0)
		n = -n;

	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);

	if (sign < 0)
		s[i++] = '-';

	s[i] = '\0';
	reverse(s);
}

#if TEST
int main(void) {
	char s[100];
	int n;
	scanf("%d", &n);

	itoa(n, s);
	printf("%s\n", s);
	itoa2(n, s);
	printf("%s\n", s);
	return EXIT_SUCCESS;
}
#endif
