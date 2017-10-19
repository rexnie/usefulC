#ifndef __NUM_SEQ_H__
#define __NUM_SEQ_H__

/**
 * 生成N个数据的函数库
 */

/**
 * 未指定要生成的数据范围时的默认值，有正负值
 */
#define RAND_MIN_DEFAULT (-RAND_MAX / 2)
#define RAND_MAX_DEFAULT (RAND_MAX / 2)

/**
 * 用于指定生成非负数时的最大值
 */
#define RAND_MAX_POSITIVE (RAND_MAX)

/**
 * 生成一个随机数，[s, e]
 */
int rand_int(int s, int e);

/**
 * 返回nums个未排序的随机数, [RAND_MIN_DEFAULT, RAND_MAX_DEFAULT],
 * 可能有重复数字
 */
int *get_nums_list(int nums);

/**
 * 返回nums个未排序的随机数, [min, max],
 * 设置min=1, max=RAND_MAX, 为自然数的子集
 * 可能有重复数字
 */
int *get_nums_list_in_range(int nums, int min, int max);

/**
 * 返回nums个未排序的随机数, [RAND_MIN_DEFAULT, RAND_MAX_DEFAULT],
 * 没有重复数字
 */
int *get_nums_list_dereplication(int nums);

/**
 * 返回nums个未排序的随机数, [min, max],
 * 设置min=1, max=RAND_MAX, 为自然数的子集
 * 没有重复数字
 */
int *get_nums_list_in_range_dereplication(int nums, int min, int max);

/**
 * 返回nums个按增序排序随机数, [RAND_MIN_DEFAULT, RAND_MAX_DEFAULT],
 * 没有重复数字
 */
int *get_nums_list_sorted(int nums);

/**
 * 返回nums个按增序排序随机数, [min, max],
 * 没有重复数字
 */
int *get_nums_list_in_range_sorted(int nums, int min, int max);

/**
 * 释放get_nums_list_*系列函数分配的内存
 */
void free_nums_list(int *p);
#endif
