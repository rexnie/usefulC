#include "ds.h"

int main(void)
{
	List L;

	if ((L = MakeEmpty(NULL)) == NULL) {
		err("MakeEmpty error\n");
		return EXIT_FAILURE;
	}

	InsertTail(1, L);
	InsertTail(2, L);
	InsertTail(3, L);
	InsertTail(4, L);
	PrintList(L);
	Delete(3, L);
	PrintList(L);
	Insert(10, L, Find(2, L));
	PrintList(L);
	DeleteList(L);
	return EXIT_SUCCESS;
}
