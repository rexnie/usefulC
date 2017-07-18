#include <stdio.h>
#include <stdlib.h>

#define IS_LEAP_YEAR(y)		(((y) % 4 == 0) && ((y) % 100 != 0) || ((y) % 400 == 0))

#define LEN_Y   13
static char daytab[2][LEN_Y] = {
	{0,31,28,31,30,31,30,31,31,30,31,30,31},
	{0,31,29,31,30,31,30,31,31,30,31,30,31}
};

int get_array_element(char (*array)[LEN_Y], int x, int y)
{
	return *((char *)(array + x) + y);
}
/**
 * 将某月某日的日期表示形式转换为某年中的第几天形式
 */
int day_of_year(int y, int m, int d) {
	int i, leap;

	if (y < 0) {
		printf("year must be > 0\n");
		goto err;
	}

	if (m < 1 || m > 12) {
		printf("month must be in [1,12]\n");
		goto err;
	}

	leap = IS_LEAP_YEAR(y);
	printf("leap=%d\n", leap);

	if ((d < 0 || d > 31) || (m == 2 && d > get_array_element(daytab, leap, 2))) {
		printf("date must be in [1, 31]\n");
		goto err;
	}

	for (i = 1; i < m; i++)
		d += get_array_element(daytab, leap, i);
	return d;
err:
	return -1;
}

/**
 * 将某年中的第几天形式转换为某月某日的日期表示形式
 */
void month_day(int y, int days, int *pm, int *pd) {
	int i, leap;

	if (y < 0) {
		printf("year must be > 0\n");
		goto err;
	}

	leap = IS_LEAP_YEAR(y);
	printf("leap=%d\n", leap);

	if (days < 0 || days > leap + 365) {
		printf("days must be [1, 366]\n");
		goto err;
	}
	for (i = 1; days > get_array_element(daytab, leap, i); i++)
		days -= get_array_element(daytab, leap, i);

	*pm = i;
	*pd = days;
	return;
err:
	*pm = 0;
	*pd = 0;
}

int main(void) {
	int y, m, d, days;

	//scanf("%d%d%d", &y, &m, &d);
	//printf("day_of_year: %d\n", day_of_year(y, m, d));

	scanf("%d%d", &y, &days);
	month_day(y, days, &m, &d);
	printf("month_day: %d %d\n", m, d);

	return EXIT_SUCCESS;
}
