#include "leftheap.h" /* ET_LH == int */
#include "queue.h" /* ET_Queue == void* */
#include "ds.h"

struct TreeNode
{
	ET_LH   Element;
	LeftHeap Left;
	LeftHeap Right;
	int  Npl;
};

static LeftHeap
LH_AllocNode( ET_LH X )
{
	LeftHeap p = NULL;

	if ( ( p = malloc( sizeof( struct TreeNode ) ) ) != NULL ) {
		p->Element = X;
		p->Npl = 0;
		p->Left = p->Right = NULL;
		return p;
	}
	err("alloc node err: no mem\n");
	return NULL;
}

LeftHeap
LH_BuildHeap( ET_LH *a, int n )
{
	int i;
	Queue q;
	LeftHeap node = NULL, node2 = NULL;
	LeftHeap new = NULL;

	if ( a == NULL || n <= 0 ) {
		err("build heap err: input array invalid\n");
		return NULL;
	}

	if ((q = Q_CreateQueue(n)) == NULL) {
		err("build heap err: create queue err\n");
		return NULL;
	}

	for (i = 0; i < n; i++)
		if ((node = LH_AllocNode(a[i])) == NULL)
			goto err_quit;
		else
			Q_Enqueue((void*) node, q);

	while (Q_GetQueueSize(q) >= 2) {
		node = (LeftHeap) Q_Dequeue(q);
		node2 = (LeftHeap) Q_Dequeue(q);
		new = LH_Merge(node, node2);
		Q_Enqueue((void*) new, q);
	}

	new = (LeftHeap) Q_Dequeue(q);

	Q_DisposeQueue(q);
	return new;

err_quit:
	err("alloc node err, i=%d\n", i);
	while (Q_GetQueueSize(q) > 0) {
		node = (LeftHeap) Q_Dequeue(q);
		free(node);
	}
	return NULL;
}

/* swap H->Left and H->Right */
void
LH_SwapChildren( LeftHeap H )
{
	LeftHeap Tmp;

	Tmp = H->Left;
	H->Left = H->Right;
	H->Right = Tmp;
}

/**
 * Merge H1->Right and H2
 */
static LeftHeap
LH_Merge1( LeftHeap H1, LeftHeap H2 )
{
	/**
	 * 因为H1是左式堆,所以H1->Left->Npl >= H1->Right->Npl,
	 * H1->Left==NULL的话，则H2->Right==NULL
	 */
	if( H1->Left == NULL )  /* Single node */
		H1->Left = H2;      /* H1->Right is already NULL,
				       H1->Npl is already 0 */
	else
	{
		H1->Right = LH_Merge( H1->Right, H2 );
		if( H1->Left->Npl < H1->Right->Npl )
			LH_SwapChildren( H1 );

		H1->Npl = H1->Right->Npl + 1;
	}
	return H1;
}

LeftHeap
LH_Merge( LeftHeap H1, LeftHeap H2 )
{
	if( H1 == NULL )
		return H2;
	if( H2 == NULL )
		return H1;

	/* H1 != NULL && H2 != NULL */
	if( H1->Element < H2->Element )
		return LH_Merge1( H1, H2 );
	else
		return LH_Merge1( H2, H1 );
}

LeftHeap
LH_Insert( ET_LH X, LeftHeap H )
{
	LeftHeap SingleNode;

	if ( ( SingleNode = malloc( sizeof( struct TreeNode ) ) ) != NULL ) {
		SingleNode->Element = X;
		SingleNode->Npl = 0;
		SingleNode->Left = SingleNode->Right = NULL;
		H = LH_Merge( SingleNode, H );
		return H;
	}
	err ( "Out of space!!!" );
	return NULL;
}

/* DeleteMin returns the new tree; */
/* To get the minimum, use FindMin */
LeftHeap
LH_DeleteMin( ET_LH *X, LeftHeap H )
{
	LeftHeap LeftHeap, RightHeap;

	if( LH_IsEmpty( H ) )
	{
		err ( "left heap is empty\n" );
		return H;
	}

	LeftHeap = H->Left;
	RightHeap = H->Right;
	if ( X != NULL)
		*X = H->Element;
	free( H );
	return LH_Merge( LeftHeap, RightHeap );
}

ET_LH
LH_FindMin( LeftHeap H )
{
	if( !LH_IsEmpty( H ) )
		return H->Element;
	err ( "Priority Queue is Empty" );
	return LHMinData;
}

int
LH_IsEmpty( LeftHeap H )
{
	return H == NULL;
}

LeftHeap
LH_Destroy( LeftHeap T )
{
	if( T != NULL )
	{
		LH_Destroy ( T->Left );
		LH_Destroy ( T->Right );
		free( T );
	}
	return NULL;
}

static void
LH_DumpDetails( LeftHeap T)
{
	if (T != NULL) {
		printf("%d,Npl=%d,", T->Element, T->Npl);

		if (T->Left != NULL && T->Right != NULL)
			printf("lchild=%d,rchild=%d\n", T->Left->Element, T->Right->Element);
		else if (T->Left != NULL)
			printf("lchild=%d,rchild=NULL\n", T->Left->Element);
		else if (T->Right != NULL)
			printf("lchild=NULL,rchild=%d\n", T->Right->Element);
		else
			printf("no child\n");

		LH_DumpDetails(T->Left);
		LH_DumpDetails(T->Right);
	}
}

void
LH_Dump( LeftHeap H, char *tag )
{
	dbg("########dump Left heap from %s\n", tag);
	LH_DumpDetails(H);
}

