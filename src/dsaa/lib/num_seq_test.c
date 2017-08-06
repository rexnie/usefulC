#include "ds.h"
#include <limits.h>

void get_min_max(int *a, int n, int *min, int *max)
{
	int i;

	*min = INT_MAX; *max = INT_MIN;
	for (i = 0; i < n; i++) {
		if (*min > a[i])
			*min = a[i];
		if (*max < a[i])
			*max = a[i];
	}
}

int is_sorted(int *a, int n)
{
	int i;

	for (i = 1; i < n && a[i - 1] < a[i]; i++)
		;
	return i == n ? 1 : 0;
}

int main(void)
{
	int *ptr;
	int i, n = 15;
	int min = 1, max = 100;
	int chk_min, chk_max;

	/*if ((ptr = get_nums_list(n)) != NULL) {*/
	/*if ((ptr = get_nums_list_in_range(n ,min, max)) != NULL) {*/
	/*if ((ptr = get_nums_list_sorted(n)) != NULL) {*/
	if ((ptr = get_nums_list_in_range_sorted(n ,min, max)) != NULL) {
		for (i = 0; i < n; i++)
			printf("%d ", ptr[i]);
		get_min_max(ptr, n, &chk_min, &chk_max);
		printf("\nmin=%d, max=%d, is_sorted=%d\n", chk_min, chk_max, is_sorted(ptr, n));
		free_nums_list(ptr);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

