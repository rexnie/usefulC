#include "ds.h"

int is_sorted(int *a, int n)
{
	int i;

	for (i = 1; i < n && a[i - 1] <= a[i]; i++)
		;
	return i == n ? 1 : 0;
}
