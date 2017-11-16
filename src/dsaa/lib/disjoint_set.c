#include "disjoint_set.h"

void DS_Initialize(DisjSet S)
{
	int i;

	for (i = NUM_SETS; i > 0; i--)
		S[i] = -1;
}

/**
 * 让元素较少的树成为较多树的子树
 */
void DS_SetUnion(DisjSet S, SetType Root1, SetType Root2)
{
	if (S[Root2] < S[Root1]) { /* Root2所在的集合元素更多 */
		S[Root2] += S[Root1]; /* 更新Root2所在的集合元素个数 */
		S[Root1] = Root2; /* Root1新的父节点是Root2 */
	} else {
		S[Root1] += S[Root2];
		S[Root2] = Root1;
	}
}

SetType DS_Find(ElementType X, DisjSet S)
{
	if (S[X] <= 0) /* 根节点，直接返回元素本身 */
		return X;
	else
		return DS_Find(S[X], S);
}

/**
 * 带路径压缩的DS_Find
 */
SetType DS_Find2(ElementType X, DisjSet S)
{
	if (S[X] <= 0) /* 根节点，直接返回元素本身 */
		return X;
	else
		return S[X] = DS_Find(S[X], S); /* S[X] 直接指向根节点 */
}
