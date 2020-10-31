#include <stdio.h>
#include <errno.h>

#define __USE_GNU
#include <sched.h>
#include "sched_util.h"

int main(void)
{
	int pid;
	struct sched_attr attr;

	printf("input pid, 0 is self thread: ");
	scanf("%d", &pid);

	if (sched_getattr(pid, &attr, sizeof(struct sched_attr), 0) < 0) {
		perror("sched_getattr return error");
		return -1;
	}

	printf("pid=%d sched_attr fields are:\n", pid);

	dump_sched_attr(&attr);

	return 0;
}
