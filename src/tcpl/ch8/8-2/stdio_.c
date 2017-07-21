#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#include "stdio_.h"

#define PERMS 	0666

FILE _iob[OPEN_MAX] = {
	{ 0, (char *) 0, (char *) 0, { .is_read = 1 }, 0 },
	{ 0, (char *) 0, (char *) 0, { .is_write = 1 }, 1 },
	{ 0, (char *) 0, (char *) 0, { .is_write = 1, .is_unbuf = 1 }, 2 },
};

FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if (!fp->flag.is_read && !fp->flag.is_write)
			break;
	if (fp >= _iob + OPEN_MAX)
		return NULL;

	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);

	if (fd == -1)
		return NULL;

	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->ptr = NULL;
	if (*mode == 'r')
		fp->flag.is_read = 1;
	else
		fp->flag.is_write = 1;
	return fp;
}

int _fillbuf(FILE *fp)
{
	int bufsize;

	if (!fp->flag.is_read || fp->flag.is_eof || fp->flag.is_ferr)
		return EOF;
	bufsize = (fp->flag.is_unbuf) ? 1 : BUFSIZ;

	if (fp->base == NULL)
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);

	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag.is_eof = 1;
		else
			fp->flag.is_ferr = 1;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

int main(void)
{
	FILE *fp;
	int c;

	fp = fopen("t", "r");
	if (fp == NULL) {
		printf("open file error\n");
		exit(1);
	}
	while ((c = getc(fp)) != EOF)
		printf("%c", c);
	exit(0);
}
