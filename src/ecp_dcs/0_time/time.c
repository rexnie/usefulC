#include "ds.h"
#include <time.h>
#include <limits.h>

#define ONE_DAY (24 * 60 * 60)
#define TM_FMT "%Y/%m/%d %H:%M:%S"

int main(void)
{
	time_t t1, t2;
	time_t diff;
	double diff_d;
	struct tm *local, *utc;
	char buf[1024];
	char *p;

	t2 = LONG_MAX;
	p = NULL;
	while(p == NULL) {
		t2 -= ONE_DAY;
		p = ctime(&t2);
		dbg("%ld: %s\n", t2, p);
	}

	time(&t1);
	dbg("local time=%s", ctime(&t1));
	dbg("utc time=%s", asctime(gmtime(&t1)));

	diff_d = difftime(t1, t2);
	diff = (time_t) diff_d;
	local = localtime(&diff);
	utc = gmtime(&diff);

	strftime(buf, 1024, TM_FMT, local);
	dbg("diff_d = %f, diff = %ld\n", diff_d, diff);
	dbg("local time = %s", buf);

	strftime(buf, 1024, TM_FMT, utc);
	dbg("utc time = %s", buf);

	return 0;
}
