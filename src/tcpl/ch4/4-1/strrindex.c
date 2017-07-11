/*
 * strrindex.c
 *
 *  Created on: Jun 10, 2017
 *      Author: niedaocai
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef TEST
#define TEST    0
#endif

/* 返回字符串t在s中最右边出现的位置，如果s不包含t,返回-1 */
int strrindex(char s[], char t[]) {
	int i, j, k;
	int end_index_t = strlen(t) - 1;

	for (i = strlen(s) - 1; i >= end_index_t; i--) {
		for (j = i, k = end_index_t; k >= 0 && s[j] == t[k]; j--, k--)
			;

		if (k < 0)
			return j + 1;
	}
	return -1;
}

#if TEST
int main(void) {
	char s[100];
	char t[100];
	scanf("%s %s", s, t);

	printf("%d\n", strrindex(s, t));
	return EXIT_SUCCESS;
}
#endif
