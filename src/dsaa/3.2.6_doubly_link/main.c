#include "ds.h"
#include "list.h"

struct list1 {
	int val;
	int val2;
	struct list_head l;
};

struct list2 {
	char val;
	int val2;
	struct list_head l;
};

struct list3 {
	float val;
	struct list_head l;
};

int main(void)
{
	static LIST_HEAD(list);

	struct list1 l11, l12, *l1;
	struct list2 l21, *l2;
	struct list3 l31, l32, *l3;
	struct list_head *pos;
	int cnt;

	l11.val = 1;
	l12.val = 10;

	l21.val = 'A';
	l21.val2 = 3;

	l31.val = 3.14;
	l32.val = 2.71;

	list_add_tail(&l11.l, &list);
	list_add_tail(&l12.l, &list);
	list_add_tail(&l21.l, &list);
	list_add_tail(&l31.l, &list);
	list_add_tail(&l32.l, &list);

	cnt = 0;
	list_for_each(pos, &list) {
		if (cnt == 0 || cnt == 1) {
			l1 = container_of(pos, struct list1, l);
			dbg("cnt=%d: %d\n", cnt, l1->val);
		} else if (cnt == 2) {
			l2 = container_of(pos, struct list2, l);
			dbg("cnt=%d: %c, %d\n", cnt, l2->val, l2->val2);
		} else {
			l3 = container_of(pos, struct list3, l);
			dbg("cnt=%d: %f\n", cnt, l3->val);
		}

		cnt ++;
	}
	dbg("%d\n", cnt);
	return EXIT_SUCCESS;
}
