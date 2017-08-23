#include "ds.h"

void shell_sort(ElementType *a, int n)
{
	int i, j, increment;
	ElementType tmp;

	for (increment = n / 2; increment > 0; increment /= 2)
		for (i = increment; i < n; i++) {
			tmp = a[i];
			for (j = i; j >= increment; j -= increment)
				if (tmp < a[j - increment])
					a[j] = a[j - increment];
				else
					break;
			a[j] = tmp;
		}
}
