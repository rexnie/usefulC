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

static void Q_DumpInternal( Queue Q, char *tag);

static int Q_Succ( int Value, Queue Q )
{
	if( ++Value == Q->Capacity )
		Value = 0;
	return Value;
}

int Q_IsEmpty( Queue Q )
{
	return Q->Size == 0;
}

int Q_IsFull( Queue Q )
{
	return Q->Size == Q->Capacity;
}

Queue Q_CreateQueue( int MaxElements )
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
	Q_MakeEmpty( Q );

	return Q;
}

void Q_MakeEmpty( Queue Q )
{
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;
}

void Q_DisposeQueue( Queue Q )
{
	if( Q != NULL )
	{
		free( Q->Array );
		free( Q );
	}
}

void Q_Enqueue( ET_Queue X, Queue Q )
{
	if( Q_IsFull( Q ) )
		err( "Full queue\n" );
	else
	{
		Q->Size++;
		Q->Rear = Q_Succ( Q->Rear, Q );
		Q->Array[ Q->Rear ] = X;
	}
}

ET_Queue Q_Front( Queue Q )
{
	if( !Q_IsEmpty( Q ) )
		return Q->Array[ Q->Front ];
	err( "Empty queue\n" );
	return 0;  /* Return value used to avoid warning */
}

ET_Queue Q_Dequeue( Queue Q )
{
	ET_Queue X = 0;

	if( Q_IsEmpty( Q ) )
		err( "Empty queue\n" );
	else
	{
		Q->Size--;
		X = Q->Array[ Q->Front ];
		Q->Front = Q_Succ( Q->Front, Q );
	}
	return X;
}

int Q_GetQueueSize( Queue Q )
{
	return Q->Size;
}

int Q_GetQueueCapacity( Queue Q )
{
	return Q->Capacity;
}

int Q_GetFreeSpace( Queue Q )
{
	return Q->Capacity - Q->Size;
}

static void Q_DumpInternal( Queue Q, char *tag)
{
	dbg("%s call Q_DumpInternal\n", tag);
	printf("size=%d, cap=%d, front=%d, rear=%d\n", Q->Size,
		Q->Capacity, Q->Front, Q->Rear);
}
