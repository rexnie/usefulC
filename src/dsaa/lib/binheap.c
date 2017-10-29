#include "binheap.h"
#include "ds.h"

struct HeapStruct
{
	int Capacity; /* 总容量 */
	int Size; /* 当前的实际大小 */
	ET_PQ *Elements; /* [0] 作为标记, 真实数据从下标1开始 */
};

static void
PQ_PercolateDown( int pos, PriorityQueue H )
{
	int i, Child;
	ET_PQ tmp = H->Elements[pos];

	for( i = pos; i * 2 <= H->Size; i = Child )
	{
		/* Find smaller child */
		Child = i * 2;
		/* Child != H->Size这个判断是以防二叉堆元素个数为偶数时访问数组越界，
		 * 因为Child==Size时，元素i只有一个儿子*/
		if( Child != H->Size && H->Elements[ Child + 1 ]
				< H->Elements[ Child ] )
			Child++;

		/* Percolate one level */
		if( tmp > H->Elements[ Child ] )
			H->Elements[ i ] = H->Elements[ Child ];
		else
			break;
	}
	H->Elements[ i ] = tmp;
}

static void
PQ_PercolateUp( int pos, PriorityQueue H )
{
	int i;
	ET_PQ tmp = H->Elements[pos];

	for( i = pos; H->Elements[ i / 2 ] > tmp; i /= 2 )
		H->Elements[ i ] = H->Elements[ i / 2 ]; /* 空穴上滤 */
	H->Elements[ i ] = tmp;
}

PriorityQueue
PQ_Initialize( int MaxElements )
{
	PriorityQueue H;

	if( MaxElements < PQMinSize )
		MaxElements = PQMinSize;

	H = malloc( sizeof( struct HeapStruct ) );
	if( H == NULL ) {
		err( "alloc HeapStruct out of space!!!" );
		return NULL;
	}

	/* Allocate the array plus one extra for sentinel(标记) */
	H->Elements = malloc( ( MaxElements + 1 )
			* sizeof( ET_PQ ) );
	if( H->Elements == NULL ) {
		err( "alloc Heap element out of space!!!" );
		free(H);
		return NULL;
	}

	H->Capacity = MaxElements;
	H->Size = 0;
	H->Elements[ 0 ] = PQMinData;

	return H;
}

int
PQ_BuildHeap( ET_PQ *a, int N, PriorityQueue H )
{
	int i;

	if ( H == NULL ) {
		err("build heap err: PriorityQueue is null\n");
		return -1;
	}

	if ( a == NULL || N < 0 || N > H->Capacity ) {
		err("build heap err: input array invalid\n");
		return -1;
	}

	PQ_MakeEmpty( H );
	memcpy(&H->Elements[1], a, N * sizeof(ET_PQ));
	H->Size = N;

	for( i = N / 2; i > 0; i-- )
		PQ_PercolateDown( i , H );
	return 0;
}

int
PQ_BuildHeap2( ET_PQ *a, int N, PriorityQueue H )
{
	int i;

	if ( H == NULL ) {
		err("build heap err: PriorityQueue is null\n");
		return -1;
	}

	if ( a == NULL || N < 0 || N > H->Capacity ) {
		err("build heap err: input array invalid\n");
		return -1;
	}

	PQ_MakeEmpty( H );
	for ( i = 0; i < N; i++)
		PQ_Insert( a[i], H );
	return 0;
}

void
PQ_MakeEmpty( PriorityQueue H )
{
	H->Size = 0;
}

/* H->Element[ 0 ] is a sentinel */
void
PQ_Insert( ET_PQ X, PriorityQueue H )
{
	int i;

	if( PQ_IsFull( H ) )
	{
		err( "Priority queue is full" );
		return;
	}

	/* i 从最后一个元素开始 */
	for( i = ++H->Size; H->Elements[ i / 2 ] > X; i /= 2 )
		H->Elements[ i ] = H->Elements[ i / 2 ]; /* 空穴上滤 */
	H->Elements[ i ] = X;
}

ET_PQ
PQ_DeleteMin( PriorityQueue H )
{
	int i, Child;
	ET_PQ MinElement, LastElement;

	if( PQ_IsEmpty( H ) )
	{
		err( "Priority queue is empty" );
		return H->Elements[ 0 ];
	}

	MinElement = H->Elements[ 1 ];
	LastElement = H->Elements[ H->Size-- ];

	for( i = 1; i * 2 <= H->Size; i = Child )
	{
		/* Find smaller child */
		Child = i * 2;
		/* Child != H->Size这个判断是以防二叉堆元素个数为偶数时访问数组越界，
		 * 因为Child==Size时，元素i只有一个儿子*/
		if( Child != H->Size && H->Elements[ Child + 1 ]
				< H->Elements[ Child ] )
			Child++;

		/* Percolate one level */
		if( LastElement > H->Elements[ Child ] )
			H->Elements[ i ] = H->Elements[ Child ];
		else
			break;
	}
	H->Elements[ i ] = LastElement;
	return MinElement;
}

ET_PQ
PQ_FindMin( PriorityQueue H )
{
	if( !IsEmpty( H ) )
		return H->Elements[ 1 ];
	err( "Priority Queue is Empty" );
	return H->Elements[ 0 ];
}

int
PQ_IsEmpty( PriorityQueue H )
{
	return H->Size == 0;
}

int
PQ_IsFull( PriorityQueue H )
{
	return H->Size == H->Capacity;
}

void
PQ_Destroy( PriorityQueue H )
{
	free( H->Elements );
	free( H );
}

/**
 * 根据关键字找在二叉堆中的位置，即数组的下标
 * 返回:
 * NotFound: 没找到
 * index: 关键字key在二叉堆中数组的下标
 */
static int
PQ_FindPos(ET_PQ key, PriorityQueue H)
{
	int i;
	if (H == NULL)
		return NotFound;
	for (i = 1; i <= H->Size && H->Elements[i] != key; i++)
		;
	return i <= H->Size ? i : NotFound;
}

void
PQ_DecreaseKey(int key, int delta, PriorityQueue H)
{
	int pos;
	if ((pos = PQ_FindPos(key, H)) == NotFound) {
		dbg("not found key = %d\n", key);
		return;
	}
	if (delta < 0)
		delta = - delta;
	H->Elements[pos] += delta;
	PQ_PercolateDown(pos, H);
}

void
PQ_IncreaseKey(int key, int delta, PriorityQueue H)
{
	int pos;
	if ((pos = PQ_FindPos(key, H)) == NotFound) {
		dbg("not found key = %d\n", key);
		return;
	}
	if (delta < 0)
		delta = - delta;
	H->Elements[pos] -= delta;
	if (H->Elements[pos] < PQMinData)
		H->Elements[pos] = PQMinData + 1;
	PQ_PercolateUp(pos, H);
}

ET_PQ
PQ_Delete(int key, PriorityQueue H)
{
	int pos;
	if ((pos = PQ_FindPos(key, H)) == NotFound) {
		dbg("not found key = %d\n", key);
		return PQMinData;
	}
	H->Elements[pos] = PQMinData + 1;
	return PQ_DeleteMin(H);
}

void
PQ_Dump( PriorityQueue H, char *tag )
{
	dbg("########dump priority queue from %s\n", tag);
	if (H == NULL)
		printf("priority queue is null\n");
	else {
		int i;
		printf("Size=%d, Capacity=%d\n", H->Size, H->Capacity);
		for (i = 1; i <= H->Size; i++)
			printf("%d ", H->Elements[i]);
		printf("\n");
	}
}
