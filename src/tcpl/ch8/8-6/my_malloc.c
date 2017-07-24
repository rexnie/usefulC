#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "my_malloc.h"

typedef long Align; /* 假设受限类型是long,有些平台可能是double或int */

/**
 * 空闲块的分配都是以HDR_SZ的整数倍为单位的，
 * 每个空闲块前面都有一个header结构,用来管理块的分配，释放，
 * 真正给用户的地址是没有头部的部分开始的地址，
 * 这个头部只有内部可见的，对用户程度是透明的。
 */
union header { /* 空闲块的头部 */
	struct {
		union header *ptr; /* 指向下一个空闲块地址 */
		unsigned size; /* 该空闲块大小，以HDR_SZ为单位 */
	} s;
	Align x; /* 强制块的对齐 */
};

#define HDR_SZ (sizeof(Header)) /* x86_64 linux14.02 上是16Byte, sizeof(long)=8 */
#define NALLOC 1024 /* 每次向OS申请内存时的最小大小，单位为HDR_SZ */

typedef union header Header;

static Header base; /* 空闲链表的表头 */
static Header *freep = NULL; /* 空闲链表的初始指针 */

/**
 * 向OS申请内存, nu * HDR_SZ byte,
 * OS 依赖的实现
 */
static Header *morecore(unsigned nu)
{
	char *cp;
	Header *up;

	if (nu < NALLOC)
		nu = NALLOC;

	/**
	 * man sbrk 查看详细说明
	 * 调整调用进程的data section的大小，来达到分配内存的作用
	 * 增大data section大小, 分配内存
	 * 减小data section大小, 释放内存
	 * 这块内存就是有malloc/free来管理的，叫做heap
	 * */
	cp = (char *) sbrk(nu * HDR_SZ);

	if (cp == (char *) -1) {
		printf("%s, %d sbrk fail, nu = %d\n", __FUNCTION__, __LINE__, nu);
		return NULL;
	}

	dbg("%s, %d cp=%p\n", __FUNCTION__, __LINE__, cp);
	up = (Header *) cp;
	up->s.size = nu;
	mfree((void *) (up + 1));
	return freep;
}

void *mmalloc(unsigned nbytes)
{
	Header *p, *prevp;
	unsigned nunits;

	nunits = (nbytes + HDR_SZ - 1) / HDR_SZ + 1;
	dbg("%s, %d nunits=%d\n", __FUNCTION__, __LINE__, nunits);
	if ((prevp = freep) == NULL) { /* 没有空闲链表 */
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}

	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {
			if (p->s.size == nunits)
				prevp->s.ptr = p->s.ptr;
			else { /* 当该块比较大时，先分配尾部部分，剩余部分链到空闲链表, 下次直接从这块开始查找合适块 */
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *) (p + 1); /* 去除头部给用户 */
		}

		if (p == freep) /* 闭环链表，没有合适大小的块可用，向os申请 */
			if ((p = morecore(nunits)) == NULL) {
				printf("%s, %d os no memory\n", __FUNCTION__, __LINE__);
				return NULL; /* os没有剩余内存可用 */
			}
	}
}

void mfree(void *ap)
{
	Header *bp, *p;

	bp = (Header *) ap - 1; /* 指向块头 */
	dbg("%s, %d freep=%p, bp=%p\n", __FUNCTION__, __LINE__, freep, bp);
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
		dbg("%s, %d p=%p\n", __FUNCTION__, __LINE__, p);
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
			dbg("%s, %d p=%p\n", __FUNCTION__, __LINE__, p);
			break; /* 被释放的块在链表的开头或末尾 */
		}
	}

	if (bp + bp->s.size == p->s.ptr) { /* 与上一相邻块合并 */
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		bp->s.ptr = p->s.ptr;

	if (p + p->s.size == bp) { /* 与下一相邻块合并 */
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;
	freep = p;
}

void *mcalloc(size_t nmemb, unsigned size)
{
	void *p = NULL;
	unsigned total = size * nmemb;

	if ((p = mmalloc(total)) != NULL)
		memset(p, 0, total);
	return p;
}

#ifdef DEBUG
void dump_free_list(const char *func, int line)
{
	Header *p;
	dbg("########### dump free list ############\n");
	dbg("called in %s, %d, &base=%p, freep=%p, HDR_SZ=%ld\n", func, line, &base, freep, HDR_SZ);
	for (p = &base; p->s.ptr != &base; p = p->s.ptr)
		dbg("p->s.ptr=%p, p->s.size=%d\n", p->s.ptr, p->s.size);
	dbg("p->s.ptr=%p, p->s.size=%d\n", p->s.ptr, p->s.size);
	dbg("\n");
}
#endif
