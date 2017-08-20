#include "ds.h"

int main(void)
{
	int *ptr, i;
	int n = 300;
	int min = 0, max = 1000;

	void bucket_sort(int *a, int n, int max_val);
	if ((ptr = get_nums_list_in_range(n, min, max)) != NULL) {
		for (i = 0; i < n; i++)
			printf("%d ", ptr[i]);
		printf("\n");

		bucket_sort(ptr, n, max);

		for (i = 0; i < n; i++)
			printf("%d ", ptr[i]);
		printf("\nis_sorted=%d\n", is_sorted(ptr, n));
		free_nums_list(ptr);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
