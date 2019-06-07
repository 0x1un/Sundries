#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define SIZE 6

const char comp_c = '@';
const char player_c = 'O';

void reset_board(char board[][SIZE]);
void display(char board[][SIZE]);
int valid_moves(char board[][SIZE], bool moves[][SIZE], char player);
int player_counters(char board[][SIZE], char player);

int main()
{
	char board[SIZE][SIZE] = {}; // create 6x6 reversi board
	bool moves[SIZE][SIZE] = { false };

	int no_of_moves = 0;
	int invalid_moves = 0;
	bool next_player = true;
	char y = 0;
	size_t x = 0;

	char again = 0; // receive player input

	printf("\n>>>>>>>Reversi Started<<<<<<<\n\n");
	do
	{
		reset_board(board);
		next_player = !next_player;
		no_of_moves = 4;

		do
		{
			display(board);
			if( true == (next_player = !next_player) )
			{
				if ( valid_moves(board, moves, player_c) )
				{
					for( ;; )
					{
						printf("Please enter your move (row column - no space): ");
						scanf(" %zd%c", &x, &y);
						fflush(stdin);
						y = tolower(y) - 'a';
						--x;
						if( y < 0 || y >= SIZE || x >= SIZE || !moves[x][y] )
						{
							printf("Not a valid move, try again.\n");
							continue;
						}
						make_move(board, x, y, player_c);
						++no_of_moves;
						break;
					}
				}
				else
				{
					if ( ++invalid_moves < 2 )
					{
						printf("\nYou have to pass, press return");
						scanf("%c", &again);
						fflush(stdin);
					}
					else
					{
						printf("\nNeither of us can go, so the game is over.\n");
					}
				}
				else
				{
					if ( valid_moves(board, moves, comp_c) )
					{
						invalid_moves = 0;
						computer_move(board, moves, comp_c);
						++no_of_moves;
					}
					else
					{
						if( ++invalid_moves < 2 )
						{
							printf("\nI have to pass, your go\n");
						}
						else
						{
							printf("\nNeither of us can go, so the game is over.\n");
						}
					}
				}
			}
			
		}while( no_of_moves < SIZE*SIZE && invalid_moves < 2 );

		display(board);
		printf("The final score is:\n");
		printf("Computer %d\n User %d\n\n", player_counters(board, comp_c), player_counters(board, player_c));
		printf("Do you want to play again (y/n): ");
		scanf(" %c", &again);
		fflush(stdin);

	}while(tolower(again) == 'y');
	printf("\nGoodbye\n");


	return 0;
}

int player_counters(char board[][SIZE], char player)
{
	int count = 0;
	for( size_t row = 0; row < SIZE; ++row )
	{
		for( size_t col = 0; col < SIZE; ++col )
		{
			if ( board[row][col] == player )
				++count;
		}
	}
	return count;
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


int valid_moves(char board[][SIZE], bool moves[][SIZE], char player)
{
	int rowdelta = 0;
	int coldelta = 0;
	int x = 0, y = 0;
	int no_of_moves = 0;

	char opponent = (player == player_c) ? comp_c : player_c;

	for( size_t row = 0; row < SIZE; ++row )
	{
		for( size_t col = 0; col < SIZE; ++col )
		{
			moves[row][col] = false;
		}
	}
	for( size_t row = 0; row < SIZE; ++row )
	{
		for( size_t col = 0; col < SIZE; ++col )
		{
			if( board[row][col] != ' ' ) // If it's not a blank square...
			{
				continue; // go to the next
			}
			for( rowdelta = -1; rowdelta <= 1; ++rowdelta )
			{
				for( coldelta = -1; coldelta <= 1; ++coldelta )
				{
					if ( ( row == 0 && rowdelta == -1 ) || row + rowdelta >= SIZE || \
							(col == 0 && coldelta == -1) || col + coldelta >= SIZE || \
							(rowdelta == 0 && coldelta == 0))
					{
						continue;
					}
					if( board[row + rowdelta][col + coldelta] == opponent )
					{
						x = row + rowdelta;
						y = col + coldelta;
						for(;;)
						{
							x += rowdelta;
							y += coldelta;
							if( x < 0 || x >= SIZE || y < 0 || y >= SIZE || board[x][y] == ' ' )
							{
								break;
							}
							if( board[x][y] == player )
							{
								moves[row][col] = true;
								no_of_moves++;
								break;
							}
						}
					}
				}
			}
		}
	}
	return no_of_moves;
}
