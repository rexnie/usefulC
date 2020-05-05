#include<stdio.h>
#include<malloc.h>

char *global_string_name = "daocain";
int global_int_var_inited = 11;
int global_int_var_uninited;

int main(int argc,char *argv[])
{
	char *local_string_a ="Hello World";
	int local_int_b = 22;
	int *local_intp_c = 0;
	int local_int_d;
	static int local_static = 1;

	local_intp_c = (int *)malloc(0x100);
	if(local_intp_c == 0) {
		printf("malloc failed\n");
		return -1;
	}
	printf("%s\n", local_string_a);
	return 0;
}

