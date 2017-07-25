#include <stdio.h>
/**
 * 最大子序列和问题
 */

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
static int MaxSubSum( const int A[ ], int Left, int Right )
{
	int MaxLeftSum, MaxRightSum;
	int MaxLeftBorderSum, MaxRightBorderSum;
	int LeftBorderSum, RightBorderSum;
	int Center, i;

	if( Left == Right )  /* Base case */
		if( A[ Left ] > 0 )
			return A[ Left ];
		else
			return 0;

	Center = ( Left + Right ) / 2;
	MaxLeftSum = MaxSubSum( A, Left, Center );
	MaxRightSum = MaxSubSum( A, Center + 1, Right );

	MaxLeftBorderSum = 0; LeftBorderSum = 0;
	for( i = Center; i >= Left; i-- )
	{
		LeftBorderSum += A[ i ];
		if( LeftBorderSum > MaxLeftBorderSum )
			MaxLeftBorderSum = LeftBorderSum;
	}

	MaxRightBorderSum = 0; RightBorderSum = 0;
	for( i = Center + 1; i <= Right; i++ )
	{
		RightBorderSum += A[ i ];
		if( RightBorderSum > MaxRightBorderSum )
			MaxRightBorderSum = RightBorderSum;
	}

	return Max3( MaxLeftSum, MaxRightSum,
			MaxLeftBorderSum + MaxRightBorderSum );
}

int MaxSubsequenceSum( const int A[ ], int N )
{
	return MaxSubSum( A, 0, N - 1 );
}
/* END */


#endif


#ifdef LinearAlgorithm
/* START: fig2_8.txt */
int MaxSubsequenceSum( const int A[ ], int N )
{
	int ThisSum, MaxSum, j;

	ThisSum = MaxSum = 0;
	for( j = 0; j < N; j++ )
	{
		ThisSum += A[ j ];

		if( ThisSum > MaxSum )
			MaxSum = ThisSum;
		else if( ThisSum < 0 )
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
