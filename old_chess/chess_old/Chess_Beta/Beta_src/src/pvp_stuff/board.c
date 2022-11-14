// board.c

#include <stdio.h>
#include <stdlib.h>

#include "board.h"

const char pieceLetter[8] = {' ', 'R', 'N', 'B', 'Q', 'K', 'P', '\0'};
const char pieceName[7][7] = {" ", "Rook", "Knight", "Bishop", "Queen", "King", "Pawn"};
const char colLetter[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

void pieceRep(const int piece, char* representation)
{
	if (piece > 0){
		representation[0] = 'w';
	}  

	else if (piece < 0){
		representation[0] = 'b';
	}

	else if (piece == 0){
		representation[0] = ' ';
	}

	representation[1] = pieceLetter[abs(piece)];
}

void displayRow(int board[8][8], const int row)
{
	char representation[3] = {' ', ' ', '\0'};

	printf("%d |", 8 - row);

	for (unsigned int i = 0; i < 8; ++i){
		pieceRep(board[row][i], representation);
		printf(" %s |", representation);
	}
}

void displayBoard(int board[8][8])
{
	for (unsigned int i = 0; i < 8; ++i){
		printf("  +----+----+----+----+----+----+----+----+\n");
		displayRow(board, i);
		printf("\n");
	}

	printf("  +----+----+----+----+----+----+----+----+\n");
	printf("    a    b    c    d    e    f    g    h   \n"); 

}

void write2Log(int piece, const int prevRow, const int prevCol, const int currRow, const int currCol)
{
	printf("%s at %c%d moved to %c%d\n", pieceName[piece], colLetter[prevCol], prevRow + 1, colLetter[currCol], currRow + 1);
}
