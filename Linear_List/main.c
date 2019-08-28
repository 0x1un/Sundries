#include <stdio.h>

#define LIST_SIZE 100

typedef struct SeqList 
{
	int data[LIST_SIZE];
	int length;
}SeqList;

void InsertList( SeqList *L, int i, int x )
{
	int j;
	if ( i < 1 || (i > L->length+1) )
		{
			printf("postition error");
			return;
		}
	if ( L->length >= LIST_SIZE )
	{
		printf("overflow");
		return;
	}

	for ( j=L->length-1; j >= i-1; j-- )
	{
		L->data[j+1] = L->data[j];
	}
	L->data[i-1] = x;
	L->length++;
}

int main(void)
{
	
	

	return 0;
}
