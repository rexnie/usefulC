#ifndef __EXPR_H__
#define __EXPR_H__

#define TYPE_NUM 	1
#define TYPE_OPERATOR   2

#define ASS_LEFT_2_RIGHT 1
#define ASS_RIGHT_2_LEFT 2

extern int getop(char **p, char out_str[]);
#endif
