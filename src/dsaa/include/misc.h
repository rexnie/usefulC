#ifndef __MISC_H__
#define __MISC_H__
#include "ds.h"

/**
 * 测试数组是否按递增排序
 * a: [in] 被测试数组
 * n: [in] 测试元素个数，一般为数组的元素个数
 * 返回:
 * 1 如果数组是排序的
 * 0 数组不是按递增排序的
 */
int is_sorted(ElementType *a, int n);

/**
 * 测试数组是否按递增排序,和is_sorted的差别在相邻相等的情况处理
 * a: [in] 被测试数组
 * n: [in] 测试元素个数，一般为数组的元素个数
 * 返回:
 * 1 如果数组是排序的
 * 0 数组不是按递增排序的,包括相邻相等的情况
 */
int is_sorted_no_equal(ElementType *a, int n);

/**
 * 返回val在数组中的索引
 * a: [in] 数组
 * n: [in] 数组元素个数
 * val: [in]
 * 返回:
 * x=[0, n) 数组的索引x, a[x] = val
 * NotFound 数组中不存在val的元素
 *
 */
int index_of_array(ElementType *a, int n, int val);

/**
 * 向递增有序的数组中插入val
 * a: [in] 数组
 * n: [in] 数组元素个数
 * val: [in] 要插入的值
 * 返回:
 * x=[0, n) x表示val在数组中的位置, a[x] = val
 * -1 插入失败, val已经存在在数组中了
 */
int insert_val(ElementType *a, int n, int val);

/**
 * 在递增有序的数组中删除val
 * a: [in] 数组
 * n: [in] 数组元素个数
 * val: [in] 要插入的值
 * 返回:
 * x=[0, n) x表示val原来在数组中的位置, a[x] = val
 * NotFound 数组中不存在val
 */
int delete_val(ElementType *a, int n, int val);

/**
 * 测试两个数组中各个元素是否相等
 * a: [in] 数组a
 * b: [in] 数组b
 * n: [in] 数组元素个数
 * 返回:
 * 1: a[i]== b[i], i=[0,n-1]
 * 0: 不相等
 */
int is_array_equal(ElementType *a, ElementType *b, int n);

/**
 * 打印数组的元素
 *
 */
void dump_array(int *ptr, int n, char *calling);

/**
 * 交换x & y的值
 */
void swap(ElementType *x, ElementType *y);
#endif
