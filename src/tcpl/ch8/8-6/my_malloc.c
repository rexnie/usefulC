#include <unistd.h>
#include <string.h>
#include "my_malloc.h"

typedef long Align;

union header {
	struct {
		union header *ptr;
		unsigned size;
	} s;
	Align x;
};

#define HDR_SZ (sizeof(Header))
#define NALLOC 1024

typedef union header Header;

static Header base;
static Header *freep = NULL;

static Header *morecore(unsigned nu)
{
	char *cp;
	Header *up;

	if (nu < NALLOC)
		nu = NALLOC;

	cp = (char *) sbrk(nu * HDR_SZ);

	if (cp == (char *) -1)
		return NULL;

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
	if ((prevp = freep) == NULL) {
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}

	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {
			if (p->s.size == nunits)
				prevp->s.ptr = p->s.ptr;
			else {
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *) (p + 1);
		}

		if (p == freep)
			if ((p = morecore(nunits)) == NULL)
				return NULL;
	}
}

void mfree(void *ap)
{
	Header *bp, *p;

	bp = (Header *) ap - 1;
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;

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

void dump_free_list(void)
{
}
