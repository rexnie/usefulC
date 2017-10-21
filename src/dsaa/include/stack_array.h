#ifndef __STACK_ARRAY_H__
#define __STACK_ARRAY_H__

typedef void* ET_Stack;

struct StackRecord;
typedef struct StackRecord *Stack;

int IsStackEmpty( Stack S );
int IsFull( Stack S );
Stack CreateStack( int MaxElements );

/**
 * 清除stack，释放Stack.Array, Stack内存
 */
void DisposeStack( Stack S );

/**
 * 设置Stack为空栈
 */
void MakeStackEmpty( Stack S );
void Push( ET_Stack X, Stack S );

/**
 * 查看栈顶元素，不弹出栈 
 */
ET_Stack Top( Stack S );

/**
 * 弹出栈顶元素
 */
ET_Stack Pop( Stack S );

/** 返回栈中元素的个数
 */
int NumOfElement( Stack S);

/**
 * 打印栈中的元素
 * 设置func为特定的打印回调函数，
 * 传递NULL,使用默认打印函数
 */
void DumpStack( Stack S, void (*func)(ET_Stack));
#endif
