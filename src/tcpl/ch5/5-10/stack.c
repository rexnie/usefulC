#include <stdio.h>
#include "stack.h"

static double *sp = NULL;

#define MAXVAL 	1000
double stack_val[MAXVAL];

void init_stack(void)
{
	sp = &stack_val;
}

double pop(void)
{
	if (sp <= stack_val) {
		printf("pop error: stack is empty\n");
		return 0.0;
	}
	return *--sp;
}

void push(double v)
{
	if (sp > stack_val + MAXVAL) {
		printf("push error: stack is full\n");
		return;
	}
	*sp++ = v;
}
