#include "ds.h"

int check1(int *a, int n)
{
	int i;

	for (i = 0; i < n && a[i] != i; i++)
		;
	return i < n && a[i] == i ? i : NotFound;
}

int check2(int *a, int n)
{
	int i;

	for (i = 0; i < n;) {
		if (a[i] > i)
			i += a[i] - i;
		else if (a[i] == i)
			return i;
		else
			i++;
	}
	return NotFound;
}
int main(void)
{
	int *ptr;
	int i, n = 100;
	int min = 0, max = 150;
	int times = 10, j;

	do {
		times--;
		if ((ptr = get_nums_list_in_range_sorted(n, min, max)) != NULL) {
			for (i = 0; i < n; i++)
				printf("%d ", ptr[i]);
			printf("\ncheck1 ret=%d\n", check1(ptr, n));
			printf("check2 ret=%d\n", check2(ptr, n));
			free_nums_list(ptr);
			/*return EXIT_SUCCESS;*/
		}
	} while (times > 0);
	return EXIT_FAILURE;
}

