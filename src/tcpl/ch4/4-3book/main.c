/*
 * main.c
 *
 *  Created on: Jun 12, 2017
 *      Author: niedaocai
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "calc.h"

#ifndef TEST
#define TEST    0
#endif

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
			if (op2 == 0.0)
				printf("error: divide by zero!!\n");
			else
				pushd(popd() / op2); /* 函数调用的参数的求值顺序不确定的，需要先在之前就得到op2 */
			break;
		case '\n':
			printf("\t%.8g\n", popd()); /* 一行读完，输出结果继续读下一行 */
			break;
		case '%':
			/**
			 * 关于数学中的模运算的说明：
			 *
			 * a = bn + r, 其中b为除数，不为0, n为整数，且 |r| < |b|
			 *
			 * c/java等语言，求模使用truncate，python使用floor.
			 * 详细参考:[详解负数取模运算] http://blog.csdn.net/hk2291976/article/details/52775299
			 * r = a - bn
			 * 	 = a - b * trunc(a/b)
			 */
			op2 = popd();
			if (op2 == 0.0)
				printf("error: divide by zero!!\n");
			else
				pushd(fmod(popd(), op2));
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return EXIT_SUCCESS;
}
#endif
