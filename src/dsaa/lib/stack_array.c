#include "ds.h"
#include "stack_array.h"

#define EmptyTOS ( -1 )
#define MinStackSize ( 5 )

struct StackRecord
{
	int Capacity;
	int TopOfStack;
	ET_Stack *Array;
};

int IsStackEmpty( Stack S )
{
	return S->TopOfStack == EmptyTOS;
}

int IsFull( Stack S )
{
	return S->TopOfStack == S->Capacity - 1;
}

Stack CreateStack( int MaxElements )
{
	Stack S;

	if( MaxElements < MinStackSize )
		MaxElements = MinStackSize;

	S = malloc( sizeof( struct StackRecord ) );
	if( S == NULL ) {
		err( "Out of space!!!\n" );
		return NULL;
	}

	S->Array = malloc( sizeof( ET_Stack ) * MaxElements );
	if( S->Array == NULL ) {
		err( "Out of space!!!\n" );
		free(S);
		return NULL;
	}
	S->Capacity = MaxElements;
	MakeStackEmpty( S );

	return S;
}

void MakeStackEmpty( Stack S )
{
	S->TopOfStack = EmptyTOS;
}

void DisposeStack( Stack S )
{
	if( S != NULL )
	{
		free( S->Array );
		free( S );
	}
}

void Push( ET_Stack X, Stack S )
{
	if( IsFull( S ) )
		err( "Full stack\n" );
	else
		S->Array[ ++S->TopOfStack ] = X;
}


ET_Stack Top( Stack S )
{
	if( !IsStackEmpty( S ) )
		return S->Array[ S->TopOfStack ];
	err( "Empty stack\n" );
	return 0;  /* Return value used to avoid warning */
}

ET_Stack Pop( Stack S )
{
	if( !IsStackEmpty( S ) )
		return S->Array[ S->TopOfStack-- ];
	err( "Empty stack\n" );
	return 0;  /* Return value used to avoid warning */
}

void DumpStack( Stack S, void (*func)(ET_Stack))
{
	int i;

	dbg("\n---TopOfStack=%d\n", S->TopOfStack);
	for (i = 0; i <= S->TopOfStack; i++)
		if (func != NULL)
			func(S->Array[i]);
		else
			printf("%d ", S->Array[i]);
	dbg("\ntotal %d elements in stack\n", i);
}
