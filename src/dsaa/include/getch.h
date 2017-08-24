#ifndef __GETCH_H__
#define __GETCH_H__
/**
 * 取一个字符
 * 如果缓冲区为空，从标准输入读一个
 * 如果缓冲区不为空,代表之前有压回的字符
 */
int getch(void);

/**
 * 压回一个字符
 */
void ungetch(int c);
#endif
