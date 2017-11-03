#include "ds.h" /* ElementType = int */
#include "leftheap.h" /* ET_LH = int */
#include "binheap.h" /* ET_PQ = int */

#define __DBG 1

/* 使用二叉堆和左式堆分别求第K个最大数，两个算法对比 */

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
 * 算法同上，使用左式堆实现
 */
int get_kTh_max2(int *a, int n, int k)
{
	int i;
	int val = LHMinData;
#if __DBG
	char buf[512];
#endif

	LeftHeap lh = NULL;
	if (k > n || k < 0) {
		err("k must be [1, n]\n");
		return LHMinData;
	}

	if ((lh = LH_BuildHeap(a, n)) == NULL) {
		err("build heap err\n");
		return LHMinData;
	}

#if __DBG
	LH_Dump(lh, "get_kTh_max2");
#endif

	for (i = 1; i <= n + 1 - k; i++) {
		lh = LH_DeleteMin(&val, lh);
#if __DBG
		dbg("i=%d, val=%d\n", i, val);
		snprintf(buf, sizeof(buf), "after %s_%d", __func__, i);
		LH_Dump(lh, buf);
#endif
	}

	LH_Destroy(lh);

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

	if ((i = get_kTh_max2(ptr, n, k)) == LHMinData) {
		err("internal err\n");
		return EXIT_FAILURE;
	}
	dbg("%dth max val = %d\n", k, i);

	free_nums_list(ptr);
	return EXIT_SUCCESS;
}
