#include <stdio.h>
#include <stdlib.h>
/**
 * 最大子序列和问题
 */

// 定义其中一个宏选择测试算法
//#define CubicAlgorithm
//#define QuadraticAlgorithm
//#define NlogNAlgorithm
#define LinearAlgorithm

#ifdef CubicAlgorithm

/* START: fig2_5.txt */
/**
 * 枚举所有可能的组合序列
 * 时间复杂度为 O(n*n*n)
 */
int MaxSubsequenceSum( const int A[ ], int N )
{
	int ThisSum, MaxSum, i, j, k;

	MaxSum = 0;
	for( i = 0; i < N; i++ ) /* 以a[i]为起始点 */
		for( j = i; j < N; j++ ) /* 枚举所有可能长度的子序列 */
		{
			ThisSum = 0;
			for( k = i; k <= j; k++ ) ThisSum += A[ k ]; /* 求和 */
			if( ThisSum > MaxSum )
				MaxSum = ThisSum;
		}
	return MaxSum;
}
/* END */

#endif


#ifdef QuadraticAlgorithm

/**
 * 枚举所有可能的组合序列
 * 时间复杂度为 O(n*n)
 */
/* START: fig2_6.txt */
int MaxSubsequenceSum( const int A[ ], int N )
{
	int ThisSum, MaxSum, i, j;

	MaxSum = 0;
	for( i = 0; i < N; i++ ) /* 以a[i]为起始点 */
	{
		ThisSum = 0;
		for( j = i; j < N; j++ ) /* 在枚举所有可能长度的子序列的过程中，记录最大的和
					    去除了一个单独求和的for循环 */
		{
			ThisSum += A[ j ];

			if( ThisSum > MaxSum )
				MaxSum = ThisSum;
		}
	}
	return MaxSum;
}
/* END */

#endif



#ifdef NlogNAlgorithm

static int Max3( int A, int B, int C )
{
	return A > B ? A > C ? A : C : B > C ? B : C;
}

/* START: fig2_7.txt */
/**
 * 递归算法，采用分治(divide-and-conquer)策略
 * 时间复杂度为 O(N*logN)
 * 注意事项：
 * 1. 别重复算边界, 包括
 *   @1和@2刚好构成，[Left,Right],
 *   @3和@4刚好构成，[Left,Right],
 * 2. @3,@4的起始循环位置是有讲究的，必须从中间开始
 */
static int MaxSubSum( const int A[ ], int Left, int Right )
{
	int MaxLeftSum, MaxRightSum;
	int MaxLeftBorderSum, MaxRightBorderSum;
	int LeftBorderSum, RightBorderSum;
	int Center, i;

	if( Left == Right )  /* Base case, 只有一个元素的子序列 */
		if( A[ Left ] > 0 ) /* >0 即纳入和 */
			return A[ Left ];
		else
			return 0;

	Center = ( Left + Right ) / 2;
/* @1*/	MaxLeftSum = MaxSubSum( A, Left, Center ); /* 递归求解前半部分 */
/* @2*/	MaxRightSum = MaxSubSum( A, Center + 1, Right ); /* 递归求解后半部分 */

	MaxLeftBorderSum = 0; LeftBorderSum = 0;
/* @3*/	for( i = Center; i >= Left; i-- ) /* 求解左半部分最大和，包括Center/Left边界
					    i 的起始位置一定是Center开始，不是Left开始,
					    因为要跨越中间的位置，最大和必须包括Center */
	{
		LeftBorderSum += A[ i ];
		if( LeftBorderSum > MaxLeftBorderSum )
			MaxLeftBorderSum = LeftBorderSum;
	}

	MaxRightBorderSum = 0; RightBorderSum = 0;
/* @4*/	for( i = Center + 1; i <= Right; i++ ) /* 求解右半部分最大和，包括Center+1/Right边界
					    i 的起始位置一定是Center+1开始，不是Right开始 */
	{
		RightBorderSum += A[ i ];
		if( RightBorderSum > MaxRightBorderSum )
			MaxRightBorderSum = RightBorderSum;
	}

	return Max3( MaxLeftSum, MaxRightSum,
			MaxLeftBorderSum + MaxRightBorderSum ); /* 跨越中间的，[Left, Right] 最大和*/
}

int MaxSubsequenceSum( const int A[ ], int N )
{
	/*可以在这里判断输入数据的合理性，避免影响算法*/
	if (N <= 0) {
		printf("N must be >=1\n");
		exit(1);
	}
	return MaxSubSum( A, 0, N - 1 );
}
/* END */


#endif


#ifdef LinearAlgorithm
/* START: fig2_8.txt */

/**
 * 时间复杂度为 O(N)
 */
int MaxSubsequenceSum( const int A[ ], int N )
{
	int ThisSum, MaxSum, j;

	ThisSum = MaxSum = 0;
	for( j = 0; j < N; j++ )
	{
		ThisSum += A[ j ];

		if( ThisSum > MaxSum ) /* 出现更大的子序列和，记录下来 */
			MaxSum = ThisSum;
		else if( ThisSum < 0 ) /* < 0, 重新开始一个子序列，之前的子序列不能纳入下一个子序列 */
			ThisSum = 0;
	}
	return MaxSum;
}
/* END */

#endif

main( )
{
	static int A[ ] = { 4, -3, 5, -2, -1, 2, 6, -2 };

	printf( "Maxsum = %d\n",
			MaxSubsequenceSum( A, sizeof( A ) / sizeof( A[ 0 ] ) ) );
	return 0;
}
