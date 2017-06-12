/*
 * squeeze.c
 *
 *  Created on: May 20, 2017
 *      Author: niedaocai
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEST    0

char* squeeze(char *s1, char *s2) {
	int i, j;
	for(i = j = 0; s1[i] != '\0'; i++) {
		if (strchr(s2, s1[i]) == NULL) { // s1[i] 不在s2中
			s1[j++] = s1[i];
		}
	}

	s1[j] = '\0';
	return s1;
}

#if TEST
int main(void) {
	char s1[200], s2[200];
	scanf("%s %s",s1, s2);
	printf("%s", squeeze(s1,s2));
    return EXIT_SUCCESS;
}
#endif
