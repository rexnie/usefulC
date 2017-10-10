/*
 * stack.h
 *
 *  Created on: Jun 12, 2017
 *      Author: niedaocai
 */
#ifndef __STACK_H
#define __STACK_H 1

typedef double ET_Stack2;
#define MAXVAL	100	/* 栈最大深度 */

int is_stack_empty(void);

int nums_of_stack(void);

void dump_stack(void);

void push_stack(ET_Stack2 v);

ET_Stack2 pop_stack(void);

ET_Stack2 peek_top(void);

void switch_top2(void);

void clear_stack(void);
#endif
