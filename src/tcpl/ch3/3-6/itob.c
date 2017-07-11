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

#include "stack.h"

#ifndef TEST
#define TEST    0
#endif

/* 将数字n转换为b进制的字符串并保存到s中，指定字符宽度，
 * 不足的左边填充空格
 * 支持 INT_MIN
 */
static void itob(int n, char s[], const int b, const int width) {
	int i, j, space, elem;
	unsigned int un;

	if (n < 0) {
		un = (unsigned int) -n;
	} else {
		un = (unsigned int) n;
	}

	init_stack(); /*使用栈的FILO的特性，避免反转字符串*/
	do {
		push(un % b + '0');
	} while ((un /= b) > 0);

	if (n < 0)
		push('-');

	elem = get_element_num_in_stack();
	space = width - elem; /* 需要填充空格的个数 */

	for (i = 0; i < space; i++)
		s[i] = ' ';

	for (j = 0; j < elem; j++)
		s[i++] = pop();
	s[i] = '\0';
}

#if TEST
int main(void) {
	char s[100];
	int n, b, w;
	scanf("%d %d %d", &n, &b, &w);

	itob(n, s, b, w);
	printf("%s\n", s);
	return EXIT_SUCCESS;
}
#endif
