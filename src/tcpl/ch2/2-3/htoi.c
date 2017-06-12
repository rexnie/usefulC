/*
 * htoi_.c
 *
 *  Created on: May 20, 2017
 *      Author: niedaocai
 */

#include <stdio.h>
#include <stdlib.h>

#define TEST	0
#define BASE	16

int htoi(char *hex_str) {
	int sum = 0;
	char *p = hex_str;

	if ((*p == '0') && ((*(p + 1) == 'x') || (*(p + 1) == 'X'))) {
		p += 2;
	}

	while (*p != '\0') {
		if (*p >= '0' && *p <= '9') {
			sum = sum * BASE + *p - '0';
			p++;
		} else if (*p >= 'A' && *p <= 'F') {
			sum = sum * BASE + *p - 'A' + 10;
			p++;
		} else if (*p >= 'a' && *p <= 'f') {
			sum = sum * BASE + *p - 'a' + 10;
			p++;
		} else {
			printf("input error, must be [0-9,a-f,A-F],%c\n", *p);
			return 0;
		}
	}
	return sum;
}

#if TEST
int main(void) {
	char hex_str[1024];
	memset(hex_str, 0, sizeof(hex_str));

	scanf("%s", hex_str);
	printf("\"%s\" len=%d,int=%d\n",hex_str,strlen(hex_str),htoi(hex_str));
	return EXIT_SUCCESS;
}
#endif
