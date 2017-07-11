/*
 * binsearch.c
 *
 *  Created on: Jun 10, 2017
 *      Author: niedaocai
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef TEST
#define TEST    0
#endif

int binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n -1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

/**
 * 时间可以大大缩小的版本
 * */
int binsearch2(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n -1;
	while (low < high) {
		mid = (low + high) / 2;
		if (x <= v[mid])
			high = mid;
		else
			low = mid + 1;
	}
	return (x == v[low]) ? low : -1;
}

#if TEST
int main(void) {
	int x = 8, n = 10;
	int v[10] = {2, 3, 7, 10, 11, 12, 15, 18, 20, 21};
	int idx = -1;
	clock_t clk_start, clk_end;

	clk_start = clock();
	idx = binsearch(x, v, n);
	clk_end = clock();
	printf("binsearch result: %d, clocks=%lu\n", idx, clk_end - clk_start);

	clk_start = clock();
	idx = binsearch2(x, v, n);
	clk_end = clock();
	printf("binsearch2 result: %d, clocks=%lu\n", idx, clk_end - clk_start);

    return EXIT_SUCCESS;
}
#endif
