#ifndef __BINARY_SEARCH_H__
#define __BINARY_SEARCH_H__

typedef int ElementType;

/**
 * 二分查找算法
 * 时间复杂度为 O(logN)
 * 时间可以大大缩小的版本
 * 减少了while 内的判断次数
 * NotFound 当数组中不存在x
 * 否则返回 在数组中首次出现的下标
 */
int binary_search(ElementType x, const ElementType v[], int n);
#endif
