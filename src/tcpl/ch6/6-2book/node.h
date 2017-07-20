#ifndef __NODE_H__
#define __NODE_H__

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *addtree(struct tnode* p, char *w);
void printtree(struct tnode *root);
#endif
