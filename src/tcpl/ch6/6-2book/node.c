#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

struct tnode *addtree(struct tnode* p, char *w)
{
	int cond;

	if (p == NULL) {
		p = (struct tnode*) malloc(sizeof(struct tnode));
		if (p == NULL) {
			printf("memory alloc for tnode error\n");
			return NULL;
		}
		p->word = strdup(w);
		if (p->word == NULL)
			printf("memory alloc for word error\n");
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0) {
		p->count ++;
	} else if (cond < 0) {
		p->left = addtree(p->left, w);
	} else {
		p->right = addtree(p->right, w);
	}
	return p;
}

void printtree(struct tnode *root)
{
	if (root != NULL) {
		printtree(root->left);
		printf("%4d %s\n", root->count, root->word);
		printtree(root->right);
	}
}
