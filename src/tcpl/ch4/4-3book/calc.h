/*
 * calc.h
 *
 *  Created on: Jun 12, 2017
 *      Author: niedaocai
 */

#ifndef TCPL_CH4_4_3BOOK_CALC_H_
#define TCPL_CH4_4_3BOOK_CALC_H_

#define NUMBER	'0'

void pushd(double);
double popd(void);

int getop(char[]);

int getch(void);
void ungetch(int);

#endif /* TCPL_CH4_4_3BOOK_CALC_H_ */
