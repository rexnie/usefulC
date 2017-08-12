#include "ds.h"
#include <limits.h>

/**
 * 2.12a 最小子序列和问题
 */
static int Min3( int A, int B, int C )
{
	return A > B ? (B > C ? C : B) : (A > C ? C : A);
}

/**
 * 递归算法，采用分治(divide-and-conquer)策略
 * 时间复杂度为 O(N*logN)
 * 注意事项：
 * 1. 别重复算边界, 包括
 *   @1和@2刚好构成，[Left,Right],
 *   @3和@4刚好构成，[Left,Right],
 * 2. @3,@4的起始循环位置是有讲究的，必须从中间开始
 */
static int MinSubSum( const int A[ ], int Left, int Right )
{
	int minLeftSum, minRightSum;
	int minLeftBorderSum, minRightBorderSum;
	int LeftBorderSum, RightBorderSum;
	int Center, i;

	if( Left == Right )  /* Base case, 只有一个元素的子序列 */
		if( A[ Left ] < 0 ) /* <0 即纳入和 */
			return A[ Left ];
		else
			return 0;

	Center = ( Left + Right ) / 2;
/* @1*/	minLeftSum = MinSubSum( A, Left, Center ); /* 递归求解前半部分 */
/* @2*/	minRightSum = MinSubSum( A, Center + 1, Right ); /* 递归求解后半部分 */

	minLeftBorderSum = INT_MAX; LeftBorderSum = 0;
/* @3*/	for( i = Center; i >= Left; i-- ) /* 求解左半部分最小和，包括Center/Left边界
					    i 的起始位置一定是Center开始，不是Left开始,
					    因为要跨越中间的位置，最小和必须包括Center */
	{
		LeftBorderSum += A[ i ];
		if( LeftBorderSum < minLeftBorderSum )
			minLeftBorderSum = LeftBorderSum;
	}

	minRightBorderSum = INT_MAX; RightBorderSum = 0;
/* @4*/	for( i = Center + 1; i <= Right; i++ ) /* 求解右半部分最小和，包括Center+1/Right边界
					    i 的起始位置一定是Center+1开始，不是Right开始 */
	{
		RightBorderSum += A[ i ];
		if( RightBorderSum < minRightBorderSum )
			minRightBorderSum = RightBorderSum;
	}

	return Min3( minLeftSum, minRightSum,
			minLeftBorderSum + minRightBorderSum ); /* 跨越中间的，[Left, Right] 最小和*/
}

int MinSubsequenceSum1( const int A[ ], int N )
{
	/*可以在这里判断输入数据的合理性，避免影响算法*/
	if (N <= 0) {
		err("N must be >=1\n");
		exit(1);
	}
	return MinSubSum( A, 0, N - 1 );
}

/**
 * 时间复杂度为 O(N)
 */
int MinSubsequenceSum2(const int a[], int n)
{
	int thisSum, minSum, j;

	thisSum = 0;
	minSum = INT_MAX;

	for (j = 0; j < n; j++) {
		thisSum += a[j];
		if (thisSum < minSum)
			minSum = thisSum;
		else if (thisSum > 0)
			thisSum = 0;
	}
	return minSum;
}

/**
 * 2.12b 最小正子序列和问题
 */
int MinPositiveSubsequenceSum(const int a[], int n)
{
	int thisSum, minSum, j;

	thisSum = 0;
	minSum = INT_MAX;

	for (j = 0; j < n; j++) {
		if (a[j] > 0) {
			thisSum += a[j];
		} else {
			if (thisSum > 0 && thisSum < minSum)
				minSum = thisSum;
			thisSum = 0;
		}
	}
	return minSum;
}

int main(void)
{
	int i, *ptr;
	int min = -100, max = 100, n = 20;

	if ((ptr = get_nums_list_in_range(n ,min, max)) != NULL) {
		for (i = 0; i < n; i++)
			printf("%d ", ptr[i]);
		printf("\n");
		printf( "minSum = %d\n", MinSubsequenceSum1( ptr, n));
		printf( "minSum = %d\n", MinSubsequenceSum2( ptr, n));
		printf( "minPositiveSum = %d\n", MinPositiveSubsequenceSum( ptr, n));
		free_nums_list(ptr);
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}
