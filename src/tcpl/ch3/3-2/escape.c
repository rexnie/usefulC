/*
 * escape.c
 *
 *  Created on: Jun 10, 2017
 *      Author: niedaocai
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TEST
#define TEST    0
#endif

/**
 * 将字符串t拷贝到s,遇到换行符'\n'，制表符'\t'等不可打印字符转换为"\\n", "\\t"
 * 等对应的可见的转义字符序列
 */
char *escape(char *s, const char *t)
{
	int i, j;

	for (i = 0, j = 0; t[j] != '\0'; j++) {
		switch(t[j]) {
		case '\a':		/* BEL */
			s[i++] = '\\';
			s[i++] = 'a';
			break;
		case '\b':
			s[i++] = '\\';
			s[i++] = 'b';
			break;
		case '\t':
			s[i++] = '\\';
			s[i++] = 't';
			break;
		case '\n':	/* LF */
			s[i++] = '\\';
			s[i++] = 'n';
			break;
		case '\v':
			s[i++] = '\\';
			s[i++] = 'v';
			break;
		case '\f':
			s[i++] = '\\';
			s[i++] = 'f';
			break;
		case '\r':	/* CR */
			s[i++] = '\\';
			s[i++] = 'r';
			break;
		case '\e':
			s[i++] = '\\';
			s[i++] = 'e';
			break;
		case '\\':
			s[i++] = '\\';
			s[i++] = '\\';
			break;
		default:
			s[i++] = t[j];
		}
	}
	s[i] = '\0';
	return s;
}
/**
 * 将字符串s拷贝到r,遇到转义字符序列的，将它转换为实际的字符。
 * 如"\\n" --> '\n', "\\t" --> '\t'
 */
char *escape_r(char *r, const char *s)
{
	int i, j;

	for (i = 0, j = 0; s[j] != '\0';) {
		if (s[j] == '\\') {
			switch (s[j+1]) {
			case 'a':
				r[i++] = '\a';
				j += 2;
				break;
			case 'b':
				r[i++] = '\b';
				j += 2;
				break;
			case 't':
				r[i++] = '\t';
				j += 2;
				break;
			case 'n':
				r[i++] = '\n';
				j += 2;
				break;
			case 'v':
				r[i++] = '\v';
				j += 2;
				break;
			case 'f':
				r[i++] = '\f';
				j += 2;
				break;
			case 'r':
				r[i++] = '\r';
				j += 2;
				break;
			case 'e':
				r[i++] = '\e';
				j += 2;
				break;
			case '\\':
				r[i++] = '\\';
				j += 2;
				break;
			default:
				r[i++] = s[j++];
				break;
			}
		} else {
			r[i++] = s[j++];
		}
	}

	r[i] = '\0';
	return r;
}

#if TEST
int main(void) {
	char s[100] = "";
	char r[100] = "";
	char *t = "\\C\nh\rina";

	printf("t=%s, len(t)=%ld, %s, len(s)=%ld\n", t, strlen(t), escape(s, t), strlen(s));

	printf("%s, len(r)=%ld\n", escape_r(r, s), strlen(r));

	return EXIT_SUCCESS;
}
#endif
