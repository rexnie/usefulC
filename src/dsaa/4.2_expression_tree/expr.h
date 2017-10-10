#ifndef __EXPR_H__
#define __EXPR_H__

#define TYPE_NUM 	1
#define TYPE_OPERATOR   2

#define ASS_LEFT_2_RIGHT 1
#define ASS_RIGHT_2_LEFT 2

#define MAX_STRING_LEN 500
#define MAX_NODES_NUM  100

struct expr_element {
	int type;
	union {
		double operand;
		int operator;
	} value;
};
typedef struct expr_element* pnode_expr;

extern int getop(char **p, char out_str[]);
#endif
