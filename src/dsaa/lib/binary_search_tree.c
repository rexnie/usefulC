#include "ds.h"
#include "binary_search_tree.h"
#include "stack_array.h" /* modify ET_Stack to void* */
#include "stack.h" /* modify ET_Stack2 to double */

#define MAX_NODES_NUM  251000

struct TreeNode
{
	ET_STree Element;
	SearchTree  Left;
	SearchTree  Right;
};

SearchTree BST_MakeEmpty( SearchTree T )
{
	if( T != NULL )
	{
		BST_MakeEmpty( T->Left );
		BST_MakeEmpty( T->Right );
		free( T );
	}
	return NULL;
}

Position BST_Find( ET_STree X, SearchTree T )
{
	if( T == NULL )
		return NULL;
	if( X < T->Element )
		return BST_Find( X, T->Left );
	else if( X > T->Element )
		return BST_Find( X, T->Right );
	else
		return T;
}

/**
 * 使用递归实现，这是典型的尾递归，应该避免
 */
Position BST_FindMin( SearchTree T )
{
	if( T == NULL )
		return NULL;
	else if( T->Left == NULL ) /*此为一个退出条件，不能少*/
		return T;
	else
		return BST_FindMin( T->Left );
}

/**
 * 非递归实现
 */
Position BST_FindMax( SearchTree T )
{
	if( T != NULL )
		while( T->Right != NULL )
			T = T->Right;

	return T;
}

static Position BST_FindMin2(Position *parent, SearchTree T)
{
	*parent = T;
	if (T != NULL)
		while (T->Left != NULL) {
			*parent = T;
			T = T->Left;
		}
	return T;
}

static Position BST_FindMax2( Position *parent, SearchTree T )
{
	*parent = T;
	if( T != NULL )
		while( T->Right != NULL ) {
			*parent = T;
			T = T->Right;
		}

	return T;
}
SearchTree BST_Insert( ET_STree X, SearchTree T )
{
	if( T == NULL )
	{
		/* Create and return a one-node tree */
		T = malloc( sizeof( struct TreeNode ) );
		if( T == NULL )
			err( "Out of space!!!\n" ); /* quit Insert() */
		else
		{
			T->Element = X;
			T->Left = T->Right = NULL;
		}
	}
	else if( X < T->Element )
		T->Left = BST_Insert( X, T->Left );
	else if( X > T->Element )
		T->Right = BST_Insert( X, T->Right );
	/* Else X is in the tree already; we'll do nothing */

	return T;  /* Do not forget this line!! */
}

SearchTree BST_Delete( ET_STree X, SearchTree T )
{
	Position TmpCell;
	static int last_delete_flag = 0; /*在删除有两个儿子的节点时,
				0: 删除右子树最小值，1:删除左子树最大值 */
	Position Parent;

	if( T == NULL )
		;/*dbg( "delete X=%d not found\n", X );*/
	else if( X < T->Element )  /* Go left */
		T->Left = BST_Delete( X, T->Left );
	else if( X > T->Element )  /* Go right */
		T->Right = BST_Delete( X, T->Right );
	else  /* Found element to be deleted */
		if( T->Left && T->Right ) { /* Two children */
			/* 轮流使左子树最大值/右子树最小值上升一层，而不是一直上升右子树最小值，
			 * 在一定程度避免出现不平衡
			 */
			if (!last_delete_flag) { /* 右子树最小值上升 */
				last_delete_flag = 1;
				TmpCell = BST_FindMin2(&Parent, T->Right );
				dbg("up right:T=%d,Parent=%d\n", T->Element, Parent->Element);
				T->Element = TmpCell->Element;
				if (T->Right == Parent) /* 可能删除parent自身,所以根从T->Right开始 */
					T->Right = BST_Delete(TmpCell->Element, T->Right);
				else if (Parent->Left == TmpCell)
					Parent->Left = BST_Delete( TmpCell->Element, Parent->Left);
				else
					Parent->Right = BST_Delete( TmpCell->Element, Parent->Right);
			} else if (last_delete_flag == 1) { /* 左子树最大值上升 */
				last_delete_flag = 0;
				TmpCell = BST_FindMax2(&Parent, T->Left );
				dbg("up left:T=%d,Parent=%d\n", T->Element, Parent->Element);
				T->Element = TmpCell->Element;
				if (T->Left == Parent) /* 可能删除parent自身,所以根从T->Left开始 */
					T->Left = BST_Delete( TmpCell->Element, T->Left);
				else if (Parent->Left == TmpCell)
					Parent->Left = BST_Delete( TmpCell->Element, Parent->Left);
				else
					Parent->Right = BST_Delete( TmpCell->Element, Parent->Right);
			}
		}
		else { /* One or zero children */
			TmpCell = T;
			if( T->Left == NULL ) /* Also handles 0 children */
				T = T->Right;
			else if( T->Right == NULL )
				T = T->Left;
			free( TmpCell );
		}

	return T;
}

ET_STree BST_Retrieve( Position P )
{
	return P->Element;
}

void BST_PrintTreeInorder(SearchTree T)
{
	if (T != NULL) {
		BST_PrintTreeInorder(T->Left);
		printf("%d ", T->Element);
		BST_PrintTreeInorder(T->Right);
	}
}

void BST_TravelInorder(SearchTree root, ET_STree *outbuf)
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
		root = (SearchTree) Pop(stack);
		if (outbuf != NULL) {
			*outbuf++ = root->Element;
		}
		root = root->Right;
		goto travel_left;
	}

	DisposeStack(stack);
}

/**
 * 使用二叉树后序遍历的一个算法来做，详细可看4.2_expression_tree/BinTree.c中
 * 的BinT_TravelPostorder2函数
 */
int BST_Height(SearchTree root)
{
	int height = -1, i;
	Stack stack = NULL;
	if ((stack = CreateStack(MAX_NODES_NUM)) == NULL) {
		err("CreateStack err\n");
		return -2;
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
			return -2;
		}
		if ((int) peek_top() == FL_FIRST) {
			/* 第一次出现在栈顶，从左子树回来 */
			pop_stack();
			push_stack(FL_CLR);

			root = (SearchTree) Top(stack);
			root = root->Right;
			goto travel_left;
		} else {
			/* 第二次出现在栈顶，从右子树回来 */
			i = NumOfElement(stack);
			if (i > height)
				height = i;
			pop_stack();
			root = (SearchTree) Pop(stack);
			root = NULL;
			goto pop_stk;
		}
	}

	DisposeStack(stack);
	return height;
}

int BST_HeightRootLeft(SearchTree T)
{
	return BST_Height(T->Left);
}

int BST_HeightRootRight(SearchTree T)
{
	return BST_Height(T->Right);
}

void BST_DumpDetails(SearchTree T)
{
	if (T != NULL) {
#if 1
		int lh, rh;
		lh = BST_Height(T->Left);
		rh = BST_Height(T->Right);
		printf("%d lheight=%d, rheight=%d,", T->Element, lh, rh);
#else
		printf("%d,", T->Element);
#endif

		if (T->Left != NULL && T->Right != NULL)
			printf("lchild=%d,rchild=%d\n", T->Left->Element, T->Right->Element);
		else if (T->Left != NULL)
			printf("lchild=%d,rchild=NULL\n", T->Left->Element);
		else if (T->Right != NULL)
			printf("lchild=NULL,rchild=%d\n", T->Right->Element);
		else
			printf("no child\n");

		BST_DumpDetails(T->Left);
		BST_DumpDetails(T->Right);
	}
}
