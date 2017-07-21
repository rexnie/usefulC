#ifndef __STDIO__H__
#define __STDIO__H__

#undef NULL
#define NULL 	 0
#define EOF 	 (-1)
#define BUFSIZ   (1024)
#define OPEN_MAX (20)

typedef struct _iobuf {
	int cnt; 	/* buf中剩余字符个数 */
	char *ptr; 	/* 指向buf的下一个读写位置 */
	char *base; 	/* buf地址 */
	struct {
		unsigned int is_read : 1;
		unsigned int is_write : 1;
		unsigned int is_unbuf : 1;
		unsigned int is_eof : 1;
		unsigned int is_ferr: 1;
	} flag; 	/* 文件访问模式 */
	int fd; 	/* unix 底层fd */
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin 	(&_iob[0])
#define stdout 	(&_iob[1])
#define stderr 	(&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE*);

#define feof(p) 	((p)->flag.is_eof)
#define ferror(p) 	((P)->flag.is_ferr)
#define fileno(p) 	((p)->fd)

#define getc(p) 	(--(p)->cnt >= 0 \
			? (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define putc(x, p) 	(--(p)->cnt >= 0 \
			? *(p)->ptr++ = (x) : _flushbuf((x), (p)))

#define getchar() 	getc(stdin)
#define putchar(x) 	putc((x), stdout)
#endif
