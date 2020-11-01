#ifndef SCHED_UTIL_H
#define SCHED_UTIL_H 1

#define __USE_GNU
#include <sched.h>

/* Scheduling algorithms. ref: /usr/include/x86_64-linux-gnu/bits/sched.h */
/*
#define SCHED_OTHER		0
#define SCHED_FIFO		1
#define SCHED_RR		2
#ifdef __USE_GNU
# define SCHED_BATCH		3
# define SCHED_ISO		4
# define SCHED_IDLE		5
# define SCHED_DEADLINE		6

# define SCHED_RESET_ON_FORK	0x40000000
#endif
*/

char *policy_name(int policy)
{
	switch(policy) {
		case SCHED_OTHER:
			return "SCHED_OTHER";
		case SCHED_FIFO:
			return "SCHED_FIFO";
		case SCHED_RR:
			return "SCHED_RR";
		case SCHED_BATCH:
			return "SCHED_BATCH";
		case SCHED_ISO:
			return "SCHED_ISO";
		case SCHED_IDLE:
			return "SCHED_IDLE";
		case SCHED_DEADLINE:
			return "SCHED_DEADLINE";
		default:
			printf("unknown policy: %d\n", policy);
			return "unknown policy";
	}
}

#if 0
//TODO: sched_getattr syscall is not support now, ref
//  https://www.kernel.org/doc/Documentation/scheduler/sched-deadline.txt
//to add the function(sched_getattr) and type(struct sched_attr) manually
//#include <linux/sched/types.h>
void dump_sched_attr(struct sched_attr *attr)
{
	printf("sizeof(struct sched_attr) in userspace: %ld/kernel space:%d\n", sizeof(struct sched_attr), attr->size);
	printf("sched_policy: %d (%s)\n", attr->sched_policy, policy_name(attr->sched_policy));
	printf("sched_flags: %lld\n", attr->sched_flags);
	printf("sched_nice: %d\n", attr->sched_nice);
	printf("sched_priority: %d\n", attr->sched_priority);
	printf("sched_runtime: %lld\n", attr->sched_runtime);
	printf("sched_deadline: %lld\n", attr->sched_deadline);
	printf("sched_period: %lld\n", attr->sched_period);
}
#endif

#endif
