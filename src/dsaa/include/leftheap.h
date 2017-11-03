#ifndef _LeftHeap_H
#define _LeftHeap_H

/**
 * 左式堆实现优先级队列
 */

typedef int ET_LH;
struct TreeNode;
typedef struct TreeNode *LeftHeap;

/* 左式堆中元素最小值的界，所有的元素都要大于该值 */
#define LHMinData (-1)

/* Minimal set of priority queue operations */

/**
 * 创建节点个数为n的左式堆
 * 返回:
 * NULL: 创建失败
 * !NULL: 新建的堆的根指针
 */
LeftHeap LH_BuildHeap( ET_LH *a, int n );


/**
 * 合并两个堆,返回新堆的根指针
 * Note that nodes will be shared among several
 * leftist heaps after a merge; the user must
 * make sure to not use the old leftist heaps
 */
LeftHeap LH_Merge( LeftHeap H1, LeftHeap H2 );

/**
 * 删除堆中最小元
 * X: [out] 返回被删除节点的最小值
 * 返回:
 * 新堆的根的指针
 */
LeftHeap LH_DeleteMin( ET_LH *X, LeftHeap H );

/**
 * 找堆中的最小元
 * 返回:
 * LHMinData: 这是一个空堆
 * 其他: 堆中的最小元
 */
ET_LH LH_FindMin( LeftHeap H );

/**
 * 返回:
 * 1: 堆为空
 * 0: 堆不为空
 */
int LH_IsEmpty( LeftHeap H );

/**
 * 释放heap占用的内存空间
 */
LeftHeap LH_Destroy( LeftHeap T );

/**
 * 打印左式堆内部结构,方便调试，形式如下:
 * node val=, node_npl, node->Left, node->Right
 */
void LH_Dump( LeftHeap H, char *tag );
#endif

