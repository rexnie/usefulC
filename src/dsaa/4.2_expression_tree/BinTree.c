#include "ds.h"
#include "BinTree.h"

struct BinTreeNode {
	ET_BinTree Element;
	BinTree Left;
	BinTree Right;
};

ET_BinTree BinT_Retrieve(BinTree t)
{
	if (t != NULL)
		return t->Element;
	return NULL;
}

BinTree BinT_BuildTree(void *val, BinTree l, BinTree r)
{
	BinTree t;
	if (val == NULL) {
		err("val is null\n");
		return NULL;
	}

	if ((t = (BinTree) malloc(sizeof(struct BinTreeNode))) == NULL) {
		err("alloc mem fail\n");
		return NULL;
	}

	t->Element = val;
	t->Left = l;
	t->Right = r;
	return t;
}

void BinT_TravelPreorder(BinTree root, void (*func)(ET_BinTree))
{
	if (root != NULL) {
		if (func != NULL)
			func(root->Element);
		else
			printf("%ld ", (long) root->Element);
		BinT_TravelPreorder(root->Left, func);
		BinT_TravelPreorder(root->Right, func);
	}
}

void BinT_TravelInorder(BinTree root)
{
}

void BinT_TravelPostorder(BinTree root)
{
}

void BinT_TravelLevelorder(BinTree root)
{
}
