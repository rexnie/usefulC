#include <string.h>
#include "keytab.h"

/**
 * 在tab[0]-tab[n-1]中查找word单词
 * -1 : 没有找到word
 *  >=0: word在tab[]中的位置
 */
int binsearch(char *word, struct key tab[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low < high) {
		mid = (low + high) / 2;
		if (strcmp(word, tab[mid].word) <= 0)
			high = mid;
		else
			low = mid + 1;
	}
	return strcmp(word, tab[low].word) == 0 ? low : -1;
}
/*指针版本*/
struct key *binsearch_p(char *word, struct key *tab, int n)
{
	struct key *low, *high, *mid;

	low = &tab[0];
	high = &tab[n - 1];
	while (low < high) {
		mid = low + (high - low) / 2; /*指针加法非法，high-low为中间元素个数*/
		if (strcmp(word, mid->word) <= 0)
			high = mid;
		else
			low = mid + 1;
	}
	return strcmp(word, low->word) == 0 ? low : NULL;
}
