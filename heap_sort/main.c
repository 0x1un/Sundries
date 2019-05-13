#include <stdio.h>
#include <stdlib.h>

void heapSort(int* array, const int n);
void heapAdjust(int* array, int n, int i);
void swap(int* a, int* b);
void printArray(int *array, const int n);

int main()
{
	int array[] = {32, 0, 1, 0, 43, 99, 100, 0, 4, 9, 2, 1, 4, 9, 5, 3, 4};

	int n = sizeof(array) / sizeof(array[0]);

	heapSort(array, n);

	printArray(array, n);
	

	return 0;
}


void swap(int* a, int* b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}


void heapAdjust(int* array, int n, int i)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if ( left < n && array[i] < array[left] )
	{
		largest = left;
	}
	if ( right < n && array[largest] < array[right] )
	{
		largest = right;

	}
	if ( largest != i )
	{
		swap(&array[i], &array[largest]);
		heapAdjust(array, n, largest);
	}
}

void heapSort(int* array, const int n)
{
	for( int i=n; i>=0; i-- )
	{
		heapAdjust(array, n, i);
	}
	for( int i=n-1; i>=0; i-- )
	{
		swap(&array[i], &array[0]);
		heapAdjust(array, i, 0);
	}
}


void printArray(int* array, const int n)
{
	for( int i=0; i<n; i++ )
	{
		printf("%d ", array[i]);
	}
}
