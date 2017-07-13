#include <stdio.h>
#include <stdlib.h>

/**
 * 用指针实现strcat
 */
void strcat_p(char *s, char *t) {
	while (*s)
		s++;

	while (*s++ = *t++)
		;
	*s = '\0';
}

int main(void) {
	char s[500], t[100];

	scanf("%s%s", s, t);
	strcat_p(s, t);
	printf("%s\n", s);
	return EXIT_SUCCESS;
}
