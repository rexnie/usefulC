#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ds.h"

#define USED 	1
#define UNUSED 	0

#define N 	640000
#define TEST_TIMES 10

/**
 * 生成[i, j]之间的一个随机数
 */
int randInt(unsigned int i, unsigned int j)
{
	if (i >= j) {
		err("i should be < j\n");
		return -1;
	}

	return random() % (j - i + 1) + i;
}

void permutate1(int *array, int n)
{
	int tmp, i, j;

	array[0] = randInt(1, n);
	i = 1;
	while (i < n) { /* 为 array[1,n-1] 生成随机数 */
		tmp = randInt(1, n);
		for (j = 0; j < i && array[j] != tmp; j++)
			;
		if (j == i) /* 之前没有生成过该数，存入 */
			array[i++] = tmp;
	}
}

/**
 * 基本同算法1.
 * 增加一个附加数组，记录之前是否已经填入某数，
 * 生成的随机是[1, n]的范围，那么任意随机数X，
 * ptr[X-1] == USED就记录了随机数X已经填入过了，
 * 避免了查询过程
 */
void permutate2(int *array, int n)
{
	int tmp, i;
	int *ptr;

	if ((ptr = (int *) malloc(sizeof(int) * n)) == NULL) {
		err("malloc error\n");
		return;
	}

	memset(ptr, UNUSED, sizeof(int) * n);
	i = 0;
	while (i < n) { /* 为 array[0,n-1] 生成随机数 */
		tmp = randInt(1, n);
		if (ptr[tmp - 1] == UNUSED) { /* 之前没有生成过该数，存入 */
			array[i++] = tmp;
			ptr[tmp - 1] = USED;
		}
	}
	free(ptr);
}

void swap(int *x, int *y)
{
	int t;
	t = *x;
	*x = *y;
	*y = t;
}

void permutate3(int *array, int n)
{
	int i;

	for (i = 0; i < n; i++)
		array[i] = i + 1;

	for (i = 1; i < n; i++)
		swap(&array[i], &array[randInt(0, i)]);
}

void dump_array(int *a, int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%5d %d\n", i, a[i]);
	printf("\n");
}

/**
 * 检查生成随机置换是否合法，合法的返回0, 否则返回-1
 * 合法必须满足:
 * 1. 数组a[0,n-1]中的随机数应该在[1, n]的范围内,
 * 2. 不出现重复
 * 对于任意随机数X, ptr[X-1] == USED就说明随机数X已经填入过了，
 */
int check_result(int *a, int n)
{
	int *ptr;
	int i, idx;
	int ret;

	if ((ptr = (int *) malloc(sizeof(int) * n)) == NULL) {
		err("malloc error\n");
		return -1;
	}

	memset(ptr, UNUSED, sizeof(int) * n);
	ret = 0;
	for (i = 0; i < n; i++) {
		idx = a[i] - 1;
		if (idx >= 0 && idx < n && ptr[idx] == UNUSED) {
			ptr[idx] = USED; /* 标记a[i]已经出现过了 */
		} else if (idx < 0 || idx >= n) { /* a[i]不在合理范围内 */
			err("pseudo-random num=%d out of range\n", a[i]);
			ret = -1;
			break;
		} else if (ptr[idx] == USED) { /* 随机数a[i]重复出现了 */
			err("pseudo-random num=%d reuse error\n", a[i]);
			ret = -1;
			break;
		}
	}

	if (ret < 0)
		dump_array(a, n);
	free(ptr);
	return ret;
}

int main(void)
{
	int i;
	int buf[N];

	srandom((unsigned int) time(NULL));
	prepare_measure(TEST_TIMES);
	for (i = 0; i < TEST_TIMES; i++) {
		start_clock_ns();
		permutate3(buf, N);
		end_clock_ns();
	}
	finish_and_dump_measure();
	return EXIT_SUCCESS;
}
