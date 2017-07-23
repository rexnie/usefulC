#include <stdio.h>
#include <stdlib.h>
#include "my_malloc.h"

int main(void)
{
	void *p1, *p2, *p3;
	if ((p1 = mmalloc(20)) == NULL)
		printf("mmalloc p1 error\n");
	else
		printf("p1=%p\n", p1);

	if ((p2 = mmalloc(500)) == NULL)
		printf("mmalloc p2 error\n");
	else
		printf("p2=%p\n", p2);

	if ((p3 = mmalloc(1024)) == NULL)
		printf("mmalloc p3 error\n");
	else
		printf("p3=%p\n", p3);
	mfree(p3);
	mfree(p1);
	mfree(p2);
	exit(0);
}
