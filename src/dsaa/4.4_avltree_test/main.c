#include "ds.h"
#include "avltree.h"
#include "num_seq.h"

#define N 16

int main(void)
{
	int i;
	AvlTree T = NULL;
	ET_AvlTree nums[N] = { 3, 2, 1, 4, 5,
		6, 7, 16, 15, 14,
		13, 12, 11, 10, 8,
		9,
	};

	for (i = 0; i < N; i++) {
		T = AVLT_Insert(nums[i], T);
		/*AVLT_DumpDetails(T);*/
	}

	AVLT_DumpDetails(T);
	return EXIT_SUCCESS;
}
