/*
 * getop.c
 *
 *  Created on: Jun 12, 2017
 *      Author: niedaocai
 */
#include <ctype.h>
#include "ds.h"
#include "expr.h"

/**
 * 分析中缀表达式的字符串
 * 返回值是TYPE_OPERATOR, TYPE_NUM和'\0',
 * out_str[] 为对应的token字串
 *
 * 对于负号和减号的区分，主要判别方法为：
 * 　　1）若前一个字符为‘('，则必定为负号； 如，3*(-4)
 *
 * 　　2）若前一个字符为')'或者数字，则必定为减号； 如，3-4
 *
 * 　　3）若前面一个字符为其他运算符，如*，/，则必定是负号； 如，3*-4
 *
 * 　　3）若前面没有字符，即该字符为表达式的第一个字符，则必定是负号。如，-3 * 4
 *
 * 　　也就是说只有一种情况下，”-“是作为减号使用的，就是前一个字符为')'或者数字的时候。
 *
 * 　　如果判断出“-”是作为负号使用的，这里我采用“#”来代替“-”，并将其作为一种运算符
 *  ref: http://blog.csdn.net/yuyanggo/article/details/48063473
 */
int getop(char **p, char out_str[]) {
	int i = 0;
	char *n;

	dbg("*p=%s\n", *p);
	if (**p == '\0')
		return '\0';

	if (**p == '-' || **p == '+') { /* *p 是'+'或者'-',根据下个字符来判断是否是符号位,还是加减号 */
		n = *p - 1;
		if (isdigit(*n) || *n == ')') { /* 前一个字符是数字或')'，是加号/减号 */
			out_str[i++] = **p;
		} else { /* 否则就是正/负号 */
			out_str[i++] = **p == '-' ? '#': '$';
		}
		out_str[i] = '\0';
		(*p)++;
		return TYPE_OPERATOR;
	} else if (!isdigit(**p) && **p != '.') { /* 不是数 */
		out_str[0] = **p;
		out_str[1] = '\0';
		(*p)++;
		return TYPE_OPERATOR;
	}

	if (isdigit(**p)) /* 收集整数部分 */
		while (isdigit(**p)) {
			out_str[i++] = **p;
			(*p)++;
		}
	if (**p == '.') { /* 收集小数部分 */
		out_str[i++] = **p; /* 小数点 */
		(*p)++;
		while (isdigit(**p)) {
			out_str[i++] = **p;
			(*p)++;
		}
	}

	out_str[i] = '\0';

	dbg("*p=%s\n", *p);
	return TYPE_NUM;
}
