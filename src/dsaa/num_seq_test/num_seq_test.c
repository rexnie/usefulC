#include "ds.h"
#include <limits.h>

static void get_min_max(int *a, int n, int *min, int *max)
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

int main(void)
{
	int *ptr;
	int i, n = 30;
	int min = 1, max = 100;
	int chk_min, chk_max;

	/*if ((ptr = get_nums_list(n)) != NULL) {*/
	/*if ((ptr = get_nums_list_in_range(n ,min, max)) != NULL) {*/
	/*if ((ptr = get_nums_list_sorted(n)) != NULL) {*/
	/*if ((ptr = get_nums_list_in_range_sorted(n ,min, max)) != NULL) {*/
	if ((ptr = get_nums_list_in_range_dereplication(n ,min, max)) != NULL) {
		for (i = 0; i < n; i++)
			printf("%d ", ptr[i]);
		get_min_max(ptr, n, &chk_min, &chk_max);
		printf("\nn=%d, min=%d, max=%d, is_sorted_no_equal=%d\n",n,  chk_min, chk_max,is_sorted_no_equal(ptr, n));
		free_nums_list(ptr);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
