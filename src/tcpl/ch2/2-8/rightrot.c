/*
 * rightrot.c
 *
 *  Created on: Jun 1, 2017
 *      Author: niedaocai
 */

#include <stdio.h>
#include <stdlib.h>

#define TEST    0

unsigned rightrot(unsigned x, int n)
{
	int val_bit0;
	int leading_pos = fast_log2(x);
	const unsigned msb = 1 << leading_pos;
	for (;n > 0; n--) {
		val_bit0 = x & 0x1;
		x /= 2;
		if (val_bit0) {
			x |= msb;
		}
	}
	return x;
}

/**
 * 摘自网络
 * 在x取值范围合理的情况下，是正确的
 * 参数x原为int，调整为unsigned表示的范围更大
 * TODO:原理是什么？？
 */
int fast_log2(unsigned int x)
{
    float fx;
    unsigned long ix, exp;
    fx = (float)x;
    ix = *(unsigned long*)&fx;
    exp = (ix >> 23) & 0xFF;
    return exp - 127;
}

#if TEST
int main(void) {
	unsigned x;
	int n;
	scanf("%d %d", &x, &n);
	printf("%d\n", rightrot(x, n));
    return EXIT_SUCCESS;
}
#endif
