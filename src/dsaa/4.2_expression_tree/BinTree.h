#ifndef __BIN_TREE_h
#define __BIN_TREE_h 1
/** 二叉树 */

typedef void* ET_BinTree;
typedef struct BinTreeNode* BinTree;

ET_BinTree BinT_Retrieve(BinTree t);

/**
 * 构建一棵新树
 */
BinTree BinT_BuildTree(void *val, BinTree l, BinTree r);

/**
 * 先序遍历二叉树, 递归实现
 */
void BinT_TravelPreorder(BinTree root, void (*func)(ET_BinTree));

/**
 * 先序遍历二叉树, 非递归实现
 */
void BinT_TravelPreorder2(BinTree root, void (*func)(ET_BinTree));

/**
 * 中序遍历二叉树, 递归实现
 */
void BinT_TravelInorder(BinTree root, void (*func)(ET_BinTree));

/**
 * 中序遍历二叉树, 非递归实现
 */
void BinT_TravelInorder2(BinTree root, void (*func)(ET_BinTree));

/**
 * 后序遍历二叉树, 递归实现
 */
void BinT_TravelPostorder(BinTree root, void (*func)(ET_BinTree));

/**
 * 后序遍历二叉树, 非递归实现, 方法1
 */
void BinT_TravelPostorder2(BinTree root, void (*func)(ET_BinTree));

/**
 * 后序遍历二叉树, 非递归实现, 方法2
 */
void BinT_TravelPostorder3(BinTree root, void (*func)(ET_BinTree));

/**
 * 层序遍历二叉树, 非递归实现
 */
void BinT_TravelLevelorder(BinTree root, void (*func)(ET_BinTree));
#endif
