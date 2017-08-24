#ifndef __DS_H__
#define __DS_H__
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define NotFound (-1)

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

/**
 * 二分查找算法
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
#include "misc.h"

/**
 * for linked list ADT
 */
#include "linked_list.h"

/**
 * stack ADT, 数组实现
 */
#include "stack_array.h"

/**
 * 带写回功能的从标准输入读入字符函数实现
 */
#include "getch.h"

#endif
