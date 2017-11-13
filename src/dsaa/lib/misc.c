#include "ds.h"

int is_sorted(ElementType *a, int n)
{
	int i;

	for (i = 1; i < n && a[i - 1] <= a[i]; i++)
		;
	return i == n ? 1 : 0;
}

int is_sorted_no_equal(ElementType *a, int n)
{
	int i;

	for (i = 1; i < n && a[i - 1] < a[i]; i++)
		;
	return i == n ? 1 : 0;
}

int index_of_array(ElementType *a, int n, int val)
{
	int i;
	for (i = 0; i < n && a[i] != val; i++)
		;
	return i == n ? NotFound : i;
}

int insert_val(ElementType *a, int n, int val)
{
	int i, idx;

	if ((idx = index_of_array(a, n, val)) != NotFound) {
		err("val=%d exist in array, idx=%d\n", val, idx);
		return -1;
	}

	for (i = n - 1; i >= 0 && a[i] > val; i--)
		a[i+1] = a[i];

	a[i+1] = val;
	return i+1;
}

int delete_val(ElementType *a, int n, int val)
{
	int i, idx;

	if ((idx = index_of_array(a, n, val)) == NotFound) {
		err("val=%d not exist in array\n", val);
		return NotFound;
	}

	for (i = idx; i < n; i++)
		a[i] = a[i+1];

	return idx;
}

int is_array_equal(ElementType *a, ElementType *b, int n)
{
	int i;

	for (i = 0; i < n && a[i] == b[i]; i++)
		;
	return i == n ? 1 : 0;
}

void dump_array(ElementType *a, int n, char *calling)
{
	int i;
	dbg("%s call dump_array:\n", calling);
	for (i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}


void swap(ElementType *x, ElementType *y)
{
	ElementType t;
	t = *x;
	*x = *y;
	*y = t;
}
