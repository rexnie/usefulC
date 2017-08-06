#include <stdlib.h>
#include "ds.h"

static int rand_int(int s, int e)
{
	return random() % (e - s + 1) + s;
}

static int *check_parameters_and_alloc_momory(int nums, int min, int max)
{
	int *ptr;

	if (nums < 1) {
		err("nums must >=1\n");
		return NULL;
	}
	if (min >= max) {
		err("min value must be smaller than max\n");
		return NULL;
	}

	if ((ptr = (int *) malloc(sizeof(int) * nums)) == NULL) {
		err("malloc error\n");
		return NULL;
	}

	return ptr;
}

int *get_nums_list(int nums)
{
	return get_nums_list_in_range(nums, RAND_MIN_DEFAULT, RAND_MAX_DEFAULT);
}

int *get_nums_list_in_range(int nums, int min, int max)
{
	int i;
	int *ptr, *p;

	if ((ptr = check_parameters_and_alloc_momory(nums, min, max)) != NULL) {
		srandom((unsigned int) time(NULL));
		for (i = 0, p = ptr; i < nums; i++, p++)
			*p = rand_int(min, max);
	}
	return ptr;
}

/**
 * 把val插入已经排序的数组中
 * 返回1: 插入成功
 *     0: a中已经存在val，未插入
 */
int find_and_insert(int *a, int n, int val)
{
	int i;
	int idx;

	if ((idx = binary_search(val, a, n)) < 0) { /* not find it */
		for (i = n - 1; i >= 0 && a[i] > val; i--)
			a[i+1] = a[i];
		a[i+1] = val;
		return 1;
	}
	return 0;
}

int *get_nums_list_sorted(int nums)
{
	return get_nums_list_in_range_sorted(nums,RAND_MIN_DEFAULT, RAND_MAX_DEFAULT);
}

int *get_nums_list_in_range_sorted(int nums, int min, int max)
{
	int i;
	int tmp;
	int *ptr;

	if ((ptr = check_parameters_and_alloc_momory(nums, min, max)) != NULL) {
		srandom((unsigned int) time(NULL));
		ptr[0] = rand_int(min, max);
		for (i = 0; i < nums;) {
			tmp = rand_int(min, max);
			if (find_and_insert(ptr, i+1, tmp) == 1)
				i++;
		}
	}
	return ptr;
}

void free_nums_list(int *p)
{
	if (p != NULL)
		free(p);
}
