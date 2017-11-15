#include "ds.h"
#include "sort.h"

/**
 * l_idx, m_idx, r_idx三个位置的值取中位数作为枢纽元pivot
 * pivot先放在r_idx-1的位置，因为r_idx是最大值，应该在右边
 */
static ElementType median3(ElementType *a, int l_idx, int r_idx)
{
	int m_idx = (l_idx + r_idx) / 2;

	if (a[l_idx] > a[m_idx])
		swap(&a[l_idx], &a[m_idx]);
	if (a[l_idx] > a[r_idx])
		swap(&a[l_idx], &a[r_idx]);
	if (a[m_idx] > a[r_idx])
		swap(&a[m_idx], &a[r_idx]);

	/* so after this: a[l_idx] <= a[m_idx] <= a[r_idx] */
	/* a[m_idx] is the pivot, put it to r_idx - 1 */

	swap(&a[m_idx], &a[r_idx - 1]);
	return a[r_idx - 1];
}

#define CUTOFF_RANGE 5
int q_select(ElementType *a, int k_idx, int l_idx, int r_idx)
{
	int i, j;
	ElementType pivot;

	if (l_idx + CUTOFF_RANGE <= r_idx) {
		pivot = median3(a, l_idx, r_idx);
		i = l_idx;
		j = r_idx - 1;

		for (;;) {
			while (a[++i] < pivot)
				;
			while (a[--j] > pivot)
				;
			if (i < j)
				swap(&a[i], &a[j]);
			else
				break;
		}
		swap(&a[i], &a[r_idx - 1]);

		if (k_idx <= i)
			q_select(a, k_idx, l_idx, i - 1);
		else
			q_select(a, k_idx, i + 1, r_idx);
	} else { /* 小数组使用插入排序 */
		insert_sort(a + l_idx, r_idx - l_idx + 1);
		return k_idx + l_idx;
	}
}

/**
 * 在n个数里，求第k小的数，
 * 第1小的就是最小值，第n小的就是最大值
 * 最坏运行时间: O(n^2)
 * 平均运行时间: O(n)
 */
ElementType quick_selection(ElementType *a, int n, int k)
{
	int pos;
	if (k < 1 || k > n) {
		err("k must be [1, %d]\n", n);
		return -1;
	}
	pos = q_select(a, k - 1, 0, n - 1);
	return a[pos];
}

int main(void)
{
	int *ptr;
	int n = 20;
	int min = 1, max = 100;
	int k = 2;

	if ((ptr = get_nums_list_in_range_dereplication(n ,min, max)) != NULL) {
		dump_array(ptr, n, "main");
		dbg("the %dth smallest is: %d\n", k, quick_selection(ptr, n, k));
		/*dump_array(ptr, n, "main2");*/
		free_nums_list(ptr);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
