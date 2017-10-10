#include "ds.h"
#include "BinTree.h"
#include "stack_array.h"

#define MAX_NODES_NUM  100

struct BinTreeNode {
	ET_BinTree Element;
	BinTree Left;
	BinTree Right;
};

ET_BinTree BinT_Retrieve(BinTree t)
{
	return t != NULL ? t->Element : NULL;
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

void BinT_PrintNode(BinTree root, void (*func)(ET_BinTree))
{
	if (root != NULL)
		if (func != NULL)
			func(root->Element);
		else
			printf("%ld ", (long) root->Element);
}

void BinT_TravelPreorder(BinTree root, void (*func)(ET_BinTree))
{
	if (root != NULL) {
		BinT_PrintNode(root, func);
		BinT_TravelPreorder(root->Left, func);
		BinT_TravelPreorder(root->Right, func);
	}
}

void BinT_TravelPreorder2(BinTree root, void (*func)(ET_BinTree))
{
	Stack stack = NULL;
	if ((stack = CreateStack(MAX_NODES_NUM)) == NULL) {
		err("CreateStack err\n");
		return;
	}

travel_left:
	while (root != NULL) {
		BinT_PrintNode(root, func);
		Push((void*) root, stack);
		root = root->Left;
	}

	if (!IsStackEmpty(stack)) {
		root = Pop(stack);
		root = root->Right;
		goto travel_left;
	}

	DisposeStack(stack);
}

void BinT_TravelInorder(BinTree root, void (*func)(ET_BinTree))
{
	if (root != NULL) {
		BinT_TravelInorder(root->Left, func);
		BinT_PrintNode(root, func);
		BinT_TravelInorder(root->Right, func);
	}
}

void BinT_TravelInorder2(BinTree root, void (*func)(ET_BinTree))
{
	Stack stack = NULL;
	if ((stack = CreateStack(MAX_NODES_NUM)) == NULL) {
		err("CreateStack err\n");
		return;
	}

travel_left:
	while (root != NULL) {
		Push((void*) root, stack);
		root = root->Left;
	}

	if (!IsStackEmpty(stack)) {
		root = Pop(stack);
		BinT_PrintNode(root, func);
		root = root->Right;
		goto travel_left;
	}

	DisposeStack(stack);
}

void BinT_TravelPostorder(BinTree root, void (*func)(ET_BinTree))
{
	if (root != NULL) {
		BinT_TravelPostorder(root->Left, func);
		BinT_TravelPostorder(root->Right, func);
		BinT_PrintNode(root, func);
	}
}

void BinT_TravelPostorder2(BinTree root, void (*func)(ET_BinTree))
{
}

void BinT_TravelLevelorder(BinTree root, void (*func)(ET_BinTree))
{
}
