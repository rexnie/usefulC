#include "binary_search_tree.h"
#include "ds.h"

#define N 20

static SearchTree AutoCreateTree( int n, int min, int max, SearchTree T )
{
	ET_STree *ptr;
	int i;
	if ((ptr = get_nums_list_in_range(n, min, max)) != NULL) {
		for (i = 0; i < n; i++)
			printf("%d ", ptr[i]);
		printf("\n");
		for (i = 0; i < n; i++)
			T = BST_Insert(ptr[i], T);
		free(ptr);
	}
	return T;
}

int main(void)
{
	int i;
	SearchTree T = NULL;
	Position pos = NULL;
	ET_STree nums[N] = { 50, 73, 36, 86, 40,
		10, 64, 75, 26, 34,
		18, 44, 41, 57, 89,
		58, 98, 3, 4, 2,
	};

	/*
	T = AutoCreateTree(N, 0, 100, T);
	BST_DumpDetails(T);
	*/

	for (i = 0; i < N; i++)
		T = BST_Insert(nums[i], T);

	BST_DumpDetails(T);

	pos = BST_Find(1, T);
	dbg("%d\n", pos != NULL ? BST_Retrieve(pos) : -1);

	pos = BST_FindMin(T);
	dbg("%d\n", BST_Retrieve(pos));

	pos = BST_FindMax(T);
	dbg("%d\n", BST_Retrieve(pos));

	pos = BST_Insert(37,T);
	dbg("%d\n", BST_Retrieve(pos));

	BST_DumpDetails(T);

	pos = BST_Delete(73,T);
	dbg("%d\n", BST_Retrieve(pos));

	BST_DumpDetails(T);
	BST_PrintTreeInorder(T);
	return EXIT_SUCCESS;
}
