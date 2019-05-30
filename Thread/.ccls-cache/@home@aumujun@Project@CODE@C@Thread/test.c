#include <stdio.h>

add(int a, int b)
{
	return a + b;
}

int main()
{
	int a = 23;
	void *pvoid;
	
	void *p1 = &a;
	printf("add : %d\n", add(1, 2));

	printf("%d\n", *(int *)p1);
	printf("%p\n", pvoid);
	pvoid++;
	printf("%p\n", pvoid);

}
