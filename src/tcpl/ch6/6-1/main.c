#include <stdio.h>
#include <stdlib.h>
#include "keytab.h"

#define MAXWORD 100

int binsearch(char *word, struct key tab[], int n);
int getword(char *word, int lim);

struct key keytab[] = {
	{ "_abc", 0 }, /*这不是关键字，测试_开头标志符用*/
	{ "asm", 0 },
	{ "auto", 0 },
	{ "break", 0 },
	{ "case", 0 },
	{ "char", 0 },
	{ "const", 0 },
	{ "continue", 0 },
	{ "default", 0 },
	{ "do", 0 },
	{ "double", 0 },
	{ "else", 0 },
	{ "enum", 0 },
	{ "extern", 0 },
	{ "float", 0 },
	{ "for", 0 },
	{ "goto", 0 },
	{ "if", 0 },
	{ "int", 0 },
	{ "long", 0 },
	{ "register", 0 },
	{ "return", 0 },
	{ "short", 0 },
	{ "signed", 0 },
	{ "sizeof", 0 },
	{ "static", 0 },
	{ "struct", 0 },
	{ "switch", 0 },
	{ "typedef", 0 },
	{ "union", 0 },
	{ "unsigned", 0 },
	{ "void", 0 },
	{ "volatile", 0 },
	{ "while", 0 },

};

#define NKEYS  (sizeof(keytab) / sizeof(keytab[0]))

int main(void)
{
	int n;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF)
	{
		printf("%s\n", word);
		if ((isalpha(word[0]) || word[0] == '_') &&
				(n = binsearch(word, keytab, NKEYS)) >= 0)
			keytab[n].count++;
	}

	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
	return EXIT_SUCCESS;
}
