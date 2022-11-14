#include "aimoves.h"
#include "moves.h"

MLIST *getmoves(int board[8][8], MLIST *list, int color);


int board_evaluate(int board[8][8]);  


int piecevalue(int piece);


int **BoardCopy(int og[8][8], int **new1);

int checkmate2(int board[8][8],int color);
