/*
 * getch.c
 *
 *  Created on: Jun 12, 2017
 *      Author: niedaocai
 */
#include <stdio.h>

#include "calc.h"

#define BUFSIZE	100

static char buf[BUFSIZE]; /* 用于ungetch()的缓冲区 */
static int bufp = 0; /* 指向一个空闲的位置 */

/* 取一个字符
 * 如果缓冲区为空，从标准输入读一个
 * 如果缓冲区不为空,代表之前有压回的字符
 */
int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* 压回一个字符 */
void ungetch(int c) {
	if (bufp >= BUFSIZE)
		printf("ungetch: buf full\n");
	else
		buf[bufp++] = c;
}
