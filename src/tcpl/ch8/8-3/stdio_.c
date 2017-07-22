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
	int bufsize;

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
	bufsize = (fp->flag.is_unbuf) ? 1 : BUFSIZ;

	/* 这里用户空间的读写函数都用这个buffer,
	 * 所以这个demo里一个文件只能读打开(r)或者写打开(w,a),
	 * 不能同时既读又写，这样buffer 会乱。
	 * TODO: 应该使用读写两个独立的buffer或者复杂点的读写在两端的fifo */
	if ((fp->base = (char *) malloc(bufsize)) == NULL)
		return EOF;
	fp->ptr = fp->base;
	if (*mode == 'r') {
		fp->flag.is_read = 1;
		fp->cnt = 0;
	} else {
		fp->flag.is_write = 1;
		fp->cnt = bufsize;
	}
	return fp;
}

int _fillbuf(FILE *fp)
{
	int bufsize;

	if (!fp->flag.is_read || fp->flag.is_eof || fp->flag.is_ferr)
		return EOF;
	bufsize = (fp->flag.is_unbuf) ? 1 : BUFSIZ;

	fp->cnt = read(fp->fd, fp->base, bufsize);
	fp->ptr = fp->base;

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

int _flushbuf(int c, FILE* fp)
{
	int bufsize;
	int i;
	int written;
	unsigned char *buf, *p, *psrc;

	if (fp->flag.is_ferr || !fp->flag.is_write)
		return EOF;
	bufsize = (fp->flag.is_unbuf) ? 1 : BUFSIZ;
	bufsize -= fp->cnt + 1; // +1 表存储c, 这样可减少write system call次数

	if ((p = buf = (unsigned char *) malloc(bufsize)) == NULL)
		return -1;
	psrc = fp->base;

	for (i = bufsize; i >= 2; i--)
		*p++ = *psrc++;
	*p++ = (unsigned char) c;

	written = 0;
	psrc = buf;
	while (written < bufsize &&
			(i = write(fp->fd, psrc, bufsize - written)) > 0) {
		written += i;
		psrc += i;
	}

	if (i <= 0) {
		printf("write error, i = %d\n", i);
	}

	fp->cnt = bufsize - 1;
	fp->ptr = fp->base;

	free(buf);
	return written;
}

int _flush_writebuf(FILE* fp)
{
	int bufsize;
	int i;
	int written;
	unsigned char *buf;

	if (fp->flag.is_ferr || !fp->flag.is_write)
		return EOF;
	bufsize = (fp->flag.is_unbuf) ? 1 : BUFSIZ;
	bufsize -= fp->cnt;

	written = 0;
	buf = fp->base;
	while (written < bufsize &&
			(i = write(fp->fd, buf, bufsize - written)) > 0) {
		written += i;
		buf += i;
	}

	if (i <= 0) {
		printf("write error, i = %d\n", i);
	}

	fp->cnt = bufsize;
	fp->ptr = fp->base;

	return written;
}


int fflush(FILE *fp)
{
	int i;
	FILE *tmp;
	int ret = 0;

	if (fp != NULL) {
		if (fp->flag.is_read) {
			fp->cnt = 0;
			fp->ptr = fp->base;
		} else
			ret = _flush_writebuf(fp);
	} else {
		for (i = 0; i < OPEN_MAX; i++) {
			tmp = &_iob[i];
			if (tmp != NULL && tmp->fd >= 0) {
				if (tmp->flag.is_read) {
					tmp->cnt = 0;
					tmp->ptr = tmp->base;
				} else
					ret = _flush_writebuf(tmp);
			}
		}

	}
	return ret >= 0 ? 0 : EOF;
}

int fclose(FILE *fp)
{
	if (fp != NULL) {
		fflush(fp);
		free(fp->base);
		fp->base = NULL;
		memset(fp, 0, sizeof(*fp));
	}
	return 0;
}

int main(void)
{
	FILE *fp, *fpw;
	int c;
	int fd;

	fp = fopen("t", "r");
	if (fp == NULL) {
		printf("open file for read error\n");
		exit(1);
	}

	fpw = fopen("tw", "w");
	if (fpw == NULL) {
		printf("open file for write error\n");
		exit(1);
	}
	while ((c = getc(fp)) != EOF) {
		//printf("%c", c);
		putc(c, fpw);
	}
	fclose(fp);
	fclose(fpw);
	exit(0);
}
