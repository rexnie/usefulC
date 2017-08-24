#include "ds.h"

#define EmptyTOS ( -1 )
#define MinStackSize ( 5 )

struct StackRecord
{
	int Capacity;
	int TopOfStack;
	ElementType *Array;
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
		err( "Out of space!!!" );
		return NULL;
	}

	S->Array = malloc( sizeof( ElementType ) * MaxElements );
	if( S->Array == NULL ) {
		err( "Out of space!!!" );
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

void Push( ElementType X, Stack S )
{
	if( IsFull( S ) )
		err( "Full stack" );
	else
		S->Array[ ++S->TopOfStack ] = X;
}


ElementType Top( Stack S )
{
	if( !IsStackEmpty( S ) )
		return S->Array[ S->TopOfStack ];
	err( "Empty stack" );
	return 0;  /* Return value used to avoid warning */
}

ElementType Pop( Stack S )
{
	if( !IsStackEmpty( S ) )
		return S->Array[ S->TopOfStack-- ];
	err( "Empty stack" );
	return 0;  /* Return value used to avoid warning */
}
