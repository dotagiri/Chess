#ifndef MOVES_H
#define MOVES_H

/* moves a piece from one location on the board to the next */
int move(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

/* check whether a move is legal */
int checkLegal(int piece,int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

/* check the legality of the pawn move */
int checkPawn(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

/* check the legality of the rook move */
int checkRook(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

/* check the legality of the bishop move */
int checkBishop(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

/* check the legality of the knight move */
int checkKnight(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

/* check the legality of the queen move */
int checkQueen(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

/* check the legality of the king move */
int checkKing(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

/* check whether the king is in check */
int check4Check(int board[8][8]);

/* check whether it is a checkmate situation */
int checkmate(int board[8][8], int color, char piece);

/* check diagonal direction (used in checkBishop() and checkQueen()) */
int diagonalDirection(int prevRow, int prevCol, int nextRow, int nextCol);

/* check legality of diagonal move*/
int checkDiagonal(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

/* check blocked pieces in diagonally down to the right*/
int diagonalDownRightBlock(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

/* check blocked pieces in diagonally down to the left */
int diagonalDownLeftBlock(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

/* check blocked pieces in diagonally up to the left*/
int diagonalUpLeftBlock(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

/* check blocked pieces in diagonally up to the right*/
int diagonalUpRightBlock(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

/* check horizontal */
int checkHorizontal(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

/* check vertical */
int checkVertical(int board[8][8],int prevRow, int prevCol, int nextRow, int nextCol);

#endif
