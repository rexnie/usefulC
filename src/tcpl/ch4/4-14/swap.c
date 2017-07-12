#include <stdio.h>
#include <stdlib.h>

#define swap(t, x, y) do {\
			t tmp;\
			tmp = (x);\
			(x) = (y);\
			(y) = tmp;\
		} while(0)

//#define swap(t,x,y) {t tmp; tmp = (x); (x) = (y); (y) = tmp;}

int main(void) {
	int a = 3, b = 4;
	char c = 'a', d = 'b';

	swap(int, a, b);
	printf("swap(int, 3, 4)=%d %d\n", a, b);

	swap(char, c, d);
	printf("swap(char, a, b)=%c %c\n", c, d);

	return EXIT_SUCCESS;
}
