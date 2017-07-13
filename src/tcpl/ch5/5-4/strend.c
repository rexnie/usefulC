#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 如果字符串t出现在字符串s的尾部，返回1
 * 否则返回0
 */
int strend(char *s, char *t) {
	char *t_end, *s_end;

	s_end = strlen(s) - 1 + s;
	t_end = strlen(t) - 1 + t;

	while (t_end > t && *s_end == *t_end) { /*从后往前比较, n-1,n-2,...,1 */
		s_end--;
		t_end--;
	}

	return (t_end == t && *s_end == *t_end) ? 1 : 0; /*比较第0个*/
}

int main(void) {
	char s[500], t[100];

	scanf("%s%s", s, t);
	printf("%d\n", strend(s, t));
	return EXIT_SUCCESS;
}
