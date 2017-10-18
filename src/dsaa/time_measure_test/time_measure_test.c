#include "ds.h"
#include "time_measure.h"

int main(void)
{
	int i, j;
	tm_t b;

	start_clock();
	for (i = 0; i < 1000000; i++)
		for (j = 0; j < 1000000; j++)
			b += i * j;

	dbg("%llu\n", end_clock());
	return 0;
}
