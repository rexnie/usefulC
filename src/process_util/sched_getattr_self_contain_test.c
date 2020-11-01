 /**
  * this demo show how to use sched_getattr get process info.
  * some system do not support sched_getattr/setattr() yet.
  * i get this code from Documentation/scheduler/sched-deadline.txt
  * run with root user
  *
  * We provide in what follows a simple (ugly) self-contained code snippet
  * showing how SCHED_DEADLINE reservations can be created by a real-time
  * application developer.
  */

 #define _GNU_SOURCE
 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <time.h>
 #include <linux/unistd.h>
 #include <linux/kernel.h>
 #include <linux/types.h>
 #include <sys/syscall.h>
#include <sched.h>

 #define gettid() syscall(__NR_gettid)

 #define SCHED_DEADLINE	6

 /* XXX use the proper syscall numbers */
 #ifdef __x86_64__
 #define __NR_sched_setattr		314
 #define __NR_sched_getattr		315
 #endif

 #ifdef __i386__
 #define __NR_sched_setattr		351
 #define __NR_sched_getattr		352
 #endif

 #ifdef __arm__
 #define __NR_sched_setattr		380
 #define __NR_sched_getattr		381
 #endif

 struct sched_attr {
	__u32 size;

	__u32 sched_policy;
	__u64 sched_flags;

	/* SCHED_NORMAL, SCHED_BATCH */
	__s32 sched_nice;

	/* SCHED_FIFO, SCHED_RR */
	__u32 sched_priority;

	/* SCHED_DEADLINE (nsec) */
	__u64 sched_runtime;
	__u64 sched_deadline;
	__u64 sched_period;
 };

 int sched_setattr(pid_t pid,
		  const struct sched_attr *attr,
		  unsigned int flags)
 {
	return syscall(__NR_sched_setattr, pid, attr, flags);
 }

 int sched_getattr(pid_t pid,
		  struct sched_attr *attr,
		  unsigned int size,
		  unsigned int flags)
 {
	return syscall(__NR_sched_getattr, pid, attr, size, flags);
 }

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

 int main (int argc, char **argv)
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
