#include <stdio.h>
#include <math.h>

int main(void)
{
	int nice;

	printf("nice   weight\n");
	for (nice=-20; nice<20; nice++) {
		printf("%3d    %f\n", nice, (double) 1024 / pow(1.25, nice));
	}

	return 0;
}
