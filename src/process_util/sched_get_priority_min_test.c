#include <stdio.h>
#include <errno.h>

#define __USE_GNU
#include <sched.h>
#include "sched_util.h"

int main(void)
{
	int policy;
	int min, max;

	for (policy = SCHED_OTHER; policy <= SCHED_DEADLINE; policy++) {
		errno = 0;
		min = sched_get_priority_min(policy);
		if (errno != 0)
			perror("sched_get_priority_min return error");

		errno = 0;
		max = sched_get_priority_max(policy);
		if (errno != 0)
			perror("sched_get_priority_max return error");

		printf("policy name: %s, priority min: %d, max: %d\n", policy_name(policy),
			min, max);
	}

	return 0;
}
