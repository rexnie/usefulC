#ifndef __BIN_TREE_h
#define __BIN_TREE_h 1
/** 二叉树 */

typedef void* ET_BinTree;
typedef struct BinTreeNode* BinTree;

ET_BinTree BinT_Retrieve(BinTree t);

BinTree BinT_BuildTree(void *val, BinTree l, BinTree r);


/**
 * 先序遍历二叉树
 */
void BinT_TravelPreorder(BinTree root, void (*func)(ET_BinTree));

/**
 * 中序遍历二叉树
 */
void BinT_TravelInorder(BinTree root);

/**
 * 后序遍历二叉树
 */
void BinT_TravelPostorder(BinTree root);

/**
 * 层序遍历二叉树
 */
void BinT_TravelLevelorder(BinTree root);
#endif
