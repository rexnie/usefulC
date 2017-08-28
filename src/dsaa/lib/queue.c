#include "queue.h"
#include "ds.h"

#define MinQueueSize ( 5 )

struct QueueRecord
{
	int Capacity;
	int Front;
	int Rear;
	int Size;
	ET_Queue *Array;
};

static int Succ( int Value, Queue Q )
{
	if( ++Value == Q->Capacity )
		Value = 0;
	return Value;
}

int IsEmpty( Queue Q )
{
	return Succ(Q->Rear, Q) == Q->Front ? 1 : 0;
}

int IsFull( Queue Q )
{
	return Q->Size == Q->Capacity;
}

Queue CreateQueue( int MaxElements )
{
	Queue Q;

	if( MaxElements < MinQueueSize )
		MaxElements = MinQueueSize;

	Q = malloc( sizeof( struct QueueRecord ) );
	if( Q == NULL ) {
		err( "Out of space!!!\n" );
		return NULL;
	}

	Q->Array = malloc( sizeof( ET_Queue ) * MaxElements );
	if( Q->Array == NULL ) {
		err( "Out of space!!!\n" );
		free( Q );
		return NULL;
	}
	Q->Capacity = MaxElements;
	MakeEmpty( Q );

	return Q;
}

void MakeEmpty( Queue Q )
{
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;
}

void DisposeQueue( Queue Q )
{
	if( Q != NULL )
	{
		free( Q->Array );
		free( Q );
	}
}

void Enqueue( ET_Queue X, Queue Q )
{
	if( IsFull( Q ) )
		err( "Full queue\n" );
	else
	{
		Q->Size++;
		Q->Rear = Succ( Q->Rear, Q );
		Q->Array[ Q->Rear ] = X;
	}
}

ET_Queue Front( Queue Q )
{
	if( !IsEmpty( Q ) )
		return Q->Array[ Q->Front ];
	err( "Empty queue\n" );
	return 0;  /* Return value used to avoid warning */
}

ET_Queue Dequeue( Queue Q )
{
	ET_Queue X = 0;

	if( IsEmpty( Q ) )
		err( "Empty queue\n" );
	else
	{
		Q->Size--;
		X = Q->Array[ Q->Front ];
		Q->Front = Succ( Q->Front, Q );
	}
	return X;
}
