#include "ds.h"
#include <time.h>
#include <limits.h>

#define ONE_DAY (24 * 60 * 60)
#define TM_FMT "%Y/%m/%d %H:%M:%S\n"
#define LINE_MAX 1024

time_t find_max_valid_time(void)
{
	time_t low = 0, high = LONG_MAX;
	time_t mid;
	struct tm* tm_mid;
	char *p;
	char buf[LINE_MAX];

	do {
		mid = (low + high) / 2;
		tm_mid = gmtime(&mid);
		if(tm_mid == NULL) {
			high = mid;
		} else {
			low = mid;
		}

		dbg("mid=%ld, high-low=%ld, tm_mid=%p\n", mid, high - low, tm_mid);
	} while((high - low > 1) || (tm_mid == NULL));

	dbg("mid=%ld, high-low=%ld, tm_mid=%p\n", mid, high - low, tm_mid);

	strftime(buf, LINE_MAX, TM_FMT, tm_mid);
	dbg("max value utc time = %s", buf);

	/* asctime return null, but tm_mid is not null
	 * the max value gmtime & asctime can express is implement-depend
	 * */
	dbg("max value, utc time=%s\n", asctime(tm_mid));
	return mid;
}

int main(void)
{
	time_t t1, t2;
	time_t diff;
	double diff_d;
	struct tm *local, *utc;
	char buf[LINE_MAX];
	char *p;

	dbg("%ld, %ld\n", sizeof(time_t), sizeof(long));

	t2 = find_max_valid_time();

	time(&t1);
	dbg("now local time=%s", ctime(&t1));
	dbg("now utc time=%s", asctime(gmtime(&t1)));

	diff_d = difftime(t2, t1);
	diff = (time_t) diff_d;
	dbg("diff_d = %f, diff = %ld\n", diff_d, diff);

	local = localtime(&diff);
	strftime(buf, LINE_MAX, TM_FMT, local);
	dbg("diff local time = %s", buf);
	utc = gmtime(&diff);

	strftime(buf, LINE_MAX, TM_FMT, utc);
	dbg("diff utc time = %s", buf);

	return 0;
}
