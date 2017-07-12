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

/* 将数字n转换为字符串并保存到s中
 * 支持 INT_MIN
 */
void itoa(int n, char s[]) {
	int i;
	unsigned int un;

	i = 0;
	if (n < 0) {
		un = (unsigned int) -n;
		s[i++] = '-';
	} else {
		un = (unsigned int) n;
	}

	/**
	 * make sure that array s[] be initialized
	 * alternatively, you can initialize it in main()
	 */
	s[i] = '\0';
	if (un / 10)
		itoa(un / 10, &s[i]);

	i = strlen(s);
	s[i++] = un % 10 + '0';
}

int main(void) {
	char s[100]/* = {0,};*/;
	int n;
	scanf("%d", &n);

	itoa(n, s);
	printf("%s\n", s);
	return EXIT_SUCCESS;
}
