#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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
	if (!isalpha(c) && c != '_') {
		if (c == '"') { // 处理字符串常量, 直接忽略""之间的字符串
			while ((c = getch()) != '"')
				;
		} else if (c = '/') {
			if ((c = getch()) == '/') { // 处理//注释,直接忽略// \n之间的字符串
				while ((c = getch()) != '\n')
					;
			} else if (c == '*') { // 处理/**/注释,直接忽略/**/之间的字符串
				int last;
				last = getch();
again:
				while ((c = getch()) != '/')
					last = c;
				if (last != '*')
					goto again;
			} else
				ungetch(c);
		}

		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++)
		if (!isalnum(*w = getch()) && *w != '_') {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}
