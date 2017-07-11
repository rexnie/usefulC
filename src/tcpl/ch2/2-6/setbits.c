/*
 * setbits.c
 *
 *  Created on: Jun 1, 2017
 *      Author: niedaocai
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef TEST
#define TEST    0
#endif

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	return ((~0 << (p + 1)) & x) // x的高位: x[:p+1]
			| (((1 << (p - n + 1)) - 1) & x ) // x的低位: x[p-n:0]
			| ((y & ((1 << n) - 1)) << (p - n + 1)); // y低n位，左移
}

unsigned getbits(unsigned x, int p, int n)
{
	return (x >> (p + 1 - n)) & ~(~0 << n);
}

#if TEST
int main(void) {
	unsigned x, y;
	int p, n;
	scanf("%d %d %d %d", &x, &p, &n, &y);
	printf("%d\n", setbits(x,p,n,y));
    return EXIT_SUCCESS;
}
#endif
