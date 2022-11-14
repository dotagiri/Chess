// board.c

#include <stdio.h>
#include <stdlib.h>

#include "board.h"


const char pieceLetter[8] = {' ', 'R', 'N', 'B', 'Q', 'K', 'P', '\0'};
const char pieceName[7][7] = {" ", "Rook", "Knight", "Bishop", "Queen", "King", "Pawn"};


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


void chessOutput(const int piece, const char prevChessCol, const int prevChessRow, const char newChessCol, const int newChessRow)
{
	printf("*** %s at %c%d moved to %c%d. ***\n", pieceName[abs(piece)], prevChessCol, prevChessRow, newChessCol, newChessRow);

	write2Log(piece, prevChessCol, prevChessRow, newChessCol, newChessRow);
}


void write2Log(const int piece, const char prevChessCol, const int prevChessRow, const char newChessCol, const int newChessRow)
{
	FILE* fp = fopen("log.txt", "a");

	if (piece > 0){
		fprintf(fp, "%c%c    %c%d -> %c%d\n", 'w', pieceLetter[abs(piece)], prevChessCol, prevChessRow, newChessCol, newChessRow);
	}

	else if (piece < 0){
		fprintf(fp, "%c%c    %c%d -> %c%d\n\n", 'b', pieceLetter[abs(piece)], prevChessCol, prevChessRow, newChessCol, newChessRow);
	}

	fclose(fp);
}
