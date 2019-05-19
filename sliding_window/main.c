#include <stdio.h>


int max(const int a, const int b)
{
	return a > b?a:b;
}


/*
 * 以k为块区域向右移动一个位置, 相加其k区域中的所有值, 循环遍历整个列表
 * 最终返回遍历过程当中最大和.
 * */
int slidingWindow(int *array, const int n, const int k)
{
	if (n < k)
	{
		printf("Invalid\n");
		return -1;
	}

	int max_sum = 0;
	for(int i=0; i < k; i++)
		max_sum += array[i];
	int windows_sum = max_sum;
	for(int i=k; i<n; i++)
	{
		/*
		 * [3, 2, 4, 5], k = 2
		 * |   | => 5;
		 *     |  | => 6; 相当于 5减去第一个值, 加上k+1的值
		 *        |  | => 6 - 2 + 5; 9 
		 * 其中9在遍历过程中最大, 将其返回
		 * */
		windows_sum += array[i] - array[i - k];
		max_sum = max(max_sum, windows_sum);
	}

	return max_sum;
}

int main()
{
	int array[] = {1, 4, 2, 10, 23, 3, 1, 0, 20};
	int n = sizeof(array) / sizeof(array[0]);
	printf("%d\n", slidingWindow(array, n, 4));
	return 0;
}
