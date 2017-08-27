#include "binary_search.h"
#include "ds.h"

int binary_search(ET_Search x, const ET_Search v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low < high) {
		mid = (low + high) / 2;
		if (x <= v[mid])
			high = mid;
		else
			low = mid + 1;
	}
	return (x == v[low]) ? low : NotFound;
}
