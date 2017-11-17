#include "sort.h"
#include <math.h>

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
	 * TODO: 增量这里放了10个数，如果是非常大的n的话，需要更多的inc空间
	 */
	int inc[] = { 1, 5, 19, 41, 109,
		209, 505, 929, 8929, 2161,
		3905, 8929, 16001, 36289, 64769,
		146305, 260609, 587521, 2354689, 2354689,
	};

#if 0
	/* generate sedgewick增量 */
	for (i = 0; i< 10;i++)
		printf("%d %d %d\n", i, 9*(1<<(2*i)) - 9 * (1<<i) + 1,
				(1<<(2*i)) - 3 * (1<<i) +1);
#endif

#if 0
	for (i = 0; i < sizeof(inc) / sizeof(inc[0]); i++)
		if (inc[i] > n / 2)
			break;
	inc_num = i;
#else
	inc_num = sizeof(inc) / sizeof(inc[0]) - 1;
#endif
#if 0
	dbg("n=%d inc_num=%d\n", n, inc_num);
	dump_array(inc, inc_num+1, "shell_sort3");
#endif
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

#define LeftChild( i )  ( 2 * ( i ) + 1 )
static void perc_down(ElementType *a, int i, int n)
{
	int child;
	ElementType tmp;

	for(tmp = a[i]; LeftChild( i ) < n; i = child ) {
		child = LeftChild( i );

		if( child != n - 1 && a[ child + 1 ] > a[ child ] )
			child++; /* find Larger child */
		if( tmp < a[ child ] )
			a[ i ] = a[ child ];
		else
			break;
	}
	a[ i ] =tmp;
}

void heap_sort(ElementType *a, int n)
{
	int i;

	for( i = n / 2; i >= 0; i-- )  /* Build Max Heap, index from 0 to n-1 */
		perc_down(a, i, n);

	for( i = n - 1; i > 0; i-- ) { /* n-1 次delete操作 */
		swap( &a[ 0 ], &a[ i ] );  /* DeleteMax: a[0] 是最大值，与最后一个元素交换 */
		perc_down( a, 0, i );
	}
}

/**
 * 合并两个已经排序的子数组
 * [l_start_idx : ]   [r_start_idx : r_end_idx]
 */
static void merge(ElementType *a, ElementType *ta,
		int l_start_idx, /* start index of left sub-array */
		int r_start_idx, /* start index of right sub-array */
		int r_end_idx)  /* end index of right sub-array */
{
	int i, l_end_idx, nums, tmp_idx;

	l_end_idx = r_start_idx - 1;
	tmp_idx = l_start_idx;
	nums = r_end_idx - l_start_idx + 1;

	/* main loop */
	while(l_start_idx <= l_end_idx && r_start_idx <= r_end_idx)
		if(a[l_start_idx] <= a[r_start_idx])
			ta[tmp_idx++] = a[l_start_idx++];
		else
			ta[tmp_idx++] = a[r_start_idx++];

	while(l_start_idx <= l_end_idx)  /* Copy rest of left half */
		ta[tmp_idx++] = a[l_start_idx++];
	while(r_start_idx <= r_end_idx) /* Copy rest of right half */
		ta[tmp_idx++] = a[r_start_idx++];

	/* Copy from tmp array back to array */
	for(i = 0; i < nums; i++, r_end_idx--)
		a[r_end_idx] = ta[r_end_idx];
}

static void m_sort(ElementType *a, ElementType *ta, int l_idx, int r_idx )
{
	int m_idx; /* middle index */

	if(l_idx < r_idx) { /* 退出递归条件 */
		m_idx = (l_idx + r_idx) / 2;
		m_sort(a, ta, l_idx, m_idx); /* 递归地排序左半数组 */
		m_sort(a, ta, m_idx + 1, r_idx); /* 递归地排序右半数组 */
		merge(a, ta, l_idx, m_idx + 1, r_idx);
	}
}

void merge_sort(ElementType *a, int n)
{
	ElementType *ta;

	if ((ta = malloc(n * sizeof(ElementType))) != NULL) {
		m_sort(a, ta, 0, n - 1);
		free(ta);
	}
	else
		err("merge sort alloc tmp array fail\n");
}

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

/**
 * 对于小数组(n<20),快速排序不如插入排序好
 * 所以小数组使用插入排序
 */
#define CUTOFF_RANGE 10
static void q_sort(ElementType *a, int l_idx, int r_idx)
{
	int i, j;
	ElementType pivot, tmp;

	if (l_idx + CUTOFF_RANGE <= r_idx) {
		pivot = median3(a, l_idx, r_idx);
		i = l_idx;
		j = r_idx - 1;
		for (;;) {
			/* 根据与pivot的大小关系，把数组中的分成2个集合 */
			while (a[++i] < pivot)
				;
			while (a[--j] > pivot)
				;
			if (i < j) { /* 这里直接交换，没有调用swap方法，速度会更快 */
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			} else
				break;
		}
		swap(&a[i], &a[r_idx - 1]);

		q_sort(a, l_idx, i - 1);
		q_sort(a, i + 1, r_idx);
	} else /* 小数组使用插入排序 */
		insert_sort(a + l_idx, r_idx - l_idx + 1);
}

void quick_sort(ElementType *a, int n)
{
	q_sort(a, 0, n - 1);
}

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
