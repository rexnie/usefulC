#include <stdio.h>
#include <stdlib.h>
#include "my_malloc.h"

int main(void)
{
	void *p1, *p2, *p3, *p4;
	if ((p1 = mmalloc(1022 * 16)) == NULL)
		printf("mmalloc p1 error\n");
	else
		printf("p1=%p\n", p1);

	dump_free_list(__FUNCTION__, __LINE__);
	if ((p2 = mmalloc(1022 * 16)) == NULL)
		printf("mmalloc p2 error\n");
	else
		printf("p2=%p\n", p2);

	dump_free_list(__FUNCTION__, __LINE__);
	if ((p3 = mmalloc(1022 * 16)) == NULL)
		printf("mmalloc p3 error\n");
	else
		printf("p3=%p\n", p3);
	dump_free_list(__FUNCTION__, __LINE__);
	mfree(p3);
	dump_free_list(__FUNCTION__, __LINE__);
	mfree(p1);
	dump_free_list(__FUNCTION__, __LINE__);
	mfree(p2);
	dump_free_list(__FUNCTION__, __LINE__);
	exit(0);
}
