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

/**
 * 中序遍历二叉查找树
 */
void BST_PrintTreeInorder(SearchTree T);

/**
 * 中序遍历二叉查找树
 * 输出到outbuf, 不是stdout
 * 调用者必须保证outbuf足够大，并且初始化为一个特殊的
 * 不是树的元素的值，如-1
 */
void BST_TravelInorder(SearchTree root, ET_STree *outbuf);

/**
 * 求树的高
 * 空树的高为-1，叶子节点的高为0
 * 返回-2表示内部出错
 */
int BST_Height(SearchTree T);

/**
 * 求树T左子树的高
 */
int BST_HeightRootLeft(SearchTree T);

/**
 * 求树T右子树的高
 */
int BST_HeightRootRight(SearchTree T);

/**
 * 打印二叉查找树的结构信息，可由这个结构信息方便地画出树
 */
void BST_DumpDetails(SearchTree T);
#endif  /* __BINARY_SEARCH_TREE_H__*/
