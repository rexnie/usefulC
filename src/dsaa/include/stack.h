/*
 * stack.h
 *
 *  Created on: Jun 12, 2017
 *      Author: niedaocai
 */
#include "ds.h"

typedef int ET;
#define MAXVAL	100	/* 栈最大深度 */

static int _sp = 0;
static ET _val[MAXVAL];

int is_stack_empty(void)
{
	return _sp == 0;
}

int nums_of_stack(void)
{
	return _sp;
}

void dump_stack(void) {
	int i;
	dbg("---dump_stack: _sp=%d\n", _sp);
	for (i = 0; i < _sp; i++)
		printf("%d ", _val[i]);
	printf("\n");
}

void push_stack(ET v) {
	if (_sp < MAXVAL)
		_val[_sp++] = v;
	else {
		err("stack full, can't push %d\n", v);
		dump_stack();
		exit(-1);
	}
}

ET pop_stack(void) {
	if (_sp > 0)
		return _val[--_sp];
	else {
		err("stack empty\n");
		dump_stack();
		exit(-1);
	}
}

ET peek_top(void) {
	if (_sp > 0)
		return _val[_sp - 1];

	err("stack is empty.\n");
	return 0;
}

void switch_top2(void) {
	if (_sp >= 2) {
		ET t;
		t = _val[_sp - 1];
		_val[_sp - 1] = _val[_sp - 2];
		_val[_sp - 2] = t;
	}
}

void clear_stack(void) {
	int i;
	for (i = 0; i < _sp; i++)
		_val[i] = 0;
	_sp = 0;
}
