#ifndef __DISJOINT_SET_H
#define __DISJOINT_SET_H 1
#include "ds.h"

#define NUM_SETS 100

/**
 * 不相关集ADT
 * 使用树表示集合，树存储在数组中
 */

/**
 * DisjSet[i]
 * < 0: 表示该节点是集合的根节点，DisjSet[i]的绝对值表示该集合的元素个数
 * > 0: 存放的是元素i的父节点
 * DisjSet[0] reserved
 */
typedef int DisjSet[NUM_SETS + 1];
typedef int SetType;

/**
 * 初始化不相关集
 * 初始化每个元素为独立的集合
 */
void DS_Initialize(DisjSet S);

/**
 * 不相关集的Union操作
 * union by size
 */
void DS_SetUnion(DisjSet S, SetType Root1, SetType Root2);

/**
 * 不相关集的Find操作
 * 返回元素X所在的集合
 * 这里集合的名字也就是集合根元素的值
 */
SetType DS_Find(ElementType X, DisjSet S);

/**
 * 带路径压缩的DS_Find
 */
SetType DS_Find2(ElementType X, DisjSet S);
#endif
