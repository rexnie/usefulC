/*
 * invert.c
 *
 *  Created on: Jun 1, 2017
 *      Author: niedaocai
 */

#include <stdio.h>
#include <stdlib.h>

#define TEST    0

unsigned invert(unsigned x, int p, int n)
{
	return ((~0 << (p + 1)) & x) // x的高位: x[:p+1]
			| (((1 << (p - n + 1)) - 1) & x ) // x的低位: x[p-n:0]
			| ((~x) & (((1 << (p + 1)) - 1) - (~(~0 << (p - n + 1)))));/* x中间的位取反:
			算法是:x取反 & 0001111000 */
}

#if TEST
int main(void) {
	unsigned x;
	int p, n;
	scanf("%d %d %d", &x, &p, &n);
	printf("%d\n", invert(x, p, n));
    return EXIT_SUCCESS;
}
#endif
