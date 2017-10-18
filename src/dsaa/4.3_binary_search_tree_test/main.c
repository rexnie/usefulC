#include "binary_search_tree.h"
#include "ds.h"
#include "num_seq.h"

#define AUTO_TEST_INSERT_DELETE 1

#if AUTO_TEST_INSERT_DELETE
#include "misc.h"

#define N 500
#define MIN_NODE_VAL 1
#define MAX_NODE_VAL 1000
#define TEST_TIMES 300

#define TCASE_INS 1
#define TCASE_DEL 2
#else
#define N 20
#endif

static SearchTree AutoCreateTree( int n, int min, int max, SearchTree T )
{
	int i;
	ET_STree *ptr;
	if ((ptr = get_nums_list_in_range_sorted(n, min, max)) != NULL) {
		for (i = 0; i < n; i++)
			printf("%d ", ptr[i]);
		printf("\n");
		for (i = 0; i < n; i++)
			T = BST_Insert(ptr[i], T);
		free(ptr);
	}
	return T;
}

#if AUTO_TEST_INSERT_DELETE
static int AutoTestInsertDelete(void)
{
	int i, idx;
	ET_STree *buf1 = NULL;
	ET_STree *buf2 = NULL;
	SearchTree T = NULL;
	int times = TEST_TIMES;
	int val;
	int tcase;
	int node_nums = N, node_nums2 = N;

#define SZ_TEST_BUF (N + TEST_TIMES)

	if ((buf1 = (ET_STree *) malloc(sizeof(ET_STree) * SZ_TEST_BUF)) == NULL) {
		err("alloc mem err\n");
		return -1;
	}

	if ((buf2 = (ET_STree *) malloc(sizeof(ET_STree) * SZ_TEST_BUF)) == NULL) {
		err("alloc mem err\n");
		return -1;
	}

	if ((T = AutoCreateTree(N, MIN_NODE_VAL, MAX_NODE_VAL, T)) == NULL) {
		err("create tree err\n");
		return -1;
	}

	while (times--) {

		if (times % 2 == 0)
			tcase = TCASE_INS;
		else
			tcase = TCASE_DEL;

		for (i = 0; i < SZ_TEST_BUF; i++)
			buf1[i] = buf2[i] = -1;

		BST_TravelInorder(T, buf1);

		val = rand_int(MIN_NODE_VAL, MAX_NODE_VAL);
		idx = index_of_array(buf1, node_nums, val);
		if ((idx != NotFound) && (tcase == TCASE_DEL))  /* val是某节点的值 */
			node_nums2 = node_nums - 1;

		if ((idx == NotFound) && (tcase == TCASE_INS))  /* val在树中不存在 */
			node_nums2 = node_nums + 1;
		switch (tcase) {
			case TCASE_INS:
				T = BST_Insert(val, T);
				break;
			case TCASE_DEL:
				T = BST_Delete(val, T);
				break;
			default:
				err("unknown test case\n");
				break;
		}

		BST_TravelInorder(T, buf2);
		if (node_nums == node_nums2) {
			/* 元素的个数不变，对比数组是否相等 */
		} else {
			/* 把val insert/del后，看是否相等 */
			if (tcase == TCASE_INS) {
				if (insert_val(buf1, node_nums, val) < 0) {
					err("insert value err\n");
					break;
				}
			} else if (tcase == TCASE_DEL) {
				if (delete_val(buf1, node_nums, val) < 0) {
					err("delete value err\n");
					break;
				}
			}
		}

		if (is_array_equal(buf1, buf2, node_nums2) == 0) {
			err("not equal\n");
			break;
		}

		node_nums = node_nums2;
	}


	BST_DumpDetails(T);
	for (i = 0; i < SZ_TEST_BUF; i++)
		printf("%d ", buf2[i]);
	printf("\ntimes=%d, node_nums2=%d\n", times, node_nums2);
	/*dbg("Height L=%d, R=%d\n", BST_HeightRootLeft(T), BST_HeightRootRight(T));
	dbg("Height root=%d\n", BST_Height(T));*/

	if (times == -1 ) {
		dbg("autotest finished successfully\n");
	} else {
		dbg("autotest fail\n");
	}
	BST_MakeEmpty(T);
	if (buf1 != NULL)
		free(buf1);
	if (buf2 != NULL)
		free(buf2);
	return 0;
}
#endif

int main(void)
{
#if AUTO_TEST_INSERT_DELETE
	AutoTestInsertDelete();
#else
	int i;
	SearchTree T = NULL;
	Position pos = NULL;
	ET_STree nums[N] = { 50, 73, 36, 86, 40,
		10, 64, 75, 26, 34,
		18, 44, 41, 57, 89,
		58, 98, 3, 4, 2,
	};

	for (i = 0; i < N; i++)
		T = BST_Insert(nums[i], T);

	dbg("after create tree:\n");
	BST_DumpDetails(T);

	pos = BST_Find(1, T);
	dbg("find val=1:%d\n", pos != NULL ? BST_Retrieve(pos) : -1);

	pos = BST_FindMin(T);
	dbg("find min:%d\n", BST_Retrieve(pos));

	pos = BST_FindMax(T);
	dbg("find max:%d\n", BST_Retrieve(pos));

	pos = BST_Insert(37,T);
	dbg("insert 37,pos=%d\n", BST_Retrieve(pos));
	dbg("after insert tree:\n");
	BST_DumpDetails(T);
	BST_PrintTreeInorder(T);
	printf("\n");

	pos = BST_Delete(73,T);
	dbg("delete 73, pos=%d\n", BST_Retrieve(pos));
	dbg("after delete 73:\n");
	BST_DumpDetails(T);
	BST_PrintTreeInorder(T);
	printf("\n");

	pos = BST_Delete(75,T);
	dbg("delete 75, pos=%d\n", BST_Retrieve(pos));
	dbg("after delete 75:\n");
	BST_DumpDetails(T);
	BST_PrintTreeInorder(T);
	printf("\n");

	pos = BST_Delete(64,T);
	dbg("delete 64, pos=%d\n", BST_Retrieve(pos));
	dbg("after delete 64:\n");
	BST_DumpDetails(T);
	BST_PrintTreeInorder(T);
	printf("\n");

	pos = BST_Delete(86,T);
	dbg("delete 86, pos=%d\n", BST_Retrieve(pos));
	dbg("after delete 86:\n");
	BST_DumpDetails(T);
	BST_PrintTreeInorder(T);
	printf("\n");
#endif
	return EXIT_SUCCESS;
}
