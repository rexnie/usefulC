#include "ds.h" /* ElementType = int */
#include "binomial.h" /* ET_BQ = int */
#include "binheap.h" /* ET_PQ = int */

#define __DBG 1

/* 使用二叉堆和二项队列分别求第K个最大数，两个算法对比 */

/**
 * n个数里，求第K个最大数
 * 算法6A:
 * 对n个元素建立堆, deleteMin n+1-k次
 * 时间复杂度: O(N+klogN)
 * 返回:
 * PQMinData: 内部错
 * X: 第K个最大数
 */
int get_kTh_max(int *a, int n, int k)
{
	int i;
	int val = PQMinData;
#if __DBG
	char buf[512];
#endif

	PriorityQueue pq = NULL;
	if (k > n || k < 0) {
		err("k must be [1, n]\n");
		return PQMinData;
	}

	if ((pq = PQ_Initialize(n)) == NULL) {
		err("init priority queue err\n");
		return PQMinData;
	}

	if (PQ_BuildHeap2(a, n, pq) < 0) {
		err("build heap err\n");
	}

#if __DBG
	PQ_Dump(pq, "get_kTh_max");
#endif

	for (i = 1; i <= n + 1 - k; i++) {
		val = PQ_DeleteMin(pq);
#if __DBG
		dbg("i=%d, val=%d\n", i, val);
		snprintf(buf, sizeof(buf), "after %s_%d", __func__, i);
		PQ_Dump(pq, buf);
#endif
	}

	PQ_Destroy(pq);

	return val;
}

/**
 * 算法同上，使用二项队列实现
 */
int get_kTh_max2(int *a, int n, int k)
{
	int i;
	int val = -Infinity;
#if __DBG
	char buf[512];
#endif
	BinQueue bq = NULL;

	if (k > n || k < 0) {
		err("k must be [1, n]\n");
		return -Infinity;
	}

	if ((bq = BQ_Initialize()) == NULL) {
		err("init binomial queue err\n");
		return -Infinity;
	}

	if (BQ_BuildBinQueue(a, n, bq) < 0) {
		err("build bin queue err\n");
		return -Infinity;
	}
#if __DBG
	BQ_DumpQueue(bq, "get_kTh_max2");
#endif

#if 1
	for (i = 1; i <= n + 1 - k; i++) {
		val = BQ_DeleteMin(bq);
#if __DBG
		dbg("i=%d, val=%d\n", i, val);
		snprintf(buf, sizeof(buf), "after %s_%d", __func__, i);
		BQ_DumpQueue(bq, buf);
#endif
	}
#endif
	BQ_Destroy(bq);

	return val;
}

int main(void)
{
	int *ptr, i;
	int k = 9;
	int n = 10;
	int min = 1, max = 100;

	if ((ptr = get_nums_list_in_range_dereplication(n ,min, max)) == NULL) {
		err("get num list err\n");
		return EXIT_FAILURE;
	}

	dump_array(ptr, n, "in main");
	if ((i = get_kTh_max(ptr, n, k)) == PQMinData) {
		err("internal err\n");
		free_nums_list(ptr);
		return EXIT_FAILURE;
	}
	dbg("%dth max val = %d\n", k, i);
#if 1
	if ((i = get_kTh_max2(ptr, n, k)) == -Infinity) {
		err("internal err\n");
		free_nums_list(ptr);
		return EXIT_FAILURE;
	}
	dbg("%dth max val = %d\n", k, i);

#endif
	free_nums_list(ptr);
	return EXIT_SUCCESS;
}
