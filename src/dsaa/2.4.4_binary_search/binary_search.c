#include <stdio.h>

typedef int ElementType;
#define NotFound (-1)

/* START: fig2_9.txt */
/**
 * 二分查找算法
 * 时间复杂度为 O(logN)
 */
int BinarySearch( const ElementType A[ ], ElementType X, int N )
{
	int Low, Mid, High;

	Low = 0; High = N - 1;
	while( Low <= High )
	{
		Mid = ( Low + High ) / 2;
		if( A[ Mid ] < X )
			Low = Mid + 1;
		else if( A[ Mid ] > X )
			High = Mid - 1;
		else
			return Mid;  /* Found */
	}
	return NotFound;     /* NotFound is defined as -1 */
}
/* END */

/**
 * 二分查找算法
 * 时间复杂度为 O(logN)
 * 时间可以大大缩小的版本
 * 减少了while 内的判断次数
 */
int binsearch2(ElementType x, const ElementType v[], int n)
{
	ElementType low, high, mid;

	low = 0;
	high = n - 1;
	while (low < high) {
		mid = (low + high) / 2;
		if (x <= v[mid])
			high = mid;
		else
			low = mid + 1;
	}
	return (x == v[low]) ? low : NotFound;
}

main( )
{
	static int A[ ] = { 1, 3, 5, 7, 9, 13, 15 };
	const int SizeofA = sizeof( A ) / sizeof( A[ 0 ] );
	int i;

	for( i = 0; i < 20; i++ ) {
		printf( "BinarySearch of %d returns %d\n",
				i, BinarySearch( A, i, SizeofA ) );
		printf( "BinarySearch2 of %d returns %d\n",
				i, binsearch2( i, A, SizeofA ) );
	}

	return 0;
}
