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
	int i, c, f;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;

	s[1] = '\0';

	if (c == '-' || c == '+') { /* c 是'+'或者'-',根据下个字符来判断是否是符号位,还是加减号 */
		ungetch((f = getch())); // 只是瞟一眼后面的字符
		if (isdigit(f) || f == '.') { /* 紧跟的是数字，是符号位，符号放在数组一起返回给atof() */
			c = f; // 避免line#33直接退出
		} else {
			return c;
		}
	} else if (!isdigit(c) && c != '.') { /* 不是数 */
		return c;
	}

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

