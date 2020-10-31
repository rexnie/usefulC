#include <stdio.h>
#include <errno.h>

#define __USE_GNU
#include <sched.h>
#include "sched_util.h"

int main(void)
{
	int policy;
	int min, max;
	int pid;

	printf("input pid, 0 is self thread: ");
	scanf("%d", &pid);

	policy = sched_getscheduler(pid);
	if (policy < 0)
		perror("sched_getscheduler return error");
	else
		printf("pid=%d, policy id=%d, name: %s\n", pid, policy, policy_name(policy));

	return 0;
}
