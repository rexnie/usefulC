#ifndef _BinHeap_H
#define _BinHeap_H

/**
 * 使用二叉堆(binary heap)实现优先队列,
 * 二叉堆内部使用数组作为组织数据的方式.
 * 书中提到了优先队列要实现的两个基本操作是
 * DeleteMin和Insert.
 * 也简单提到可用链表和二叉查找树实现优先队列的方法.
 */

/* 二叉堆最小的容量大小 */
#define PQMinSize (10)
/* 二叉堆中元素最小值的界，所有的元素都要大于该值 */
#define PQMinData (-1)

typedef int ET_PQ;
struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;

/**
 * 堆的基本操作
 */

/**
 * 初始二叉堆，分配内部存储
 * 返回:
 * NULL: 内部分配存储失败
 * !NULL: PriorityQueue结构的指针, 后续所有关于优先队列的操作
 * 都要传递该结构
 */
PriorityQueue PQ_Initialize( int MaxElements );

/**
 * 把数组中的N个任意排序元素放入到空的二叉堆
 * 把数组a的元素copy到H->Elements后，调用PQ_PercolateDown实现
 * 时间复杂度为O(N)
 * 返回:
 * 0: 成功
 * -1: 失败
 */
int PQ_BuildHeap( ET_PQ *a, int N, PriorityQueue H );

/**
 * 把数组中的N个任意排序元素放入到空的二叉堆
 * 调用N次PQ_Insert实现
 * 返回:
 * 0: 成功
 * -1: 失败
 */
int PQ_BuildHeap2( ET_PQ *a, int N, PriorityQueue H );

/**
 * 释放二叉堆内部的所有内存
 * 该调用后H为NULL,不可再使用
 */
void PQ_Destroy( PriorityQueue H );

/**
 * 删除二叉堆内所有的元素,
 * 该调用后H为包含0个元素的二叉堆结构
 */
void PQ_MakeEmpty( PriorityQueue H );

/**
 * 把X插入到H，并保持二叉堆的结构特性和堆序性
 * 若X已经在H中，会有多个值为X的节点
 * 时间复杂度为O(log2N), N为H中元素个数
 */
void PQ_Insert( ET_PQ X, PriorityQueue H );

/**
 * 删除最小元素
 * 时间复杂度为O(log2N), N为H中元素个数
 * 返回:
 * PQMinData: H为空
 * X: 二叉堆中的最小值
 */
ET_PQ PQ_DeleteMin( PriorityQueue H );

/**
 * 找最小元素
 * 时间复杂度为O(1)
 * 返回:
 * PQMinData: H为空
 * X: 二叉堆中的最小值
 */
ET_PQ PQ_FindMin( PriorityQueue H );

/**
 * 二叉堆是否为空
 * 返回:
 * 1: 为空
 * 0: 非空
 */
int PQ_IsEmpty( PriorityQueue H );

/**
 * 二叉堆是否已满
 * 返回:
 * 1: 已满
 * 0: 未满
 */
int PQ_IsFull( PriorityQueue H );

/**
 * 以下为堆的其它操作, 需要直到节点在二叉堆中的位置，
 * 本例因为是数组，所以直接遍历。
 * 书中提到其它的定位方法，如通过散列表来根据关键字找到节点位置
 */

/**
 * 降低关键字的值,delta为降幅>0
 */
void PQ_DecreaseKey(ET_PQ key, int delta, PriorityQueue H);

/**
 * 增加关键字的值,delta为增幅>0
 */
void PQ_IncreaseKey(ET_PQ key, int delta, PriorityQueue H);

/**
 * 删除关键字为key的节点
 */
ET_PQ PQ_Delete(ET_PQ key, PriorityQueue H);

/**
 * 打印出二叉堆中元素
 */
void PQ_Dump( PriorityQueue H, char *tag );
#endif
