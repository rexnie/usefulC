#include<stdio.h>
#include<malloc.h>

/** test on gcc 9.4
strings in .strtab section:
	string_table.c
	global_int_var_inited
	global_string_name
	global_int_var_uninited
	global_func
	local_static.1799
	malloc@@GLIBC_2.2.5
	printf@@GLIBC_2.2.5
	puts@@GLIBC_2.2.5

strings in .dynstr section:
	puts
	printf
	malloc

strings in .rodata section:
	daocain
	in global func...
	Hello World
	malloc failed
	%s %d %d\n
*/

char *global_string_name = "daocain";
int global_int_var_inited = 11;
int global_int_var_uninited;

int global_func(void)
{
	printf("in global func...\n");
	return 0;
}

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
	local_int_d = 3;
	printf("%s %d %d\n", local_string_a, local_int_d, global_func());
	return 0;
}

