/*
 * bitcount.c
 *
 *  Created on: Jun 2, 2017
 *      Author: niedaocai
 */

#include <stdio.h>
#include <stdlib.h>

#define TEST    0

int bitcount(unsigned x)
{
	int b;
	for (b = 0; x != 0; x >>= 1)
		if (x & 01)
			b++;
	return b;
}

int bitcount2(unsigned x)
{
	int b = 0;
	while (x) {
		b++;
		x &= (x-1);
	}
	return b;
}
#if TEST
int main(void) {
	unsigned x;
	scanf("%d", &x);
	printf("%d %d", bitcount(x), bitcount2(x));
    return EXIT_SUCCESS;
}
#endif
