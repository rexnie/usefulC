#include "ds.h"

int binary_search(ElementType x, const ElementType v[], int n)
{
	ElementType low, high, mid;

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
