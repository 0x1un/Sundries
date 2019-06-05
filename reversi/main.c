#include <stdio.h>
#include "public.h"

extern const char comp_c;
extern const char player_c;

extern void display(char board[][SIZE]);
extern void reset_board(char board[][SIZE]);


int main()
{
	char board[SIZE][SIZE] = {}; // create 6x6 reversi board
	char again = 0; // receive player input
	printf("\n>>>>>>>Reversi Started<<<<<<<\n\n");
	printf("You will be white - (%c), I will be black - (%c)\n\n", player_c, comp_c);
	printf("Select a square for your move by typing a digit for the row\nand a letter for the column with no spaces between.\n");

	printf("Good luck! Press ENter to start.\n");
	scanf("%c", &again); // read player input to again.
	fflush(stdin); // clear the buffer
	reset_board(board);

	display(board);


	return 0;
}



