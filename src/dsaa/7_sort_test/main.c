#include <math.h>
#include "ds.h"
#include "sort.h"

int main(void)
{
	int *ptr, i;
	int n = 200;
	int min = 0, max = 1000;

	if ((ptr = get_nums_list_in_range_dereplication(n, min, max)) == NULL) {
		err("generate test data err\n");
		return EXIT_FAILURE;
	}

	dump_array(ptr, n, "before sort");

	/*insert_sort(ptr, n);*/
	/*shell_sort(ptr, n);*/
	/*shell_sort2(ptr, n);*/
	/*shell_sort3(ptr, n);*/
	/*heap_sort(ptr, n);*/
	merge_sort(ptr, n);

	dump_array(ptr, n, "after sort");
	dbg("is_sort ret=%d\n", is_sorted_no_equal(ptr, n));

	free_nums_list(ptr);
	return EXIT_SUCCESS;
}
