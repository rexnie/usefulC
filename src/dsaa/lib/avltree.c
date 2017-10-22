#include "ds.h"
#include "avltree.h"

struct AvlNode
{
	ET_AvlTree Element;
	AvlTree  Left;
	AvlTree  Right;
	int      Height;
};

AvlTree
AVLT_MakeEmpty( AvlTree T )
{
	if( T != NULL )
	{
		AVLT_MakeEmpty( T->Left );
		AVLT_MakeEmpty( T->Right );
		free( T );
	}
	return NULL;
}

AvlTree
AVLT_Find( ET_AvlTree X, AvlTree T )
{
	if( T == NULL )
		return NULL;
	if( X < T->Element )
		return AVLT_Find( X, T->Left );
	else if( X > T->Element )
		return AVLT_Find( X, T->Right );
	else
		return T;
}

AvlTree
AVLT_FindMin( AvlTree T )
{
	if( T == NULL )
		return NULL;
	else if( T->Left == NULL )
		return T;
	else
		return AVLT_FindMin( T->Left );
}

AvlTree
AVLT_FindMax( AvlTree T )
{
	if( T != NULL )
		while( T->Right != NULL )
			T = T->Right;

	return T;
}

static int
AVLT_Height( AvlTree T )
{
	if( T == NULL )
		return -1;
	else
		return T->Height;
}

/**
 * This function can be called only if K2 has a left child
 * Perform a rotate between a node (K2) and its left child
 * Update heights, then return new root:
 * 其中H(K2->Left) - H(K2->Right) == 2,
 * 所以if Z==NULL，K1->Left==X
 * if Z!=NULL, K1的某个儿子的儿子是X.
 *
 *               K2                  K1
 *               /\                  /\
 *            K1    Z   -->        X    K2
 *            /\                        /\
 *          X    Y                    Y    Z
 */
static AvlTree
AVLT_SingleRotateWithLeft( AvlTree K2 )
{
	AvlTree K1;

	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	K2->Height = Max( AVLT_Height( K2->Left ), AVLT_Height( K2->Right ) ) + 1;
	K1->Height = Max( AVLT_Height( K1->Left ), K2->Height ) + 1;

	return K1;  /* New root */
}

/**
 * This function can be called only if K1 has a right child
 * Perform a rotate between a node (K1) and its right child
 * Update heights, then return new root:
 * 其中H(K1->Right) - H(K1->Left) == 2,
 * 所以if Y==NULL，K2->Right==X
 * if Y!=NULL, K2的某个儿子的儿子是X.
 *
 *               K1                  K2
 *               /\                  /\
 *             Y    K2   -->      K1    X
 *                  /\            /\
 *                Z    X        Y    Z
 */
static AvlTree
AVLT_SingleRotateWithRight( AvlTree K1 )
{
	AvlTree K2;

	K2 = K1->Right;
	K1->Right = K2->Left;
	K2->Left = K1;

	K1->Height = Max( AVLT_Height( K1->Left ), AVLT_Height( K1->Right ) ) + 1;
	K2->Height = Max( AVLT_Height( K2->Right ), K1->Height ) + 1;

	return K2;  /* New root */
}

/**
 * This function can be called only if K3 has a left
 * child and K3's left child has a right child
 * Do the left-right double rotation
 * Update heights, then return new root:
 * 其中H(K3->Left) - H(K3->Right) == 2,
 * 所以if D==NULL，K2==X
 * if D!=NULL, K2的某个儿子的儿子是X.
 *
 *               K3			K3	          K2
 *               /\                     /\                /\
 *            K1    D     -->        K2    D    -->     K1    K3
 *            /\                     /\                 /\    /\
 *          A    K2                K1   C             A   B  C   D
 *               /\                /\
 *             B    C            A    B
 */

static AvlTree
AVLT_DoubleRotateWithLeft( AvlTree K3 )
{
	/* Rotate between K1 and K2 */
	K3->Left = AVLT_SingleRotateWithRight( K3->Left );

	/* Rotate between K3 and K2 */
	return AVLT_SingleRotateWithLeft( K3 );
}

/**
 * This function can be called only if K1 has a right
 * child and K1's right child has a left child
 * Do the right-left double rotation
 * Update heights, then return new root
 * 其中H(K1->Right) - H(K3->Left) == 2,
 * 所以if A==NULL，K2==X
 * if A!=NULL, K2的某个儿子的儿子是X.
 *
 *               K1			K1	              K2
 *               /\                     /\                    /\
 *             A    K3     -->        A    K2    -->       K1    K3
 *                  /\                     /\              /\    /\
 *               K2    D                 B    K3         A   B  C   D
 *               /\                           /\
 *             B    C                       C    D
 *
 */
static AvlTree
AVLT_DoubleRotateWithRight( AvlTree K1 )
{
	/* Rotate between K3 and K2 */
	K1->Right = AVLT_SingleRotateWithLeft( K1->Right );

	/* Rotate between K1 and K2 */
	return AVLT_SingleRotateWithRight( K1 );
}

/**
 * 递归实现
 * 递归地找到合适插入点，找到的插入的位置是个叶子节点，
 * 从该叶子节点递归地向根节点的方向依次更新每个祖先节点的高度，
 * 以及在合适的时候进行旋转
 * 直到回到根节点，然后把该根节点作为这个过程的返回值
 */
AvlTree
AVLT_Insert( ET_AvlTree X, AvlTree T )
{
	if( T == NULL )
	{
		/* Create and return a one-node tree */
		if ((T = malloc( sizeof( struct AvlNode ) )) == NULL)
			err( "Out of space!!!" );
		else
		{
			T->Element = X; T->Height = 0;
			T->Left = T->Right = NULL;
		}
	}
	else if( X < T->Element )
	{
		T->Left = AVLT_Insert( X, T->Left );
		if( AVLT_Height( T->Left ) - AVLT_Height( T->Right ) == 2 )
			if( X < T->Left->Element )
				T = AVLT_SingleRotateWithLeft( T );
			else
				T = AVLT_DoubleRotateWithLeft( T );
	}
	else if( X > T->Element )
	{
		T->Right = AVLT_Insert( X, T->Right );
		if( AVLT_Height( T->Right ) - AVLT_Height( T->Left ) == 2 )
			if( X > T->Right->Element )
				T = AVLT_SingleRotateWithRight( T );
			else
				T = AVLT_DoubleRotateWithRight( T );
	} /* Else X is in the tree already; we'll do nothing */

	T->Height = Max( AVLT_Height( T->Left ), AVLT_Height( T->Right ) ) + 1;
	return T;
}

AvlTree
AVLT_Delete( ET_AvlTree X, AvlTree T )
{
	dbg( "Sorry; Delete is unimplemented; %d remains\n", X );
	return T;
}

ET_AvlTree
AVLT_Retrieve( AvlTree T )
{
	return T->Element;
}

void
AVLT_DumpDetails(AvlTree T)
{
	if (T != NULL) {
		printf("element=%d height=%d,",  T->Element, T->Height);

		if (T->Left != NULL && T->Right != NULL)
			printf("lchild=%d,rchild=%d\n", T->Left->Element, T->Right->Element);
		else if (T->Left != NULL)
			printf("lchild=%d,rchild=NULL\n", T->Left->Element);
		else if (T->Right != NULL)
			printf("lchild=NULL,rchild=%d\n", T->Right->Element);
		else
			printf("no child\n");

		AVLT_DumpDetails(T->Left);
		AVLT_DumpDetails(T->Right);
	}
}
