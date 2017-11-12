#ifndef _BinQueue_H
#define _BinQueue_H
typedef int ET_BQ;

/**
 * 二项队列的最大高度
 * 最大高度为h的二项队列能够表示的最大节点是2^(h+1)-1
 */
#define MaxTrees (14)   /* Stores 2^14 -1 items */
#define Capacity (16383)

#define Infinity (30000L)
struct BinNode;
typedef struct BinNode *BinTree;
struct Collection;
typedef struct Collection *BinQueue;

/**
 * alloc & initialize BinQueue struct
 * Other BQ_xx functions should take it as parameter
 * return:
 * NULL: init fail
 * !NULL: new BinQueue struct
 */
BinQueue BQ_Initialize( void );

/**
 * 把n个元素插入到空的二项队列
 * return:
 * 0: ok
 * -1: fail
 */
int BQ_BuildBinQueue(ET_BQ *a, int n, BinQueue h);

/**
 * free BinQueue struct and BinQueue's trees, after this call,
 * H is null, u should not use it further
 */
void BQ_Destroy( BinQueue H );

/**
 * 置空二项队列，回收二项树
 * 返回:
 * H
 */
BinQueue BQ_MakeEmpty( BinQueue H );

/**
 * 向二项队列插入Item元素
 * 返回:
 * NULL: 插入失败
 * H: 插入成功后的二项队列的指针
 */
BinQueue BQ_Insert( ET_BQ Item, BinQueue H );

/**
 * 同BQ_Insert, 不使用BQ_Merge实现
 * 直接构建一个二项树，插入到H
 */
BinQueue BQ_Insert2( ET_BQ Item, BinQueue H );

/**
 * 删除二项队列中最小元素
 * 返回:
 * -Infinity: 二项队列为空
 * other: 二项队列中最小元素
 */
BinQueue BQ_DeleteMin( ET_BQ *val, BinQueue H );

/**
 * 合并两个二项队列
 * 返回:
 * NULL: 合并失败, H1和H2保持不变
 * !NULL: 合并后的二项队列的指针,也即节点个数多的二项队列，
 *        另一个二项队列会被Destroy掉
 */
BinQueue BQ_Merge( BinQueue H1, BinQueue H2 );

/**
 * 返回二项队列中最小元素
 * 返回:
 * -Infinity: 二项队列为空
 * other: 二项队列中最小元素
 */
ET_BQ BQ_FindMin( BinQueue H );

/**
 * 二项队列是否为空
 * 返回:
 * 1: 二项队列为空
 * 0: 非空
 */
int BQ_IsEmpty( BinQueue H );

/**
 * 二项队列是否已满
 * 返回:
 * 1: 二项队列已满
 * 0: 未满
 */
int BQ_IsFull( BinQueue H );

/**
 * 打印二项队列的元素
 */
void BQ_DumpQueue(BinQueue h, char *tag);
#endif
