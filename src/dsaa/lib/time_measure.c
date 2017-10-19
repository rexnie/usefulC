#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ds.h"

static clock_t clk_start;
static clock_t clk_end;
static struct timespec ts_start;
static struct timespec ts_end;
static tm_t *pmsec;
static int msec_offset;
static int measure_cnt;

enum units {
	NS = 0,
	US = 1,
	MS = 2,
	S  = 3
} result_unit;

char *unit2str()
{
	switch(result_unit) {
		case NS:
			return "ns";
		case US:
			return "us";
		case MS:
			return "ms";
		case S:
			return "s";
		default:
			err("unknown unit\n");
			return "";
	}
}

int prepare_measure(int cnt)
{
	measure_cnt = 0;
	msec_offset = 0;
	if (cnt <= 0) {
		err("measure_cnt must be > 1\n");
		return -1;
	}
	if ((pmsec = (tm_t *) malloc(sizeof(*pmsec) * cnt)) == NULL) {
		err("prepare_measure, no memory\n");
		return -1;
	}
	memset(pmsec, 0, sizeof(*pmsec) * cnt);
	measure_cnt = cnt;
	return 0;
}

void print_ctime(char *tag)
{
	time_t now;

	now = time(NULL);
	dbg("%s=%s", tag, ctime(&now));
}

void start_clock(void)
{
	clk_start = clock();
	result_unit = MS;
	print_ctime("start_time");
}

tm_t end_clock(void)
{
	clock_t clk;
	tm_t msec;

	clk_end = clock();
	clk = clk_end - clk_start;
	msec = (tm_t) (1000L * clk / CLOCKS_PER_SEC);
	/*
	dbg("start=%ld end=%ld diff=%ld msec=%llu\n",
			clk_start, clk_end, clk, msec);
	*/
	if (measure_cnt > 0) {
		if (msec_offset >= measure_cnt) {
			err("out of memory, msec_offset=%d\n", msec_offset);
			return msec;
		}

		*(pmsec + msec_offset) = msec;
		msec_offset ++;
	}
	print_ctime("end_time");
	return msec;
}

void start_clock_ns(void)
{
	if (clock_gettime(CLOCK_REALTIME, &ts_start) < 0) {
		perr("clock_gettime error\n");
		ts_start.tv_sec = ts_start.tv_nsec;
		return;
	}
	result_unit = NS;
}

tm_t end_clock_ns(void)
{
	tm_t msec;
	int ret;

	if ((ret = clock_gettime(CLOCK_REALTIME, &ts_end)) < 0) {
		perr("clock_gettime error\n");
		ts_end.tv_sec = ts_end.tv_nsec;
		return 0;
	}
	msec = (tm_t) ((ts_end.tv_sec - ts_start.tv_sec) * S2NS +
			(ts_end.tv_nsec - ts_start.tv_nsec));
	/*dbg("start.s=%ld-%ld end=%ld-%ld msec=%llu\n",
	  ts_start.tv_sec, ts_start.tv_nsec,
	  ts_end.tv_sec, ts_end.tv_nsec, msec);
	  */
	if (measure_cnt > 0) {
		if (msec_offset >= measure_cnt) {
			err("out of memory, msec_offset=%d\n", msec_offset);
			return msec;
		}

		*(pmsec + msec_offset) = msec;
		msec_offset ++;
	}
	return msec;
}

void finish_and_dump_measure(void)
{
	tm_t min, max, sum;
	tm_t *cur;
	int i;

	printf("\n***** measure result in %s *****\n", unit2str());
	if (msec_offset < measure_cnt)
		err("msec_offset < measure_cnt\n");

	cur = pmsec;
	for (i = 0, sum = 0, min = max = *cur; i < msec_offset; i++, cur++) {
		if (*cur < min)
			min = *cur;
		if (*cur> max)
			max = *cur;
		sum += *cur;
		/*printf("i=%-2d %-llu\n", i, *cur);*/
		printf("%-llu\n", *cur);
	}
	printf("max=%llu,min=%llu,avg=%llu\n", max, min, sum / i);

	free(pmsec);
	msec_offset = 0;
	measure_cnt = 0;
}
