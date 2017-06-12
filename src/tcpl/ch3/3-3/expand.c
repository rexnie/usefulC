/*
 * expand.c
 *
 *  Created on: Jun 10, 2017
 *      Author: niedaocai
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define TEST    0

#define CHAR_UNKNOW (-1)
#define CHAR_DIGIT	0
#define CHAR_LOWER	1
#define CHAR_UPPER	2

int get_char_type(char ch)
{
	if (isdigit(ch))
		return CHAR_DIGIT;
	else if (islower(ch))
		return CHAR_LOWER;
	else if (isupper(ch))
		return CHAR_UPPER;
	else
		return CHAR_UNKNOW;
}

char *expand(char s1[], char s2[])
{
	int i, j, k;
	char last_ch = '\0';
	int last_char_type = CHAR_UNKNOW;
	int pre_char_type = CHAR_UNKNOW;

	for (i = 0, j = 0; s1[i] != '\0';) {
		if (s1[i] == '-') {
			if (s1[i+1] == '\0') { /* 结尾是'-' */
				s2[j++] = s1[i];
				goto out;
			}

			pre_char_type = get_char_type(s1[i+1]);
			last_char_type = get_char_type(last_ch);

			if ((pre_char_type >= 0) &&  /*下一个字符是大小字母，或者数字*/
					(pre_char_type == last_char_type) && /*字符类型一致*/
					(s1[i+1] - last_ch > 0)) {	/*字符保持增序*/
				for (k = 1; k <= s1[i+1] - last_ch; k++) {
					s2[j++] = last_ch + k;
				}
				last_ch += k;
				i += 2;
			} else {	/*不需要扩展*/
				s2[j++] = s1[i++]; /* add '-' */
				last_ch = s1[i];
				s2[j++] = s1[i++]; 	/* add ch after '-' */
			}
		} else {
			last_ch = s1[i];
			s2[j++] = s1[i++];
		}
	}
out:
	s2[j] = '\0';
	return s2;
}

#if TEST
int main(void) {
	char *s1="-n-aieA-Zdao0-8ca-bi-";
	char s2[100];

	expand(s1, s2);
	printf("%s", s2);
    return EXIT_SUCCESS;
}
#endif
