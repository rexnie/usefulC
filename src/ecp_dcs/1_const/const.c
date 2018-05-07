#include "ds.h"

const char *get_string(void)
{
	return "This is const str";
}

/**
 * get a warning when build:
 * note: expected ‘const char **’ but argument is of type ‘char **’
 */
void foo(const char **p)
{
	p = p;
}

void foo2(const char *p)
{
	p = p;
}

int main(int argc, char **argv)
{
	const int limit = 10;
	int *p = &limit; /* warning: initialization discards ‘const’ qualifier from pointer target type */

	int a = 1;
	const int *limitp = &a;
	int i = 27;

	int b = 100;
	int *const p2 = &b;

	int c = 1000;
	const int *const p3 = &c;

	char *str = "test";
	const char *str2;


	/* error: assignment of read-only variable ‘limit’ */
	/* limit = 1; */

	*p = 11;
	printf("%d\n", limit); /* OK, limit=11 now */

	/* error: assignment of read-only location ‘*limitp’ */
	/* *limitp = 1; */

	a = 2; /* OK */

	printf("limitp %p, %d\n", limitp, *limitp);
	limitp = &i;
	printf("limitp %p, %d\n", limitp, *limitp);

	/* error: assignment of read-only variable ‘p2’ */
	/* p2 = &i; */

	*p2 = 101; /* OK */

	/* error: assignment of read-only variable ‘p3’ */
	/* p3 = &i; */

	/* error: assignment of read-only location ‘*p3’ */
	/* *p3 = 1001; */

	/* warning: assignment discards ‘const’ qualifier from pointer target type  */
	str = get_string(); /* OK, but get a warning*/
	str2 = get_string(); /* OK */
	printf("%s, %s\n", str, str2);

	foo(argv);
	foo2(str);

	return 0;
}
