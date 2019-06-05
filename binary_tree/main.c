#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct Node
{
	long item;
	int count;
	struct Node *pLeft;
	struct Node *pRight;
} Node;

Node *create_node(long value);
Node *add_node(long value, Node * pNode);

void list_nodes(Node *pNode);


int main(void)
{
	long newValue;
	char anwser = 'n';
	Node *pNode = NULL;
	int count = 0;

	/* printf("item: %ld, count: %d, pLeft: %s, pRight: %s\n", pRoot->item, pRoot->count, pRoot->pLeft, pRoot->pRight); */
	do 
	{
		printf("Please enter a number to create Binary tree node: ");
		scanf("%ld", &newValue);

		if ( !pNode )
		{
			pNode = create_node(newValue);
		}
		else
		{
			add_node(newValue, pNode);
		}

		printf("Do you want to enter another node? (Y or N): ");
		scanf(" %c", &anwser);
		count++;
	} while( tolower(anwser) == 'y' );


	list_nodes(pNode);
	free(pNode);
	return 0;
}



Node *create_node(long value)
{
	Node *pNode = (Node*)malloc(sizeof(Node));
	pNode->item = value;
	pNode->count = 1;
	pNode->pLeft = pNode->pRight = NULL;
	return pNode;
}

Node *add_node(long value, Node * pNode)
{
	if ( !pNode ) // if pNode is NULL; so create the node
		return create_node(value);

	if ( value == pNode->item ) // if value and node.item are the same, plus one on the node.count
	{
		++pNode->count;
		return pNode;
	}

	if ( value < pNode->item ) // if the value less than node.item, let value to be left node
	{
		if ( !pNode->pLeft )
		{
			pNode->pLeft = create_node(value);
			return pNode->pLeft;
		}
		else
		{
			return add_node(value, pNode->pLeft);
		}
	}
	else
	{
		if ( !pNode->pRight )
		{
			pNode->pRight = create_node(value);
			return pNode->pRight;
		}
		else
		{
			return add_node(value, pNode->pRight);
		}
	}

}

void list_nodes(Node *pNode)
{
	if ( pNode->pLeft )
	{
		list_nodes(pNode->pLeft);
	}
	printf("count: %10d x pNode->item: %10ld\n", pNode->count, pNode->item); // output the current node value 

	if ( pNode -> pRight )
	{
		list_nodes(pNode -> pRight);
	}
}
