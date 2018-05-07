#include "ds.h"

int array[] = { 23, 34, 12,
	17, 204, 99, 16
};

#define TOTAL_ELEMENTS (sizeof(array) / sizeof(array[0]))

int main(void)
{
	int d = -1, x = 0;

	if (d <= TOTAL_ELEMENTS - 2)
		x = array[d+1];

	dbg("x=%d\n", x);


	if (-1 < (unsigned char)1)
		dbg("true, ANSI C semantics\n");
	else
		dbg("false, K&R C semantics\n");

	return 0;
}
