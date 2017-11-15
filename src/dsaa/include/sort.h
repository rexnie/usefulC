#ifndef __SORT_H__
#define __SORT_H__
#include "ds.h" /* ElementType = int */

/**
 * 插入排序
 * 最坏运行时间: Theta(n^2)
 * 平均运行时间: Theta(n^2), Theta表示精确的增长率
 * 最好运行时间: O(n)
 */
void insert_sort(ElementType *a, int n);

/**
 * shell 排序算法, 使用Shell增量
 * 最坏运行时间: Theta(n^2)
 * 平均运行时间: Omega(n^2), Omega表示函数的下界
 * 最好运行时间:
 */
void shell_sort(ElementType *a, int n);

/**
 * shell 排序算法, 使用Hibbard增量
 * 最坏运行时间: Theta(n^(3/2))
 * 平均运行时间: O(n^(5/4)),基于模拟的结果，没有人能够证明
 * 最好运行时间:
 */
void shell_sort2(ElementType *a, int n);

/**
 * shell 排序算法, 使用Sedgewick增量
 * 最坏运行时间: Theta(n^(4/3))
 * 平均运行时间: O(n^(7/6)), 猜测的结果
 * 最好运行时间:
 */
void shell_sort3(ElementType *a, int n);

/**
 * heap排序算法
 * 最坏运行时间: O(nlog(n))
 * 平均运行时间:
 * 最好运行时间:
 * 实践中，它慢于使用Sedgewick增量的shell排序
 */
void heap_sort(ElementType *a, int n);

/**
 * 归并(merge)排序算法
 * 最坏运行时间: O(nlog(n))
 * 平均运行时间:
 * 最好运行时间:
 * 它所使用的比较次数几乎是最优的，但是需要n个附加的内存
 */
void merge_sort(ElementType *a, int n);

/**
 * 快速排序算法
 * 最坏运行时间: O(nlog(n))
 * 平均运行时间: O(nlog(n))
 * 最好运行时间:
 */
void quick_sort(ElementType *a, int n);

/**
 * 桶式排序算法
 * 最坏运行时间: O(m+n), m即是桶的个数，max_val的大小
 * 平均运行时间: O(m+n)
 * 最好运行时间:
 * 适用范围: 很多数值很小的非负整数
 * 需要附加的空间，数组中的最大值max_val就是附加空间的大小
 */
void bucket_sort(int *a, int n, int max_val);
#endif
