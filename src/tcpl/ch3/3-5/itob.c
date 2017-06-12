/*
 * itob.c
 *
 *  Created on: Jun 10, 2017
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

/* 将数字n转换为b进制的字符串并保存到s中
 * 支持 INT_MIN
 */
static void itob(int n, char s[], const int b) {
	int i;
	unsigned int un;

	if (n < 0) {
		un = (unsigned int) -n;
	} else {
		un = (unsigned int) n;
	}

	i = 0;
	do {
		s[i++] = un % b + '0';
	} while ((un /= b) > 0);

	if (n < 0)
		s[i++] = '-';

	s[i] = '\0';
	reverse(s);
}

#if TEST
int main(void) {
	char s[100];
	int n, b;
	scanf("%d %d", &n, &b);

	itob(n, s, b);
	printf("%s\n", s);
	return EXIT_SUCCESS;
}
#endif
