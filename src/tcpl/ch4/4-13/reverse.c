#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void reverse_recursion(char str[], int s, int e) {
	char c;

	if (s < e) {
		c = str[s];
		str[s] = str[e];
		str[e] = c;

		reverse_recursion(str, ++s, --e);
	}
}

/* 反转字符串s */
static void reverse(char str[]) {
	reverse_recursion(str, 0, strlen(str) - 1);
}

int main(void) {
	char str[100];
	scanf("%s", str);
	reverse(str);
	printf("%s\n", str);
	return EXIT_SUCCESS;
}
