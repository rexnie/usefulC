#ifndef _Queue_h
#define _Queue_h

typedef void* ET_Queue;
struct QueueRecord;
typedef struct QueueRecord *Queue;

/**
 * 判断循环队列是否为空
 * 返回1为空，0 非空
 */
int Q_IsEmpty( Queue Q );

/**
 * 判断循环队列是否满
 * 返回1已满，0 未满
 */
int Q_IsFull( Queue Q );

/**
 * 创建循环队列, 队列最大元素个数是MaxElements
 * 返回NULL失败，非空为新创建的struct QueueRecord的指针
 */
Queue Q_CreateQueue( int MaxElements );

/**
 * 释放Queue所有的内存空间，包括Queue, Q->Array
 */
void Q_DisposeQueue( Queue Q );

/**
 * 初始化队列为空
 */
void Q_MakeEmpty( Queue Q );

/**
 * 把X入队
 */
void Q_Enqueue( ET_Queue X, Queue Q );

/**
 * 查看队列头部的一个元素值，不出队列
 */
ET_Queue Q_Front( Queue Q );

/**
 * 出队一个元素
 */
ET_Queue Q_Dequeue( Queue Q );

#endif  /* _Queue_h */
