#include "ds.h"
#include "stack.h"

static int _sp = 0;
static ET_Stack2 _val[MAXVAL];

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
		printf("%g ", _val[i]);
	printf("\n");
}

void push_stack(ET_Stack2 v) {
	if (_sp < MAXVAL)
		_val[_sp++] = v;
	else {
		err("stack full, can't push %g\n", v);
		dump_stack();
		exit(-1);
	}
}

ET_Stack2 pop_stack(void) {
	if (_sp > 0)
		return _val[--_sp];
	else {
		err("stack empty\n");
		dump_stack();
		exit(-1);
	}
}

ET_Stack2 peek_top(void) {
	if (_sp > 0)
		return _val[_sp - 1];

	err("stack is empty.\n");
	return 0;
}

void switch_top2(void) {
	if (_sp >= 2) {
		ET_Stack2 t;
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
