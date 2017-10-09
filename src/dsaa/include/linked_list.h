#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H
/**
 * 带头节点的单链表ADT
 */

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

typedef void* ET_List;

/**
 * 返回一个带头结点的空链表,
 * 如果L不为空，释放L所指的内存，重新分配内存
 * 返回非空 为指向头结点的指针
 * 返回NULL 内存不足
 */
List MakeEmpty( List L );

/**
 * 返回1 代表链表为空
 * 返回0 代表链表非空
 */
int IsEmpty( List L );

/**
 * Return true if P is the last position in list L
 */
int IsLast( Position P, List L );

/**
 * Return Position of X in L; NULL if not found
 */
Position Find( ET_List X, List L );

/**
 * Delete from a list
 */
void Delete( ET_List X, List L );

/**
 * If X is not found, then Next field of returned value is NULL
 */
Position FindPrevious( ET_List X, List L );

/**
 * Insert (after legal position P)
 */
void Insert( ET_List X, List L, Position P );

/**
 * Insert after the last node
 */
void InsertTail(ET_List X, List L);

/**
 * 删除List中所有元素，回收头结点内存
 */
void DisposeList( List L);

/**
 * 删除List中所有元素，保留头结点
 */
void DeleteList( List L );

/**
 * 返回linked list的头结点
 */
Position Header( List L );

/**
 * 返回linked list的第一个结点
 */
Position First( List L );

/**
 * 返回linked list中P的后继结点
 */
Position Advance( Position P );

/**
 * 返回linked list中结点P的值
 */
ET_List Retrieve( Position P );

/**
 * 打印出linked list中所有元素
 * 设置func为特定的打印回调函数，
 * 传递NULL,使用默认打印函数
 */
void PrintList(List L, void (*func)(ET_List));

#endif    /* _LINKED_LIST_H */
