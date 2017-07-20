#include <stdio.h>
#include <stdlib.h>

#include "node.h"

#define MAXWORD 100

int getword(char *word, int lim);

/* 统计单词出现的次数 */
int main(void)
{
	char word[MAXWORD];
	struct tnode *root;

	root = NULL;
	while (getword(word, MAXWORD) != EOF) {
		//printf("%s\n", word);
		if (isalpha(word[0]) || word[0] == '_')
				root = addtree(root, word);
	}

	printtree(root);
	return EXIT_SUCCESS;
}
