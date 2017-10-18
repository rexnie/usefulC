#include "binary_search.h"
#include "ds.h"

/**
 * 二分查找算法
 * 时间复杂度为 O(logN)
 * 时间可以大大缩小的版本
 * 减少了while 内的判断次数
 */
int binary_search(ET_Search x, const ET_Search v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low < high) {
		mid = (low + high) / 2;
		if (x <= v[mid])
			high = mid;
		else
			low = mid + 1;
	}
	return (x == v[low]) ? low : NotFound;
}
