#include "ds.h"
#include <time.h>
#include <limits.h>

time_t get_max_time_t(void)
{
	printf("sizeof(int)=%lu sizeof(long)=%lu sizeof(time_t)=%lu\n", sizeof(int),
		sizeof(long), sizeof(time_t));

	/**
	 * TODO: check time_t data type under new platform
	 * time_t define in /usr/include/time.h
	 * intel i5-5287U iOS10.12
	 *     time_t: long int
	 * VM ubuntu 12.04 64bit
	 *     time_t: long int
	 */
	/* 如果使用LONG_MAX的话，则会导致ctime()函数返回NULL */
	/*return LONG_MAX;*/
	return 0x7fffffff;
}

int main(void)
{
	time_t max, now;
	time_t diff;
	double diff_d;
	struct tm *local, *utc;

	max = get_max_time_t();
	dbg("max=%lx\n", max);
	dbg("max local time=%s", ctime(&max));
	dbg("max utc time=%s", asctime(gmtime(&max)));

	time(&now);
	dbg("now local time=%s", ctime(&now));
	dbg("now utc time=%s", asctime(gmtime(&now)));

	diff_d = difftime(max, now);
	diff = (time_t) diff_d;
	local = localtime(&diff);
	utc = gmtime(&diff);

	dbg("diff_d = %f, diff = %ld\n", diff_d, diff);
	dbg("diff time(local)=%s", asctime(local));
	dbg("diff time(utc)=%s", asctime(utc));

	return 0;
}
