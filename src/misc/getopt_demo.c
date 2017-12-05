/*
 ============================================================================
 Name        : getopt.c
 Author      : Rex
 Version     :
 Copyright   : Rex's copyrigith
 Description : demo getopt() usage
 ============================================================================
 */
#define _POSIX_C_SOURCE 2 /* for getopt() */
#include <unistd.h> 

#include "ds.h"

int main(int argc, char *argv[])
{
	int i;
	int ret;

	for(i=0;i<argc;i++)
		printf("%d:%s\n",i,argv[i]);
	dbg("optind=%d\n", optind);
	do {
		ret = getopt(argc, argv, "a:b::cdh");
		dbg("ret=%d, optarg=%s, optind=%d\n", ret, optarg, optind);
		if (ret == EOF) {
			err("end of option\n");
			break;
		}

		switch (ret) {
		case 'a':
			printf("got option char a, required optarg=%s\n", optarg);
			break;
		case 'b':
			printf("got option char b, optional optarg=%s\n", optarg);
			break;
		case 'c':
			printf("got option char c, optarg=%s\n", optarg);
			break;
		case 'd':
			printf("got option char d\n");
			break;
		case 'h':
			printf("Usage:\n");
			printf("getopt_demo -a aaa -b bbb -c ccc -d -h\n");
			break;
		default:
			printf("unknown option: ret=%d, optopt=%c\n", ret, optopt);
			break;
		}

	} while(1);
	dbg("optind=%d, argc=%d\n", optind,argc);
	return EXIT_SUCCESS;
}
