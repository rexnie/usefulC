/*
 * minprintf.c
 *
 *  Created on: Sep 11, 2016
 *      Author: niedaocai
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "tcpl/minprintf.h"
#define TEST    0

void minprintf(char *fmt, ...) {
	va_list ap; /*指向无名参数*/
	char *p, *sval;
	int ival;
	unsigned int uval;
	double dval;

	va_start(ap, fmt); /*ap 指向第一个无名参数*/
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		switch (*++p) {
		case 'd':
		case 'i':
			ival = va_arg(ap, int);
			printf("%d", ival);
			break;
		case 'o':
			uval = va_arg(ap, unsigned int);
			printf("%o", uval);
			break;
		case 'u':
			uval = va_arg(ap, unsigned int);
			printf("%u", uval);
			break;
		case 'f':
			dval = va_arg(ap, double);
			printf("%f", dval);
			break;
		case 's':
			for (sval = va_arg(ap, char*); *sval; sval++)
				putchar(*sval);
			break;
		default:
			putchar(*p);
			break;
		}
	}
	va_end(ap);
}

#if TEST
int main(void) {
	minprintf(":%u,%o:\n", SHRT_MAX, SHRT_MAX);
	return EXIT_SUCCESS;
}
#endif
