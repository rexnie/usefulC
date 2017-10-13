/*
 * main.c
 *
 *  Created on: Jun 12, 2017
 *      Author: niedaocai
 */
#include <math.h>
#include "ds.h"
#include "expr.h"
#include "linked_list.h" /* modify ET_List to void* */
#include "stack_array.h" /* modify ET_Stack to void* */
#include "stack.h" /* modify ET_Stack2 to double */

#define MAXLEN 100

struct expr_element {
	int type;
	union {
		double operand;
		int operator;
	} value;
};

typedef struct expr_element* pnode_expr;

struct precedence_associativity {
	int op; /* 操作符 */
	int pre; /* 优先级,数字越低，优先级越高 */
	int ass; /* 结合性 */
} pre_ass[] = {
	/* 此处优先级和结合性参照book<tcpl> p42 */
	{ '(', 1, ASS_LEFT_2_RIGHT },
	{ ')', 1, ASS_LEFT_2_RIGHT },

	{ '#', 2, ASS_RIGHT_2_LEFT }, /* 负号 */
	{ '$', 2, ASS_RIGHT_2_LEFT }, /* 正号 */

	{ '*', 3, ASS_LEFT_2_RIGHT },
	{ '/', 3, ASS_LEFT_2_RIGHT },
	{ '%', 3, ASS_LEFT_2_RIGHT },

	{ '+', 4, ASS_LEFT_2_RIGHT },
	{ '-', 4, ASS_LEFT_2_RIGHT },
	{ 0, 0, 0 },

};

typedef struct precedence_associativity* ppre_ass;

/**
 * 打印链表结点的回调函数，只有具体的实现才知道如何打印结点
 */
void dump_list_node(ET_List e)
{
	pnode_expr node;

	node = (pnode_expr) e;
	if (node->type == TYPE_NUM)
		printf("%g ", node->value.operand);
	else if (node->type == TYPE_OPERATOR)
		printf("%c ", node->value.operator);
}

/**
 * 打印栈内元素
 */
void dump_stack_element(ET_Stack e)
{
	pnode_expr node;

	node = (pnode_expr) e;
	if (node->type == TYPE_NUM)
		printf("%g ", node->value.operand);
	else if (node->type == TYPE_OPERATOR)
		printf("%c ", node->value.operator);
}

/**
 * 从操作符查找对应的优先级/结合性配置
 */
ppre_ass get_pre_ass(int op)
{
	ppre_ass p = pre_ass;
	while (p->op != 0 && p->op != op)
		p++;
	return p->op == op ? p : NULL;
}

/**
 * 分析中缀表达式，并将它转化为后缀表达式
 * 返回链表，表示后缀表达式的每个结点
 */
List parse_infix_and_2_postfix(char *infix_exp)
{
	int type, pre_ppa;
	char *p;
	char out[MAX_STRING_LEN];
	pnode_expr pnode, top;
	Stack stack_op = NULL;
	ppre_ass ppa, ppa_top;
	List head_postfix = NULL;

	if ((head_postfix = MakeEmpty(NULL)) == NULL) {
		err("MakeEmpty err\n");
		return NULL;
	}

	if ((stack_op = CreateStack(MAX_NODES_NUM)) == NULL) {
		err("CreateStack err\n");
		goto err_quit;
	}

	p = infix_exp;
	while ((type = getop(&p, out)) != '\0') {
		/*dbg("type=%d, out=%s\n", type, out);*/
		switch (type) {
		case TYPE_NUM:
			if ((pnode = malloc(sizeof(struct expr_element))) == NULL) {
				err("malloc err\n");
				goto err_quit;
			}
			pnode->type = TYPE_NUM;
			pnode->value.operand = atof(out);
			InsertTail((ET_List) pnode, head_postfix);
			break;
		case TYPE_OPERATOR:
			switch (out[0]) {
			case ')':
				/* 出栈,直到遇到'(' */
				while (!IsStackEmpty(stack_op)) {
					top = (pnode_expr) Pop(stack_op);
					if (top->value.operator == '(')
						break;
					else
						InsertTail((ET_List) top, head_postfix);
				}
				if (top->value.operator == '(') {
					free(top);
				} else {
					err("'(' and ')' not match\n");
					DumpStack(stack_op, dump_stack_element);
					PrintList(head_postfix, dump_list_node);
					goto err_quit;
				}
				break;
			default:
				/**
				 * 当前操作符的优先级比栈顶的高或者和栈顶的优先级一样，但是结合性是从右到左结合的,进栈
				 * 否则的话，就出栈
				 * 例外，当栈顶是(时,不出栈
				 */
				if ((pnode = malloc(sizeof(struct expr_element))) == NULL) {
					err("malloc err\n");
					goto err_quit;
				}
				pnode->type = TYPE_OPERATOR;
				pnode->value.operator = out[0];

				if (IsStackEmpty(stack_op)) {
					Push(pnode, stack_op);
				} else {
					ppa = get_pre_ass(pnode->value.operator);
					pre_ppa = ppa->pre;
					while (!IsStackEmpty(stack_op)) {
						top = (pnode_expr) Top(stack_op); /* peek stack */
						ppa_top = get_pre_ass(top->value.operator);
						if (ppa_top->op != '(' && ppa_top->pre <= pre_ppa) {
							/* 栈顶节点的操作符的优先级大于等于pre_ppa时，要出栈 */
							top = (pnode_expr) Pop(stack_op);
							InsertTail((ET_List) top, head_postfix);
						} else
							break;
					}
					Push(pnode, stack_op);
				}
				break;
			} /*switch (out[0]) {*/
		break; /* case TYPE_OPERATOR:*/

		default:
			err("unknown type = %d\n", type);
			break;
		}
	}
	while (!IsStackEmpty(stack_op)) {
		InsertTail((ET_List) Pop(stack_op), head_postfix);
	}
	DisposeStack(stack_op);
	return head_postfix;
err_quit:
	DisposeList(head_postfix);
	DisposeStack(stack_op);
	return NULL;
}

/**
 * 求后缀表达式的值
 */
double value_postfix(List L)
{
	Position pos;
	pnode_expr pnode, top;
	int op;
	double result, operand2;

	/**
	 * 由于库libds.a中的栈实现在parse_infix_and_2_postfix函数已经使用，
	 * 使用的是pnode_expr类型，是编译时确定的，所以这里使用另外一个栈实现，
	 * TODO: 是否有办法做到运行时决定栈元素的类型?
	 */

	pos = First(L);
	while (pos != NULL) {
		pnode = (pnode_expr) Retrieve(pos);
		if (pnode->type == TYPE_NUM)
			push_stack(pnode->value.operand);
		else if (pnode->type == TYPE_OPERATOR) {
			op = pnode->value.operator;
			switch (op) {
			case '*':
				push_stack(pop_stack() *  pop_stack());
				break;
			case '/':
				operand2 = pop_stack();
				if (operand2 == 0.0)
					err("divided by zero\n");
				else
					push_stack(pop_stack() / operand2);
				break;
			case '%':
				operand2 = pop_stack();
				if (operand2 == 0.0)
					err("divided by zero\n");
				else
					push_stack(fmod(pop_stack(), operand2));
				break;
			case '+':
				push_stack(pop_stack() + pop_stack());
				break;
			case '-':
				operand2 = pop_stack();
				push_stack(pop_stack() - operand2);
				break;
			case '#': /* 负号，一元运算符 */
				operand2 = pop_stack();
				push_stack( -operand2);
				break;
			case '$': /* 正号，一元运算符 */
				break;
			default:
				err("unkown op = %c\n", op);
				break;
			}
		}
		pos = Advance(pos);
	}

	result = pop_stack();
	if (!is_stack_empty()) {
		err("stack must be empty now\n");
		dump_stack();
	}
	return result;
}

/**
 * 预处理中缀表达式的字符串:
 * 1. 去除空白字符('\t', ' ')
 * 2. 忽略掉'\n'之后的字符
 */
void preprocess_infix_str(char *str)
{
	char *src, *dst;

	src = dst = str;
	while (*src) {
		if (*src == '\n')
			break;
		else if (*src == ' ' || *src == '\t')
			src++;
		else
			*dst++ = *src++;
	}
	*dst = '\0';
}

/* 逆波兰计算器,即求解后缀表达式 */
int main(void) {
	char infix_input[MAX_STRING_LEN] = { 0, };
	List head_postfix = NULL;

	if (fgets(infix_input, MAX_STRING_LEN, stdin) == NULL) {
		err("fgets error\n");
		return EXIT_FAILURE;
	}

	preprocess_infix_str(infix_input);

	dbg("after preprocess:\"%s\"\n", infix_input);

	head_postfix = parse_infix_and_2_postfix(infix_input);

	PrintList(head_postfix, dump_list_node);

	dbg("result = %g\n", value_postfix(head_postfix));

	DisposeList(head_postfix);

	return EXIT_SUCCESS;
}
