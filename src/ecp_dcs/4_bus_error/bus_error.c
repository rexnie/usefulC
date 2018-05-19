#include <stdio.h>

union {
    char a[10];
    int i;
} u;

int main(void)
{
#if defined(__GNUC__)
# if defined(__i386__)
    /* Enable Alignment Checking on x86 */
    __asm__("pushf\norl $0x40000,(%esp)\npopf");
# elif defined(__x86_64__)
    /* Enable Alignment Checking on x86_64 */
    __asm__("pushf\norl $0x40000,(%rsp)\npopf");
# endif
#endif

    int *p = (int *) (&(u.a[1]));

    /**
     * p中未对齐的地址将会引起总线错误，
     * 因为数组和int的联合确保了a是按照int的4字节来对齐的，
     * 所以“a+1”肯定不是int对齐的
     */
    *p = 17;
    printf("%d %p %p %p\n", *p, &(u.a[0]), &(u.a[1]), &(u.i));
    printf("%lu %lu\n", sizeof(char), sizeof(int));
    return 0;
}
