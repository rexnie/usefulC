/*
 * main.c
 *
 *  Created on: Jun 12, 2017
 *      Author: niedaocai
 */

#include <stdio.h>
#include <stdlib.h>

#include "calc.h"

#define TEST    1

#define MAXOP	100

#if TEST
/* 逆波兰计算器,即求解后缀表达式 */
int main(void) {
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			pushd(atof(s));
			break;
		case '+':
			pushd(popd() + popd());
			break;
		case '*':
			pushd(popd() * popd());
			break;
		case '-':
			op2 = popd();
			pushd(popd() - op2); /* 函数调用的参数的求值顺序不确定的，需要先在之前就得到op2 */
			break;
		case '/':
			op2 = popd();
			pushd(popd() / op2); /* 函数调用的参数的求值顺序不确定的，需要先在之前就得到op2 */
			break;
		case '\n':
			printf("\t%.8g\n", popd()); /* 一行读完，输出结果继续读下一行 */
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return EXIT_SUCCESS;
}
#endif
