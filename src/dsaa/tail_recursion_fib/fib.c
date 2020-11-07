#include <stdio.h>
/**
 * 原文链接：https://www.zhihu.com/question/20761771 什么是尾递归
 */
 
/**
 * 树形递归
 * 最直观的递归
 * fib_1(n-3) 会在fib_1(n-1) & fib_1(n-2)中计算多次，结果没有相互利用

fib_1(5)展开过程是:
fib_1(4) + fib_1(3)
(fib_1(3)+fib_1(2)) + (fib_1(2)+fib_1(1))
((fib_1(2)+fib_1(1))+(fib_1(1)+fib_1(0))) + ((fib_1(1)+fib_1(0))+fib_1(1))
(((fib_1(1)+fib_1(0))+fib_1(1))+(fib_1(1)+fib_1(0))) + ((fib_1(1)+fib_1(0))+fib_1(1))

 */
int fib_1(int n)
{
	if (n <= 1)
		return 1;
	else
		return fib_1(n-1) + fib_1(n-2);
}

/**
 * 线性递归
 *
fib_2(5)展开过程是:

fib_rec(1,1,5)
1+fib_rec(1,2,4)
1+(1+fib_rec(2,3,3))
1+(1+(2+fib_rec(3,5,2)))
1+(1+(2+(3+fib_rec(5,8,1))))
1+(1+(2+(3+1)))
8
 */
int fib_2(int n)
{
	int fib_rec(int a, int b, int n) {
		if (n <= 1)
			return 1;
		else
			return a + fib_rec(b, a+b, n-1);
	}
	return fib_rec(1, 1, n);
}

/**
 * 尾递归
 * 尾递归比线性递归多一个参数，这个参数是上一次调用函数得到的结果
 * 关键点在于，尾递归每次调用都在收集结果，避免了
 * 线性递归不收集结果只能依次展开消耗内存的坏处。
 *
 * 尾递归形式和循环(或者说"迭代")形式大致就是同一个逻辑的两种表达形式而已。
 * 尾递归代码和循环的代码的执行效率基本上是相当的，
 * 尾递归优化主要是对栈内存空间的优化, 这个优化是O(n)到O(1)的; 至于时间的优化，
 * 其实是由于对空间的优化导致内存分配的工作减少所产生的, 是一个常数优化, 不会带来质的变

fib_3(5)展开过程是:
fib_iter(1,1,5)
fib_iter(1,2,4)
fib_iter(2,3,3)
fib_iter(3,5,2)
fib_iter(5,8,1)
fib_iter(8,13,0)=8
 */
int fib_3(int n)
{
	int fib_iter(int a, int b, int n) {
		if (n == 0)
			return a;
		else
			return fib_iter(b, a+b, n-1);
	}
	return fib_iter(1, 1, n);
}

/**
 * 迭代实现(循环)
 */
int fib_4(int n)
{
	int a=1, b=1;
	int i;
	for (i=0; i<n; ++i) {
		int a_ = b, b_ = a+b;
		a = a_;
		b = b_;
	}
	return a;
}

int main(void)
{
	int n = 5;
	printf("fib_1(%d) = %d\n", n, fib_1(n));
	printf("fib_2(%d) = %d\n", n, fib_2(n));
	printf("fib_3(%d) = %d\n", n, fib_3(n));
	printf("fib_4(%d) = %d\n", n, fib_4(n));
	return 0;
}
