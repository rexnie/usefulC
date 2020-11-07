#ifndef _LINUX_STDDEF_H
#define _LINUX_STDDEF_H

typedef _Bool bool;

#ifndef __always_inline
#define __always_inline inline
#endif

#define unlikely(x) (x)

#define WRITE_ONCE(ptr, val) (ptr = val)

#undef NULL
#define NULL ((void *)0)

enum {
	false	= 0,
	true	= 1
};

#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE, MEMBER)	__compiler_offsetof(TYPE, MEMBER)
#else
#define offsetof(TYPE, MEMBER)	((size_t)&((TYPE *)0)->MEMBER)
#endif

#define container_of(ptr, type, member) ({ 			\
		void *__mptr = (void *)(ptr); 			\
		((type *)(__mptr - offsetof(type, member))); })

#endif
