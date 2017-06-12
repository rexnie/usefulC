/*
 * lower.c
 *
 *  Created on: Jun 2, 2017
 *      Author: niedaocai
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TEST    0
int lower2(int c)
{
	return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
#if 0
	if (c >= 'A' && c <= 'Z')
		return c + 'a' - 'A';
	else
		return c;
#endif
}
#if TEST
int main(void) {
	char c;
	scanf("%c", &c);
	printf("%c %c", tolower(c), lower2(c));
    return EXIT_SUCCESS;
}
#endif
