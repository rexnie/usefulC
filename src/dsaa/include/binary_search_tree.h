#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

typedef int ET_STree;

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

/**
 * 释放二叉排序树节点空间，使T为一棵空树
 */
SearchTree BST_MakeEmpty( SearchTree T );

/**
 * 在二叉排序树中找X节点
 * 找到返回节点的指针，没找到返回NULL
 */
Position BST_Find( ET_STree X, SearchTree T );

/**
 * 空树返回NULL，否则返回最小值的节点指针
 */
Position BST_FindMin( SearchTree T );

/**
 * 空树返回NULL，否则返回最大值的节点指针
 */
Position BST_FindMax( SearchTree T );

/**
 * 插入新节点X, 树中已经存在的话，什么都不做
 * 返回根节点的指针
 */
SearchTree BST_Insert( ET_STree X, SearchTree T );

/**
 * 删除树中节点X
 */
SearchTree BST_Delete( ET_STree X, SearchTree T );

/**
 * 取节点P的元素值
 */
ET_STree BST_Retrieve( Position P );

void BST_PrintTreeInorder(SearchTree T);
void BST_DumpDetails(SearchTree T);
#endif  /* __BINARY_SEARCH_TREE_H__*/
