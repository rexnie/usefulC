/*
 * any.c
 *
 *  Created on: May 26, 2017
 *      Author: niedaocai
 */

#include <stdio.h>
#include <stdlib.h>

#define TEST    0

int any(char *s1,char *s2)
{
	int i, j;
	for (i = 0; s1[i] != '\0'; i++) {
		for (j = 0; s2[j] != '\0'; j++) {
			if (s2[j] == s1[i])
				return i;
		}
	}
	return -1;
}

#if TEST
int main(void) {
	char s1[1024],s2[1024];
	memset((void *)s1, 0, sizeof(s1));
	memset((void *)s2, 0, sizeof(s1));

	scanf("%s %s",s1, s2);
	printf("%d\n",any(s1,s2));

    return EXIT_SUCCESS;
}
#endif
