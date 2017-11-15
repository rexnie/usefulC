#include <math.h>
#include "ds.h"
#include "sort.h"

int main(void)
{
	int *ptr, i, j;
	int n;
	int is_sorted;
	int test_times = 10;
#if 1
	int min = RAND_MIN_DEFAULT, max = RAND_MAX_DEFAULT;
#else
	int min = 1, max = 20;
#endif

	int case_nums = 1;
	int test_cases[] = { 10, 100, 1000, 10000, 100000, 1000000 };

	i = 0;
	while (i < case_nums) {
		n = test_cases[i];
		prepare_measure(test_times);
		for (j = 0; j < test_times; j++) {
			if ((ptr = get_nums_list_in_range_dereplication(n, min, max)) == NULL) {
				err("generate test data err\n");
				return EXIT_FAILURE;
			}

			/*dump_array(ptr, n, "before sort");*/

			start_clock_ns();
			/*insert_sort(ptr, n);*/
			/*shell_sort(ptr, n);*/
			/*shell_sort2(ptr, n);*/
			/*shell_sort3(ptr, n);*/
			/*heap_sort(ptr, n);*/
			/*merge_sort(ptr, n);*/
			quick_sort(ptr, n);
			/*bucket_sort(ptr, n, max);*/
			end_clock_ns();

			/*dump_array(ptr, n, "after sort");*/
			is_sorted = is_sorted_no_equal(ptr, n);
			if (!is_sorted) {
				dbg("not sorted\n");
				dump_array(ptr, n, "after sort");
				free_nums_list(ptr);
				return EXIT_FAILURE;
			}

			free_nums_list(ptr);
		}
		finish_and_dump_measure();
		dbg("test case end, index = %d, n = %d\n", i, n);
		i++;
	}
	return EXIT_SUCCESS;
}
