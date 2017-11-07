#include "binomial.h"
#include "ds.h"
#include "queue.h" /* ET_Queue = void* */
#include "stack_array.h" /* ET_Stack = void* */

#define MAX_DEPTH 20

typedef struct BinNode *Position;

/* 二项树结构 */
struct BinNode
{
	ET_BQ Element;
	Position    LeftChild;
	Position    NextSibling;
};

struct TmpNode
{
	Position tree;
	int height;
};
typedef struct TmpNode *PTmpNode;

/* 二项队列结构, 表示二项树的集合 */
struct Collection
{
	int CurrentSize; /* 当前节点个数 */
	BinTree TheTrees[ MaxTrees ]; /* 对应高度的二项树 */
				/* 高度为i的二项树的节点数 1<<i */
};

static BinTree BQ_CombineTrees( BinTree T1, BinTree T2 );

BinQueue
BQ_Initialize( void )
{
	BinQueue H;
	int i;

	if((H = malloc( sizeof( struct Collection ) )) == NULL) {
		err( "Initialize: Out of space!!!" );
		return NULL;
	}
	H->CurrentSize = 0;
	for( i = 0; i < MaxTrees; i++ )
		H->TheTrees[ i ] = NULL;
	return H;
}

static BinTree
BQ_AllocBinTreeNode(ET_BQ x)
{
	BinTree NewNode;

	if( (NewNode = malloc( sizeof( struct BinNode ) ) ) == NULL ) {
		err( "alloc BinTree node Out of space!!!" );
		return NULL;
	}
	NewNode->LeftChild = NewNode->NextSibling = NULL;
	NewNode->Element = x;

	return NewNode;
}

static PTmpNode
BQ_AllocTmpNode(ET_BQ x)
{
	BinTree n;
	PTmpNode p;

	if ((n = BQ_AllocBinTreeNode(x)) != NULL) {
		if ((p = malloc(sizeof(struct TmpNode))) != NULL) {
			p->height = 0;
			p->tree = n;
			return p;
		} else {
			err("alloc TmpNode err\n");
			free(n);
		}
	}
	return NULL;
}

int
BQ_BuildBinQueue(ET_BQ *a, int n, BinQueue h)
{
	int i;
	Queue q = NULL;
	ET_BQ odd;
	PTmpNode node = NULL, node2 = NULL, tmp;
	BinTree new;
	int changed; /* 0: not changed, 1: last merged */
	int num = n;

	if ( a == NULL || n <= 0 ) {
		err("build binQueue err: input array invalid\n");
		return -1;
	}

	if (h == NULL) {
		err("bin queue is null\n");
		return -1;
	}

	BQ_MakeEmpty (h);
	if ( n == 1 ) {
		odd = a[0];
		goto alloc_one_node;
	}

	if (n % 2 != 0) {
		odd = a[n - 1];
		num--;
	}

	if ((q = Q_CreateQueue(num)) == NULL) {
		err("build binQueue err: create queue err\n");
		return -1;
	}

	for (i = 0; i < num; i++)
		if ((tmp = BQ_AllocTmpNode(a[i])) == NULL)
			goto err_quit;
		else
			Q_Enqueue((void*) tmp, q);

	tmp = NULL; /* last changed node */
	changed = 1;
	while (Q_GetQueueSize(q) >= 2) {
		if (node == NULL)
			node = (PTmpNode) Q_Dequeue(q);
		if (node2 == NULL)
			node2 = (PTmpNode) Q_Dequeue(q);

		if (node->height == node2->height) { /* merge two and enqueue */
			new = BQ_CombineTrees(node->tree, node2->tree);
			if (new == node->tree) {
				node->height += 1;
				Q_Enqueue((void*) node, q);
				tmp = node;
				free(node2); /* free TmpNode, not BinTree */
			} else {
				node2->height += 1;
				Q_Enqueue((void*) node2, q);
				tmp = node2;
				free(node); /* free TmpNode */
			}
			node = NULL;
			node2 = NULL; /* need pop again */
			changed = 1;
		} else { /* can't merge */
			if (node2 == tmp && changed != 1) { /* queue not changed */
				break;
			}

			Q_Enqueue((void*) node, q);
			node = node2;
			node2 = NULL;
			changed = 0;
		}
	}
	if (node != NULL)
		Q_Enqueue((void*) node, q);
	if (node2 != NULL)
		Q_Enqueue((void*) node2, q);

	while (Q_GetQueueSize(q) >= 1) {
		tmp = (PTmpNode) Q_Dequeue(q);
		h->TheTrees[tmp->height] = tmp->tree;
		free(tmp);
	}

alloc_one_node:
	if (num != n || n == 1) {
		if ((new = BQ_AllocBinTreeNode(odd)) == NULL) {
			err("alloc mem for odd node err\n");
		}
		h->TheTrees[0] = new;
	}
	h->CurrentSize = n;

	if (q != NULL)
		Q_DisposeQueue(q);
	return 0;

err_quit:
	err("alloc nodes err\n");
	while (Q_GetQueueSize(q) > 0) {
		tmp = (PTmpNode) Q_Dequeue(q);
		free(tmp->tree);
		free(tmp);
	}
	return -1;
}

static void
BQ_DestroyTree( BinTree T )
{
	if( T != NULL )
	{
		BQ_DestroyTree( T->LeftChild );
		BQ_DestroyTree( T->NextSibling );
		free( T );
	}
}

static void
BQ_DestroyTrees( BinQueue H )
{
	int i;

	for( i = 0; i < MaxTrees; i++ )
		BQ_DestroyTree( H->TheTrees[ i ] );
}

void
BQ_Destroy( BinQueue H )
{
	BQ_DestroyTrees( H );
	free( H );
	H = NULL;
}

BinQueue
BQ_MakeEmpty( BinQueue H )
{
	int i;

	BQ_DestroyTrees( H );
	for( i = 0; i < MaxTrees; i++ )
		H->TheTrees[ i ] = NULL;
	H->CurrentSize = 0;

	return H;
}

/* Not optimized for O(1) amortized performance */
BinQueue
BQ_Insert( ET_BQ Item, BinQueue H )
{
	BinTree NewNode;
	BinQueue OneItem;

	if ((NewNode = BQ_AllocBinTreeNode(Item)) == NULL) {
		err("Insert err: malloc err\n");
		return NULL;
	}

	OneItem = BQ_Initialize( );
	OneItem->CurrentSize = 1;
	OneItem->TheTrees[ 0 ] = NewNode;

	return BQ_Merge( H, OneItem );
}

ET_BQ
BQ_DeleteMin( BinQueue H )
{
	int i, j;
	int MinTreeHeight;   /* The tree with the minimum item */
	BinQueue DeletedQueue;
	Position DeletedTree, OldRoot;
	ET_BQ MinItem; /* 最小项的值 */

	if( BQ_IsEmpty( H ) )
	{
		err( "Empty binomial queue" );
		return -Infinity;
	}

	MinItem = Infinity;
	for( i = 0; i < MaxTrees; i++ )
	{
		if( H->TheTrees[ i ] &&
				H->TheTrees[ i ]->Element < MinItem )
		{
			/* Update minimum */
			MinItem = H->TheTrees[ i ]->Element;
			MinTreeHeight = i;
		}
	}

	OldRoot = H->TheTrees[ MinTreeHeight ];
	DeletedTree = OldRoot->LeftChild;
	free( OldRoot );

	/* 被删除最小值的二项树，得到一个新的森林, 放入新的二项队列 */
	DeletedQueue = BQ_Initialize( );
	DeletedQueue->CurrentSize = ( 1 << MinTreeHeight ) - 1;
	for( j = MinTreeHeight - 1; j >= 0; j-- ) /* 从最大高度开始插入新的二项队列 */
	{
		DeletedQueue->TheTrees[ j ] = DeletedTree;
		DeletedTree = DeletedTree->NextSibling;
		DeletedQueue->TheTrees[ j ]->NextSibling = NULL;
	}

	H->TheTrees[ MinTreeHeight ] = NULL;
	H->CurrentSize -= DeletedQueue->CurrentSize + 1;

	BQ_Merge( H, DeletedQueue );
	free(DeletedQueue);
	return MinItem;
}

ET_BQ
BQ_FindMin( BinQueue H )
{
	int i;
	ET_BQ MinItem;

	if( BQ_IsEmpty( H ) )
	{
		err( "Empty binomial queue" );
		return 0;
	}

	MinItem = Infinity;
	for( i = 0; i < MaxTrees; i++ )
	{
		if( H->TheTrees[ i ] &&
				H->TheTrees[ i ]->Element < MinItem )
			MinItem = H->TheTrees[ i ]->Element;
	}

	return MinItem;
}

int
BQ_IsEmpty( BinQueue H )
{
	return H->CurrentSize == 0;
}

int
BQ_IsFull( BinQueue H )
{
	return H->CurrentSize == Capacity;
}

/* Return the result of merging equal-sized T1 and T2 */
static BinTree
BQ_CombineTrees( BinTree T1, BinTree T2 )
{
	if( T1->Element > T2->Element )
		return BQ_CombineTrees( T2, T1 );
	T2->NextSibling = T1->LeftChild;
	T1->LeftChild = T2;
	return T1;
}

/* Merge two binomial queues */
/* Not optimized for early termination */
/* H1 contains merged result */
BinQueue
BQ_Merge( BinQueue H1, BinQueue H2 )
{
	BinTree T1, T2, Carry = NULL;
	int i, j;

	if( H1->CurrentSize + H2->CurrentSize > Capacity ) {
		err( "Merge would exceed capacity" );
		return NULL;
	}

	/* 更新新的二项队列的节点个数 */
	H1->CurrentSize += H2->CurrentSize;

	/* j 为新的二项队列的节点个数的总计:
	 * 1 + 2^1 + 2^2 +...
	 * 使用j来控制for循环次数
	 */
	for( i = 0, j = 1; j <= H1->CurrentSize; i++, j *= 2 )
	{
		/**
		 * i 为二项队列的高度迭代变量
		 * T1: 二项队列H1中，高度为i的树的根指针
		 * T2: 二项队列H2中，高度为i的树的根指针
		 */
		T1 = H1->TheTrees[ i ]; T2 = H2->TheTrees[ i ];

		/**
		 * 用3个二进制为表示C/T2/T1是否为空
		 * C表示Carray,从i-1高度来的进位
		 * 000  C/T2/T1都为空
		 * 001  T1不为空
		 * 010  T2不为空
		 * ...
		 * 111  C/T2/T1都不为空
		 */
		switch( !!T1 + 2 * !!T2 + 4 * !!Carry )
		{
			case 0: /* No trees */
			case 1: /* Only H1 */
				break;
			case 2: /* Only H2 */
				H1->TheTrees[ i ] = T2;
				H2->TheTrees[ i ] = NULL;
				break;
			case 4: /* Only Carry */
				H1->TheTrees[ i ] = Carry;
				Carry = NULL;
				break;
			case 3: /* H1 and H2 */
				Carry = BQ_CombineTrees( T1, T2 );
				H1->TheTrees[ i ] = H2->TheTrees[ i ] = NULL;
				break;
			case 5: /* H1 and Carry */
				Carry = BQ_CombineTrees( T1, Carry );
				H1->TheTrees[ i ] = NULL;
				break;
			case 6: /* H2 and Carry */
				Carry = BQ_CombineTrees( T2, Carry );
				H2->TheTrees[ i ] = NULL;
				break;
			case 7: /* All three */
				H1->TheTrees[ i ] = Carry;
				Carry = BQ_CombineTrees( T1, T2 );
				H2->TheTrees[ i ] = NULL;
				break;
		}
	}
	return H1;
}

/**
 * 非递归实现先序遍历树
 */
static void
BQ_PreOrderTravelNonRecursion(Position root)
{
	Stack stack = NULL;
	if ((stack = CreateStack(MAX_DEPTH)) == NULL) {
		err("create stack err\n");
		return;
	}
start:
	while(root != NULL) {
		printf("%d ", root->Element);
		if (root->NextSibling != NULL) {
			Push((void*)root->NextSibling, stack);
		}
		root = root->LeftChild;
	}

	if (!IsStackEmpty(stack)) {
		root = Pop(stack);
		goto start;
	}
	DisposeStack(stack);
}

void
BQ_DumpQueue(BinQueue h, char *tag)
{
	unsigned int i;
	BinTree t = NULL;
	int cnt = 0;

	dbg("DumpQueue called from %s\n", tag);
	printf("CurrentSize=%d\n", h->CurrentSize);

	for (i = 0; cnt < h->CurrentSize; i++) {
		if ((t = h->TheTrees[i]) != NULL) {
			printf("height=%d, tree nodes:\n", i);
			BQ_PreOrderTravelNonRecursion(t);
			printf("\n");
			cnt += 1 << i;
		}
	}
}
