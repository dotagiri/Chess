// special_moves.h

#ifndef SPECIAL_MOVES_H
#define SPECIAL_MOVES_H

void EnPassant(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

void castleKingSide(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

void castleQueenSide(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

void whitePawnPromotion(int board[8][8]);

void blackPawnPromotion(int board[8][8]);

int choosePiece(int board[8][8], int row, int col);

int newPiece(char piece);

#endif
