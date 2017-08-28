#ifndef _Queue_h
#define _Queue_h

typedef int ET_Queue;
struct QueueRecord;
typedef struct QueueRecord *Queue;

/**
 * 判断循环队列是否为空
 * 返回1为空，0 非空
 */
int IsEmpty( Queue Q );

/**
 * 判断循环队列是否满
 * 返回1已满，0 未满
 */
int IsFull( Queue Q );
Queue CreateQueue( int MaxElements );

/**
 * 释放Queue所有的内存空间，包括Queue, Q->Array
 */
void DisposeQueue( Queue Q );

/**
 * 初始化队列为空
 */
void MakeEmpty( Queue Q );

/**
 * 把X入队
 */
void Enqueue( ET_Queue X, Queue Q );

/**
 * 查看队列头部的一个元素值，不出队列
 */
ET_Queue Front( Queue Q );

/**
 * 出队一个元素
 */
ET_Queue Dequeue( Queue Q );

#endif  /* _Queue_h */
