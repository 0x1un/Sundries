#include <stdio.h>
#include <stdlib.h>
#include "heapSort.h"
int main()
{
	int array[] = {12, 9, 4, 48, 9, 6};
	int n = sizeof(array) / sizeof(array[0]);

	printArray(array, n);

	heapSort(array, n);
	int teset;

	printf("Sorted array is: \n");
	printArray(array, n);



	return 0;
}

void swap(int *array, const int i, const int j)
{
	int temp;
	temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}




void heapAdjust(int* array, int n, int i)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if ( left < n && array[left] > array[largest] )
	{
		largest = left;
	}
	if ( right < n && array[right] > array[largest] )
	{
		largest = right;
	}
	if ( largest != i )
	{
		swap(array, i, largest);
		heapAdjust(array, n, largest);
	}
}

void heapSort(int* array, const int n)
{
	for( int i=n/2-1; i>=0; i-- )
	{
		heapAdjust(array, n, i);
	}
	for( int i=n-1;i>=0; i-- )
	{
		swap(array, 0, i);
		heapAdjust(array, i, 0);
	}
}


void printArray(int* array, const int n)
{
	for( int i=0; i<n; ++i )
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}
