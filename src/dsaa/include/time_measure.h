#ifndef __TIME_MEASURE_H__
#define __TIME_MEASURE_H__
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
 *
 * 3. start_clock()/start_clock_ns()的区别
 * start_clock() 根据进程使用了多少cpu tick统计时间
 * start_clock_ns() 获取硬件RTC统计时间
 * 每个平台的时间精度不一样
 * 在macbook sierra+virtualbox5.1.3+ubuntu 12.04上测试
 * CLOCKS_PER_SEC = 1000000
 * start_clock_ns 的精度是1ns
 * 精确计时使用start_clock_ns()
 * 计算时间长的(>min)使用start_clock()
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
 * 打印当前的时间，格式如:
 * Fri Oct 20 06:48:54 2017
 * tag是个标签，如"start_time"
 */
void print_ctime(char *tag);

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
