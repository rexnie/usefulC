#include "ds.h"
#include "BinTree.h"
#include "stack_array.h"
#include "stack.h"

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

/**
 * 非递归实现二叉树后序遍历1
 * 思路是：
 * 类似中序遍历，先找到沿着树左节点一直深入，并边把沿途的每个节点入栈，
 * 直到某节点为空，然后在弹出栈，这时是节点A第一次在栈顶，是从左子树回来，
 * 不能出栈，因为还需遍历右子树
 * 当右子树遍历完，这时节点A又在栈顶，这是第二次在栈顶，刚从右子树遍历回来，
 * 应该出栈，然后遍历节点A的根节点。
 * 这里每个节点都会有2次出现在栈顶时候，需要有个变量标志是从左子树回来的(不能出栈)，
 * 还是从右子树回来的(出栈，遍历该节点).
 * 传统教科书是对树的节点的指针和flag一起组成一个新的结构，然后新结构入栈。
 * 下面算法是使用2个独立的栈，一个保存树节点的指针，一个保存对应节点的flag,
 * 2个栈保持同时出栈，入栈。
 * 这样的优势是，避免入栈了入栈/出栈时内存的malloc/free,避免内存碎片化，也节省了时间，
 * 从空间占用的角度来说，也没有比传统的方法占用更多的内存
 * 从时间角度来说，入栈/出栈的次数，修改栈顶元素的次数也是一样的
 * 另外，个人觉得这个示例中，使用goto的程序结构比双重while的结构更加清晰，明了
 * 传统方法介绍可参考:
 * http://www.cnblogs.com/dolphin0520/archive/2011/08/25/2153720.html
 */
void BinT_TravelPostorder2(BinTree root, void (*func)(ET_BinTree))
{
	Stack stack = NULL;
	if ((stack = CreateStack(MAX_NODES_NUM)) == NULL) {
		err("CreateStack err\n");
		return;
	}
#define FL_FIRST 1
#define FL_CLR 0

travel_left:
	while (root != NULL) {  /* 一直沿左子树走 */
		Push((void*) root, stack);
		push_stack(FL_FIRST);
		root = root->Left;
	}

pop_stk:
	if (!is_stack_empty()) {
		if (IsStackEmpty(stack)) { /* 2个栈要保持同步 */
			err("two stack should the same size\n");
			DisposeStack(stack);
			return;
		}
		if ((int) peek_top() == FL_FIRST) {
			/* 第一次出现在栈顶，从左子树回来 */
			pop_stack();
			push_stack(FL_CLR);

			root = (BinTree) Top(stack);
			root = root->Right;
			goto travel_left;
		} else {
			/* 第二次出现在栈顶，从右子树回来 */
			pop_stack();
			root = (BinTree) Pop(stack);
			BinT_PrintNode(root, func);
			root = NULL;
			goto pop_stk;
		}
	}

	DisposeStack(stack);
}

/**
 * 非递归实现二叉树后序遍历2
 * 思路是：
 * 由于后序遍历，节点会2次出现在栈顶，原因如上面说明。
 * 该算法的思路是，记录先前遍历的节点,叫前置节点pre，根据pre和当前栈顶
 * 节点的位置关系，来判断是从左子树回来，还是右子树回来，进而避免了flag变量空间的占用.
 * 这样
 */
void BinT_TravelPostorder3(BinTree root, void (*func)(ET_BinTree))
{
	BinTree pre = NULL; /* 前置pre */
	BinTree top = NULL; /* 当前栈顶节点 */
	Stack stack = NULL;
	if ((stack = CreateStack(MAX_NODES_NUM)) == NULL) {
		err("CreateStack err\n");
		return;
	}

travel_left:
	while (root != NULL) {
		if (root->Left == NULL && root->Right == NULL) {
			/**
			 * 叶子节点不需要入栈了，直接遍历,
			 * 这样做的好处是:
			 * 1. 避免了该节点入栈/出栈的时间/空间的消耗
			 * 2. 给pop_stk中的if判断减少了可能性
			 */
			BinT_PrintNode(root, func);
			pre = root; /* 记录遍历中的前置节点 */
			root = NULL; /* root置空，需要弹出栈来决定下一个要遍历的元素 */
		} else {
			Push((void*) root, stack);
			root = root->Left;
		}
	}

pop_stk:
	if (!IsStackEmpty(stack)) {
		top = (BinTree) Top(stack);
		/**
		 * top节点儿子的可能性和pre的关系穷举:
		 * case1: top->Left != NULL && top->Right != NULL
		 * case2: top->Left == NULL && top->Right != NULL
		 * case3: top->Left != NULL && top->Right == NULL
		 *
		 * if (top->Right != NULL): //case 1 or 2
		 * 	if pre != top->Right:
		 * 		// 不是从右子树回来，不出栈
		 * 	else pre == top->Right
		 * 		// 从右子树回来，出栈
		 * else: // case 3
		 * 	if pre == top->Left
		 * 		// 从左子树回来，但没有右儿子，出栈
		 * 	else pre != top->Left
		 * 		// 不是从左子树回来，不出栈
		 */
		if ((top->Right != NULL && pre == top->Right) ||
				(top->Right == NULL && pre == top->Left)) {
			/* 出栈 */
			root = (BinTree) Pop(stack);
			BinT_PrintNode(root, func);
			pre = root;
			goto pop_stk;
		} else {  /* 不出栈 */
			root = top->Right;
			goto travel_left;
		}
	}

	DisposeStack(stack);
}

void BinT_TravelLevelorder(BinTree root, void (*func)(ET_BinTree))
{
}
