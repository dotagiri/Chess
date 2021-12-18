// special_moves.c

#include <stdio.h>
#include "conversion.h"
#include "special_moves.h"

void EnPassant(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol)
{

}

void castleKingSide(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol)
{

}

void castleQueenSide(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol)
{

}

void whitePawnPromotion(int board[8][8])
{
	for (unsigned int i = 0; i < 8; ++i){
		if (board[0][i] == 6){
			printf("*** White Pawn Promotion! ***\n");
			board[0][i] = choosePiece(board, 0, i);		
		}
	}
}

void blackPawnPromotion(int board[8][8])
{
	for (unsigned int i = 0; i < 8; ++i){
		if (board[7][i] == -6){
			printf("*** Black Pawn Promotion! ***\n");
			board[7][i] = -choosePiece(board, 7, i);		
		}
	}
}

int choosePiece(int board[8][8], int row, int col)
{
	char chosenPiece = '\0';
	
	do {
		printf("Select a piece to replace your Pawn at %c%d (Q - queen, R - rook, B - bishop, N - knight): ", colIndex2ColLetter(col), arrayRow2ChessRow(row));

	scanf("%c", &chosenPiece);
	} while (chosenPiece != 'Q' || chosenPiece != 'R' || chosenPiece != 'B' || chosenPiece != 'N');

	return newPiece(chosenPiece);
}

int newPiece(char piece)
{
	switch (piece){
		case 'Q':
			return 4;
		case 'R':
			return 1;
		case 'B':
			return 3;
		case 'N':
			return 2;
		default:
			return 0;
	}
}
