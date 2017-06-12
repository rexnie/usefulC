/*
 * stack.c
 *
 *  Created on: Jun 12, 2017
 *      Author: niedaocai
 */
#include <stdio.h>
#include "calc.h"

#define MAXVAL	100	/* 栈最大深度 */

static int sp = 0;
static double val[MAXVAL];

void pushd(double f) {
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double popd(void) {
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}
