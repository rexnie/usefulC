#ifndef __STACK_ARRAY_H__
#define __STACK_ARRAY_H__

typedef int ElementType;
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
void Push( ElementType X, Stack S );

/**
 * 查看栈顶元素，不弹出栈 
 */
ElementType Top( Stack S );

/**
 * 弹出栈顶元素
 */
ElementType Pop( Stack S );

#endif
