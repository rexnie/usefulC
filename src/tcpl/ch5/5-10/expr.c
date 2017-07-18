#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "stack.h"

int main(int argc, char *argv[])
{
	char *p;
	double operand1, operand2;

	if (argc < 2) {
		printf("Usage: expr x y +\n"
				"number of parameters must be greater than 2\n");
		return EXIT_FAILURE;
	}

	init_stack();
	while (--argc > 0) {
		p = *++argv;
		printf("%s ",p);
		switch (p[0]) {
			case '+':
				if (strlen(p) > 1)
					push(atof(p));
				else
					push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				if (strlen(p) > 1)
					push(atof(p));
				else {
					operand2 = pop();
					push(pop() - operand2);
				}
				break;
			case '/':
				operand2 = pop();
				if (!operand2) {
					printf("error: divided by 0\n");
					goto err;
				}

				push(pop() / operand1);
				break;
			case '%':
				operand2 = pop();
				if (!operand2) {
					printf("error: mod by 0\n");
					goto err;
				}

				push(fmod(pop(), operand2));
				break;
			case '0': case '1': case '2': case '3': case '4': case '5':
			case '6': case '7': case '8': case '9':
				push(atof(p));
				break;
			default:
				printf("error: unknown input, %s\n", p);
				goto err;
		}

	}

	printf("\n\t %g\n", pop());

	return EXIT_SUCCESS;
err:
	return EXIT_FAILURE;
}
