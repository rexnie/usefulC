#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(void)
{
	int ret, incr = 19;
	errno = 0;

	ret = nice(incr);
	if (errno != 0) {
		perror("nice return error");
		return -1;
	}

	printf("new nice val=%d\n", ret);
	while (1);
	return 0;
}
