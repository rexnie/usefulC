#ifndef __DS_H__
#define __DS_H__
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/**
 * debug functions
 */
#undef DEBUG
#define DEBUG
#ifdef DEBUG
#define dbg(fmt, args...) printf("##%s(%d)," fmt, __FILE__, __LINE__, ##args)
#else
#define dbg(fmt, args...)
#endif

#define err(fmt, args...) printf("!!%s(%d)," fmt, __FILE__, __LINE__, ##args)
#define perr(fmt, args...) \
	do { \
		int __err = errno; \
		printf("!!%s(%d),%s" fmt, __FILE__, __LINE__, \
		strerror(__err), ##args); \
	} while(0)

/**
 * 用于测量算法执行时间的工具
 */
#include "time_measure.h"

/**
 * 生成N个数据的函数库
 */
#include "num_seq.h"

/**
 * Search 算法库
 */

#define NotFound (-1)

/**
 * 二分查找算法
 * 时间复杂度为 O(logN)
 * 时间可以大大缩小的版本
 * 减少了while 内的判断次数
 * NotFound 当数组中不存在x
 * 否则返回 在数组中首次出现的下标
 */
#include "binary_search.h"

/**
 * Sort 算法库
 */

/**
 * shell 排序算法
 */
#include "shell_sort.h"

/**
 * misc function
 */

/**
 * 返回1 如果数组是排序的
 * 否则返回0
 */
int is_sorted(int *a, int n);

/**
 * for linked list ADT
 */
#include "linked_list.h"
#endif
