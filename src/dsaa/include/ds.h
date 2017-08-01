#ifndef __DS_H__
#define __DS_H__
#include <stdio.h>
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
 *
 * 时间测量的用法：
 * 1. 需要测量N次，并统计最大，最小，平均值的情况
 *
 * prepare_measure(N);
 * for (i = 0; i < N; i++) {
 *   start_clock()/start_clock_ns();
 *   your_algorith(...)
 *   end_clock()/end_clock_ns();
 * }
 * finish_and_dump_measure();
 *
 * 2. 只需要测量一次的情况
 *
 * start_clock()/start_clock_ns();
 * your_algorith(...)
 * tm = end_clock()/end_clock_ns();
 * printf("%llu\n", tm);
 */

typedef unsigned long long tm_t;

#define S2NS 1000000000L

/**
 * 统计功能准备:
 * alloc internal memory
 * initial internal structures
 * cnt: 计划测试的次数
 * 返回0成功，-1 失败
 */
int prepare_measure(int cnt);

/**
 * 开始一次测试计时
 * 使用clock()函数实现，精度是0.01sec
 */
void start_clock(void);

/**
 * 结束一次测试计时
 * 返回测试结果，单位ms
 */
tm_t end_clock(void);

/**
 * 开始一次测试计时
 * 使用clock_gettime()函数实现，精度是1nsec
 */
void start_clock_ns(void);

/**
 * 结束一次测试计时
 * 返回测试结果，单位ns
 */
tm_t end_clock_ns(void);

/**
 * 输出统计结果，释放内部资源
 * 结果的单位可能是ms/ns, 取决于一次测试的API
 */
void finish_and_dump_measure(void);

#endif
