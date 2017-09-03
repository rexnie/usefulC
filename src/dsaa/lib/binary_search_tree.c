#include "binary_search_tree.h"
#include "ds.h"

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

	if( T == NULL )
		dbg( "Element not found\n" );
	else if( X < T->Element )  /* Go left */
		T->Left = BST_Delete( X, T->Left );
	else if( X > T->Element )  /* Go right */
		T->Right = BST_Delete( X, T->Right );
	else  /* Found element to be deleted */
		if( T->Left && T->Right ) { /* Two children */
			/* Replace with smallest in right subtree */
			TmpCell = BST_FindMin( T->Right );
			T->Element = TmpCell->Element;
			T->Right = BST_Delete( T->Element, T->Right );
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

void BST_DumpDetails(SearchTree T)
{
	if (T != NULL) {
		printf("%d ", T->Element);

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
