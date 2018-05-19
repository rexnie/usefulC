#include <stdio.h>

#define SZ (64*1024*1024)

/* segmentation error */
void func(void)
{
    char buf[SZ];
    printf("sizeof buf=%lu\n", sizeof(buf));
}

int main(void)
{
    int *p = 0;
    /*p = 17;*/ /* segmentation error */

     func();

    return 0;
}
