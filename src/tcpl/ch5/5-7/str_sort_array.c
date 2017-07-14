#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXLINES	500	/* 进行排序的最大行数 */
#define MAXLEN		1000	/* 要进行排序的文本最大长度 */
char *g_lineptr[MAXLINES];

int getline_local(char *line, int maxlen) {
	int len;
	char *p;

	clearerr(stdin);
	p = fgets(line, maxlen, stdin);
	if (p == NULL) {
		printf("error: feof()=%d, ferror()=%d\n", feof(stdin), ferror(stdin));
		return -1;
	} else {
		return strlen(p);
	}
	return 0;
}

/**
 * 读行到lines数组，每行的地址放在lineptr
 */
int readlines(char *lineptr[], int maxlines, char lines[][MAXLEN]) {
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getline_local(line, MAXLEN)) > 0) {
		if (nlines >= maxlines) {
			return -1;
		} else {
			line[len - 1] = '\0';	/* 删除换行符 */
			strcpy(lines[nlines], line);
			lineptr[nlines] = lines[nlines];
			nlines++;
		}
	}
	return nlines;
}

void writelines(char *lineptr[], int nlines) {
#if 0
	int i;
	for (i = 0; i < nlines; ++i)
		printf("%d:%s\n", i, lineptr[i]);
#else
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
#endif
}


/**
 * 交换v[i]与v[j]
 */
void swap(char *v[], int i, int j) {
	char *t;
	t = v[i];
	v[i] = v[j];
	v[j] = t;
}

/**
 * 按递增顺序对v[left] ... v[right]进行排序
 * TODO: 什么算法？
 */
void qsort_local(char *v[], int left, int right) {
	int i, last;

	if (left >= right)
		return;

	swap(v, left, (left + right) / 2);
	last = left;

	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);

	swap(v, left, last);
	qsort_local(v, left, last - 1);
	qsort_local(v, left + 1, right);
}

int main(void) {
	int nlines;
	char lines[MAXLINES][MAXLEN];
	clock_t time_start;
	time_t t_start;

	printf("Usage: \n"
		"./str_sort.out <in.txt \n"
		"./str_sort.out \n"
		"      press ctrl+D to send EOF \n");
	time_start = clock();
	t_start = time(NULL);
	if ((nlines = readlines(g_lineptr, MAXLINES, lines)) >= 0) {
		qsort_local(g_lineptr, 0, nlines - 1);
		writelines(g_lineptr, nlines);
		printf("time: %ld, %g\n", clock() - time_start, difftime(time(NULL), t_start));
		return EXIT_SUCCESS;
	} else {
		printf("error: input too big to sort\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
