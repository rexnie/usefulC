#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXLINE 1000
#define MAXLEN 	1000

int read_line(char *buf, int maxlen)
{
	if (fgets(buf, maxlen, stdin))
		return strlen(buf);
	return -1;
}

/**
 * 读取最多maxline行的数据放在buf
 * 返回实际读到的行数
 */
int read_lines(char **buf, int maxline)
{
	char tmp[MAXLEN];
	int lines = 0, len;
	void *p;
	char **ptr = buf;

	while ((len = read_line(tmp, MAXLEN)) > 0) {
		//printf("%d, %d, %s\n", __LINE__, len, tmp);
		if (++lines > maxline || (p = malloc(len)) == NULL) {
			*ptr = NULL;
			return lines;
		} else {
			memcpy(p, tmp, len);
			*ptr++ = p;
			p = NULL;
		}
	}
	return lines;
}


int main(int argc, char *argv[])
{
	int output_line = 10;
	char *buf[MAXLINE];
	int lines;
	int line_num;
	int i;

	while (--argc > 0 && ((*++argv)[0] == '-')) {
		//printf("###%s\n", *argv);
		switch ((*argv)[1]) {
			case '0': case '1': case '2': case '3': case '4': case '5':
			case '6': case '7': case '8': case '9':
				i = atoi(&((*argv)[1]));
				if (i > 0)
					output_line = i;
				break;
			default:
				printf("error: unknown input, %s\n", *argv);
		}

	}

	lines = read_lines(buf, MAXLINE);

	printf("-------------------------------,%d\n", lines);
	for (i = 0; i < lines; i++) {
		printf("%d %s", i + 1, buf[i]);
	}
	printf("++++++++++++++++++++++++++++++++,%d \n", output_line);

	if (lines < output_line) {
		output_line = lines;
	}

	i = lines - output_line;
	while (output_line > 0) {
		printf("%d %s", i + 1, buf[i]);
		output_line --;
		i++;
	}
	return EXIT_SUCCESS;
}
