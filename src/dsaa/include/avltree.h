#ifndef _AvlTree_H
#define _AvlTree_H
/**
 * AVL树，带有平衡条件的二叉查找树
 * 这里的平衡条件是左右子树的高度最多叉1
 */

typedef int ET_AvlTree;
struct AvlNode;
typedef struct AvlNode *AvlTree;

/**
 * 释放二叉树的空间，回收内存
 * 返回:
 * NULL
 */
AvlTree AVLT_MakeEmpty( AvlTree T );

/**
 * 在二叉树中找节点为X的节点
 * 返回:
 * NULL: 没找到
 * !NULL: 值为X的节点的指针
 */
AvlTree AVLT_Find( ET_AvlTree X, AvlTree T );

/**
 * 返回二叉树中最小值
 * NULL: 空树
 * !NULL: 值最小的节点的指针
 */
AvlTree AVLT_FindMin( AvlTree T );

/**
 * 返回二叉树中最大值
 * NULL: 空树
 * !NULL: 值最大的节点的指针
 */
AvlTree AVLT_FindMax( AvlTree T );

/**
 * 向二叉树中插入X节点,如果X已经存在，则什么都不做
 * 插入可能会导致需要通过旋转来调整二叉树使之达到新的平衡
 * NULL: 空树,插入失败，原因如内存分配失败
 * !NULL: 根节点的指针
 */
AvlTree AVLT_Insert( ET_AvlTree X, AvlTree T );

/**
 * 删除二叉树T中值为X的节点
 * 书中提到在删除操作比较少的情况下，可采用懒惰删除
 * 因为比较复杂，未实现
 */
AvlTree AVLT_Delete( ET_AvlTree X, AvlTree T );

/**
 * 取得节点T的值，给外部调用，这样可隐藏实现内部数据结构
 */
ET_AvlTree AVLT_Retrieve( AvlTree P );

/**
 * 打印树的节点关系和高度，方便手动绘画树，方便调试
 */
void AVLT_DumpDetails(AvlTree T);
#endif  /* _AvlTree_H */
