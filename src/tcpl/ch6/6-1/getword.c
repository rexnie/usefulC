#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLINE 1000
#define MAXLEN 	1000

/**
 * 从输入中读取一个单词放到word,
 * lim标志着buf的最大长度
 * 单词以字母开头的字母和数字串，
 * 返回值：
 * 单词首字母，如果是一个单词的话
 * EOF，
 * 字符本身，如果首字符不是字母的话
 */
int getword(char *word, int lim)
{
	int c;
	char *w = word;

	int getch(void);
	void ungetch(int);

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}
