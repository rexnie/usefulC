#include <stdio.h>
#include <string.h>

#define MAX_VAL 32
#include "stack.h"

int sp = -1;
char val[MAX_VAL];

int init_stack(void) {
	memset((void* )val, 0, (size_t)MAX_VAL);
	sp = -1;
}

int push(char ch) {
	if (sp >= MAX_VAL - 1) {
		printf("stack is full\n");
		return -1;
	} else {
		val[++sp] = ch;
		return 0;
	}
}

char pop(void) {
	if (sp < 0) {
		printf("stack is empty\n");
		return EOF;
	} else
		return val[sp--];
}

int get_stack_size(void) {
	return sizeof(val) / sizeof(val[0]);
}

int get_element_num_in_stack(void) {
	return sp + 1;
}
