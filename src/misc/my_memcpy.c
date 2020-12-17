#include <stdio.h>

/**
 * void *memcpy(void *dest, const void *src, size_t count)
 * ref: https://blog.csdn.net/goodwillyang/article/details/45559925
 */

void *memcpy1(void *dest, const void *src, size_t count)
{
    char *d;
    const char *s;

    if ((dest < src) || (dest > src + count)) {
        d = (char *) dest;
        s = (char *) src;
        while (count--)
            *d++ = *s++;
    } else {
        d = (char*) (dest + count - 1);
        s = (char*) (src + count - 1);
        while (count--)
            *d-- = *s--;
    }
    return dest;
}

/* this is a fail case, which will cause case 1 fail */
void *memcpy2(void *dest, const void *src, size_t count)
{
    char *d;
    const char *s;

    d = dest + count - 1;
    s = src + count - 1;
    while (count--)
        *d-- = *s--;
    return dest;
}

int main(void)
{
    char buf[] = "11111222223333344444555556666677777888889999900000";

    char *dest, *src;

#define CASE 3

    /* case 1
     * dest < src
     * 11112222223333344444555556666677777888889999900000
     */
#if CASE == 1
    dest = &buf[0]; src = &buf[1];
#endif

    /* case 2
     * dest > src + count
     * 11111222221111144444555556666677777888889999900000
     */
#if CASE == 2
    dest = &buf[10]; src = &buf[0];
#endif

    /* case 3
     * dest >= src && src + count > dest
     * 11111122223333344444555556666677777888889999900000
     */
#if CASE == 3
    dest = &buf[4]; src = &buf[3];
#endif

    printf("dest=%s\n buf=%s\n", (char*) memcpy1(dest, src, 5), buf);
    return 0;
}
