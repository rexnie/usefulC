#include <stdio.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(void)
{
	int ret;
	int which = PRIO_PROCESS;
	int who;
	errno = 0;

	printf("input pid: ");
	scanf("%d", &who);
	ret = getpriority(which, who);
	if (errno != 0) {
		perror("nice return error");
		return -1;
	}

	printf("pid=%d's nice val=%d\n", who, ret);
	return 0;
}
