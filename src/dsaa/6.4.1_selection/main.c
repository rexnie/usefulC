#include "ds.h" /* ElementType = int */
#include "binheap.h" /* modify ET_PQ to int */

#define __DBG 0

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
	if (PQ_BuildHeap(a, n, pq) < 0) {
		err("build heap err\n");
	}

#if __DBG
	PQ_Dump(pq, __func__);
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
 * n个数里，求第K个最大数
 * 算法6B:
 * 对n + 1 - k个元素建立堆，然后后面的元素一个个入堆，DeleteMin
 * 适合在n+1-k很大的情况
 * 时间复杂度: O(Nlogk)
 * 返回:
 * PQMinData: 内部错
 * X: 第K个最大数
 */
int get_kTh_max2(int *a, int n, int k)
{
	int i;
	int val = PQMinData;
	int kmin = n + 1 - k;
#if __DBG
	char buf[512];
#endif

	PriorityQueue pq = NULL;
	if (k > n || k < 0) {
		err("k must be [1, n]\n");
		return PQMinData;
	}
	if ((pq = PQ_Initialize(kmin)) == NULL) {
		err("init priority queue err\n");
		return PQMinData;
	}
	if (PQ_BuildHeap(a, kmin, pq) < 0) {
		err("build heap err\n");
	}

#if __DBG
	PQ_Dump(pq, __func__);
#endif

	for (i = kmin; i < n; i++) {
		if (a[i] <= PQ_FindMin(pq))
			val = a[i];
		else {
			PQ_Insert(a[i], pq);
			val = PQ_DeleteMin(pq);
		}
#if __DBG
		dbg("i=%d, val=%d\n", i, val);
		snprintf(buf, sizeof(buf), "after %s_%d", __func__, i);
		PQ_Dump(pq, buf);
#endif
	}

	PQ_Destroy(pq);

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
		return EXIT_FAILURE;
	}
	dbg("%dth max val = %d\n", k, i);

	if ((i = get_kTh_max2(ptr, n, k)) == PQMinData) {
		err("internal err\n");
		return EXIT_FAILURE;
	}
	dbg("%dth max val = %d\n", k, i);

	free_nums_list(ptr);
	return EXIT_SUCCESS;
}
