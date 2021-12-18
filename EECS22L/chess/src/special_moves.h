// special_moves.h

#ifndef SPECIAL_MOVES_H
#define SPECIAL_MOVES_H

int whiteEnPassant(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

int blackEnPassant(int board[8][8], int prevRow, int prevCol,  int nextRow, int nextCol);

int castleKingSide(int board[8][8], const int currRow, const int currCol, const int nextRow, const int nextCol);

int castleQueenSide(int board[8][8], const int currRow, const int currCol, const int nextRow, const int nextCol);

void whitePawnPromotion(int board[8][8]);

void blackPawnPromotion(int board[8][8]);

int choosePiece(int board[8][8], const int row, const int col);

int newPiece(const char piece);

#endif
