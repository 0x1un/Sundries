#include <stdio.h>

#define SIZE 6

const char comp_c = '@';
const char player_c = 'O';

void reset_board(char board[][SIZE]);
void display(char board[][SIZE]);

int main()
{
	char board[SIZE][SIZE] = {0}; // create 6x6 reversi board
	char again = 0; // receive player input
	printf("\n>>>>>>>Reversi Started<<<<<<<\n\n");
	printf("You will be white - (%c), I will be black - (%c)\n\n", player_c, comp_c);
	printf("Select a square for your move by typing a digit for the row\nand a letter for the column with no spaces between.\n");

	printf("Good luck! Press ENter to start.\n");
	/* scanf("%c", &again); // read player input to again. */
	fflush(stdin); // clear the buffer
	reset_board(board);

	display(board);


	return 0;
}


void reset_board(char board[][SIZE])
{
	for (size_t row = 0; row < SIZE; ++row)
		for (size_t col = 0; col < SIZE; ++col)
		{
			board[row][col] = ' ';
		}

	size_t mid = SIZE / 2;
	board[mid-1][mid-1] = board[mid][mid] = player_c;
	board[mid-1][mid] = board[mid][mid-1] = comp_c;
}


void display(char board[][SIZE])
{
	char col_label = 'a';
	printf("\n");
	for (size_t col = 0; col < SIZE; ++col)
	{
		printf("   %c", (char)(col_label + col));
	}
	printf("\n");

	for (size_t row = 0; row < SIZE; ++row)
	{
		printf("  +");
		for (size_t col = 0; col < SIZE; ++col)
		{
			printf("---+");
		}
		printf("\n%2zd|", row+1);
	

		for (size_t col = 0; col < SIZE; ++col)
		{
			printf(" %c |", board[row][col]);
		}
		printf("\n");

	}

	printf("  +");
	for (size_t col = 0; col < SIZE; ++col)
	{
		printf("---+");
	}
	printf("\n");
}
