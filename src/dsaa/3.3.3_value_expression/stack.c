/*
 * stack.c
 *
 *  Created on: Jun 12, 2017
 *      Author: niedaocai
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXVAL	100	/* 栈最大深度 */

static int sp = 0;
static double val[MAXVAL];

int is_stack_empty(void)
{
	return sp == 0;
}

void dump_stack(void) {
	int i;
	printf("---dump_stack: sp=%d\n", sp);
	for (i = 0; i < sp; i++)
		printf("%g ", val[i]);
	printf("\n");
}

void pushd(double f) {
	if (sp < MAXVAL)
		val[sp++] = f;
	else {
		printf("error: stack full, can't push %g\n", f);
		dump_stack();
		exit(-1);
	}
}

double popd(void) {
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		dump_stack();
		exit(-1);
	}
}

double peek_top(void) {
	if (sp > 0)
		return val[sp - 1];

	printf("stack is empty.\n");
	return 0.0;
}

void switch_top2(void) {
	if (sp >= 2) {
		double t;
		t = val[sp - 1];
		val[sp - 1] = val[sp - 2];
		val[sp - 2] = t;
	}
}

void clear_stack(void) {
	int i;
	for (i = 0; i < sp; i++)
		val[i] = 0.0;
	sp = 0;
}
