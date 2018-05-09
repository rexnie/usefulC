#include "ds.h"
#include <ctype.h>

#define MAXTOKENS 100
#define MAXTOKENLEN 64

enum type_tag {
	IDENTIFIER,
	QUALIFIER,
	TYPE
};

struct token {
	char type;
	char string[MAXTOKENLEN];
};

int top = -1;
struct token stack[MAXTOKENS];
struct token this;

#define POP stack[top--]
#define PUSH(s) stack[++top] = s

enum type_tag classify_string(void)
{
	char *s = this.string;
	if(!strcmp(s, "const")) {
		strcpy(s, "read-only");
		return QUALIFIER;
	} else if(!strcmp(s, "volatile")) {
		return QUALIFIER;
	} else if(!strcmp(s, "void") ||
			!strcmp(s, "char") ||
			!strcmp(s, "signed") ||
			!strcmp(s, "unsigned") ||
			!strcmp(s, "short") ||
			!strcmp(s, "char") ||
			!strcmp(s, "int") ||
			!strcmp(s, "long") ||
			!strcmp(s, "float") ||
			!strcmp(s, "double") ||
			!strcmp(s, "struct") ||
			!strcmp(s, "union") ||
			!strcmp(s, "enum")) {
		return TYPE;
	}
	return IDENTIFIER;
}

void gettoken(void)
{
	char *p = this.string;

	while((*p = getchar()) == ' ')
		;

	/* 字母和数字作为标识符读入 */
	if(isalnum(*p)) {
		while(isalnum(*++p = getchar()))
			;
		ungetc(*p, stdin);
		*p = '\0';
		this.type = classify_string();
		return;
	}

	if(*p == '*') {
		strcpy(this.string, "pointer to");
		this.type = '*';
		return;
	}

	this.string[1] = '\0';
	this.type = *p;
}

/* 将标记入栈，直到遇到标识符
 * 标识符直接输出
 */
void read_to_first_identifier()
{
	gettoken();
	while(this.type != IDENTIFIER) {
		PUSH(this);
		gettoken();
	}

	printf("%s is ", this.string);
	gettoken();
}

void deal_with_arrays(void)
{
	while(this.type == '[') {
		printf("array ");
		gettoken();
		if(isdigit(this.string[0])) {
			printf("0..%d ", atoi(this.string) - 1);
			gettoken();
		}
		gettoken();
		printf("of ");
	}
}

void deal_with_function_args(void)
{
	while(this.type != ')') {
		gettoken();
	}
	gettoken();
	printf("function returning ");
}

void deal_with_pointers(void)
{
	while(stack[top].type == '*') {
		printf("%s ", POP.string);
	}
}

void deal_with_declarator(void)
{
	switch(this.type) {
		case '[':
			deal_with_arrays();
			break;
		case '(':
			deal_with_function_args();
			break;
	}

	deal_with_pointers();

	while(top >= 0) {
		if(stack[top].type == '(') {
			POP; /* pop '(' */
			gettoken();
			deal_with_declarator();
		} else {
			printf("%s ", POP.string);
		}
	}
}


int main(void)
{
	while(1) {
		read_to_first_identifier();
		deal_with_declarator();
		printf("\n");
	}
	return 0;
}
