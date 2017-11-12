#include "sort.h"

void insert_sort(ElementType *a, int n)
{
	int p, j;
	ElementType tmp;

	for (p = 1; p < n; p++) { /* n-1 趟(pass) 插入 */
		tmp = a[p];

		for (j = p - 1; j >= 0 && a[j] > tmp; j--)
			a[j+1] = a[j];

		a[j+1] = tmp;
	}
}

void shell_sort(ElementType *a, int n)
{
	int i, j, increment;
	ElementType tmp;

	/* 逐渐缩小的增量 n/2 n/4 ...2 1, 最后的增量一定是1
	 * 设任意增量为k, 执行插入排序,插入排序的子序列是：
	 * i i-k i-2k i-3k k
	 */
	for (increment = n / 2; increment > 0; increment /= 2)
		for (i = increment; i < n; i++) {
			tmp = a[i];
			for (j = i; j >= increment; j -= increment)
				if (tmp < a[j - increment])
					a[j] = a[j - increment];
				else
					break;
			a[j] = tmp;
		}
}

void shell_sort2(ElementType *a, int n)
{
	int i, j, k;
	ElementType tmp;
	int inc_num;
	int *ptr;
	int increment;
	/* frexp((double) (n / 2 + 1), &inc_num); */  /* 2^inc_num - 1 <= n/2 */
	inc_num = (int) logb((double) (n / 2 + 1)) + 1;

	if ((ptr = malloc(sizeof(int) * inc_num)) == NULL) {
		err("malloc err\n");
		return;
	}

	/* hibbard增量: 1, 3, 7,...2^inc_num -1
	 */
	for (i = 1; i <= inc_num; i++)
		ptr[i-1] = (1 << i) - 1;

	dbg("n=%d inc_num=%d\n", n, inc_num);
	dump_array(ptr, inc_num, "shell_sort2");

	for (i = inc_num - 1; i >= 0; i--) { /* 从最大的增量开始 */
		increment = ptr[i];
		for (j = increment; j < n; j++) {
			tmp = a[j];
			for (k = j; k >= increment; k -= increment)
				if (tmp < a[k - increment])
					a[k] = a[k - increment];
				else
					break;
			a[k] = tmp;
		}
	}
	free(ptr);
}

void shell_sort3(ElementType *a, int n)
{
	int i, j, k;
	ElementType tmp;
	int inc_num;
	int increment;

	/* Sedgewick增量: 1, 5, 19, 41, 109...
	 */
	int inc[] = { 1, 5, 19, 41, 109,
		209, 505, 929, 8929, 2161 };
#if 0
	/* generate sedgewick增量 */
	for (i = 0; i< 10;i++)
		printf("%d %d %d\n", i, 9*(1<<(2*i)) - 9 * (1<<i) + 1,
				(1<<(2*i)) - 3 * (1<<i) +1);
#endif

	for (i = 0; i < sizeof(inc) / sizeof(inc[0]); i++)
		if (inc[i] > n / 2)
			break;
	inc_num = i;

	dbg("n=%d inc_num=%d\n", n, inc_num);
	dump_array(inc, inc_num+1, "shell_sort3");

	for (i = inc_num; i >= 0; i--) { /* 从最大的增量开始 */
		increment = inc[i];
		for (j = increment; j < n; j++) {
			tmp = a[j];
			for (k = j; k >= increment; k -= increment)
				if (tmp < a[k - increment])
					a[k] = a[k - increment];
				else
					break;
			a[k] = tmp;
		}
	}
}