#ifndef __MY_MALLOC_H__
#define __MY_MALLOC_H__

void *mmalloc(unsigned nbytes);
void mfree(void *ap);
void *mcalloc(size_t nmemb, unsigned size);

/* test functions, should used internal */
void dump_free_list(void);
#endif
