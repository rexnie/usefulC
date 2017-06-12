/*
 * getop.c
 *
 *  Created on: Jun 12, 2017
 *      Author: niedaocai
 */
#include <ctype.h>
#include <stdio.h>
#include "calc.h"

int getop(char s[]) {
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;

	s[1] = '\0';

	if (!isdigit(c) && c != '.') /* 不是数 */
		return c;

	i = 0;
	if (isdigit(c)) /* 收集整数部分 */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.') /* 收集小数部分 */
		while (isdigit(s[++i] = c = getch()))
			;

	s[i] = '\0';

	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

