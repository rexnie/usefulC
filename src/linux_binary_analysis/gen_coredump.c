#include<stdio.h>

/* ulimit -c unlimited
 *   to enable coredump
 * ulimit -a
 *   to check enable coredump or not
 */

int main(void)
{
	int *p = NULL;
	printf("to generate a coredump file: %d\n", *p);
	
	return 0;
}
