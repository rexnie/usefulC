#include <stdio.h>

int count_1_in_byte(unsigned char c)
{
    int cnt = 0;
    while(c) {
        cnt += c & 0x1;
        c >>= 1;
    }

    return cnt;
}

int main(void)
{
    unsigned char i;
    char s[10];
    for (i = 0; i < 0xff; i++) {
        printf("i=%d, 0x%x, %d\n", i, i, count_1_in_byte(i));
    }

    return 0;
}
