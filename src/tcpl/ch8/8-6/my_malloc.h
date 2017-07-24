#ifndef __MY_MALLOC_H__
#define __MY_MALLOC_H__

void *mmalloc(unsigned nbytes);
void mfree(void *ap);
void *mcalloc(size_t nmemb, unsigned size);

/* test functions, should used internal */
#undef DEBUG
//#define DEBUG

#ifdef DEBUG
void dump_free_list(const char *, int);
#define dbg(fmt, args...) printf(fmt, ##args)
#else
#define dump_free_list(func, lineno)
#define dbg
#endif

#endif
