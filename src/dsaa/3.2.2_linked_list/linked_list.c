#include "linked_list.h"

/* Place in the interface file */
struct Node
{
	ElementType Element;
	Position    Next;
};

List MakeEmpty( List L )
{
	if( L != NULL ) {
		DeleteList( L );
		free(L);
	}
	L = malloc( sizeof( struct Node ) );
	if( L == NULL ) {
		err( "Out of memory!" );
		return NULL;
	}
	L->Next = NULL;
	return L;
}

/* Return true if L is empty */
int IsEmpty( List L )
{
	return L->Next == NULL;
}

/* Return true if P is the last position in list L */
/* Parameter L is unused in this implementation */
int IsLast( Position P, List L )
{
	return P->Next == NULL;
}

/* Return Position of X in L; NULL if not found */
Position Find( ElementType X, List L )
{
	Position P;

	P = L->Next;
	while( P != NULL && P->Element != X )
		P = P->Next;

	return P;
}

/* Delete from a list */
/* Cell pointed to by P->Next is wiped out */
/* Assume that the position is legal */
/* Assume use of a header node */
void Delete( ElementType X, List L )
{
	Position P, TmpCell;

	P = FindPrevious( X, L );

	if( !IsLast( P, L ) )  /* Assumption of header use */
	{                      /* X is found; delete it */
		TmpCell = P->Next;
		P->Next = TmpCell->Next;  /* Bypass deleted cell */
		free( TmpCell );
	}
}

/* If X is not found, then Next field of returned value is NULL */
/* Assumes a header */
Position FindPrevious( ElementType X, List L )
{
	Position P;

	P = L;
	while( P->Next != NULL && P->Next->Element != X )
		P = P->Next;

	return P;
}

/* Insert (after legal position P) */
/* Header implementation assumed */
/* Parameter L is unused in this implementation */
void Insert( ElementType X, List L, Position P )
{
	Position TmpCell;

	TmpCell = malloc( sizeof( struct Node ) );
	if( TmpCell == NULL )
		err( "Out of space!!!" );

	TmpCell->Element = X;
	TmpCell->Next = P->Next;
	P->Next = TmpCell;
}

void InsertTail(ElementType X, List L)
{
	Position TmpCell, p;

	TmpCell = malloc( sizeof( struct Node ) );
	if( TmpCell == NULL )
		err( "Out of space!!!" );

	TmpCell->Element = X;
	TmpCell->Next = NULL;

	p = L;
	while (p->Next != NULL)
		p = p->Next;

	p->Next = TmpCell;
}

void DeleteList( List L )
{
	Position P, Tmp;

	P = L->Next;  /* Header assumed */
	L->Next = NULL;
	while( P != NULL )
	{
		Tmp = P->Next;
		free( P );
		P = Tmp;
	}
}

Position Header( List L )
{
	return L;
}

Position First( List L )
{
	return L->Next;
}

Position Advance( Position P )
{
	return P->Next;
}

ElementType Retrieve( Position P )
{
	return P->Element;
}

void PrintList(List L)
{
	Position p;
	int i;

	dbg("**** print list ****\n");
	p = L->Next;
	i = 0;

	while(p != NULL) {
		printf("%d ", p->Element);
		p = p->Next;
		i ++;
	}
	printf("\ntotal %d elements\n", i);
}
