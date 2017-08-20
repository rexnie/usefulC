#include "ds.h"

/**
 * 桶式排序
 * 输入n个数，a[0], a[1] ... a[n-1]
 * 数值的范围是[0, max_val]
 */
void bucket_sort(int *a, int n, int max_val)
{
	int i, j, k;
	int m; /* 桶的个数 */
	int *ptr; /* 桶，使用heap内存 */

	m = max_val + 1;
	if ((ptr = (int *) malloc(sizeof(int) * m)) == NULL) {
		err("no memory\n");
		return;
	}

	/* 初始化桶元素 */
	for (i = 0; i < m; i++)
		ptr[i] = -1;

	for (i = 0; i < n; i++)
		ptr[a[i]] ++;

#if 0
	for (i = 0; i < m; i++)
		printf("%d: %d\n", i, ptr[i]);
#endif

	k = 0;
	for (i = 0; i < m; i++) {
		for (j = ptr[i]; j >= 0; j--)
			a[k++] = i;
	}

	free(ptr);
}
