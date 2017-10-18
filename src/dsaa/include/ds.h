#ifndef __DS_H__
#define __DS_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define NotFound (-1)

typedef int ElementType;

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
 * misc function
 */
#include "misc.h"

/**
 * Search 算法库
 */

/**
 * 二分查找算法
 */
/*#include "binary_search.h"*/

/**
 * Sort 算法库
 */

/**
 * shell 排序算法
 */
/*#include "shell_sort.h"*/

/**
 * for linked list ADT
 */
/*#include "linked_list.h"*/

/**
 * stack ADT, 数组实现
 */
/*#include "stack_array.h"*/

/**
 * 带写回功能的从标准输入读入字符函数实现
 */
/*#include "getch.h"*/


#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

#define Max(a, b) ((a) > (b) ? (a) : (b))
#define Min(a, b) ((a) < (b) ? (a) : (b))

#endif
