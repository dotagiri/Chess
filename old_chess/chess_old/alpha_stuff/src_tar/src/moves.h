
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

/* function to capture opponent pieces */
void capture( int row, int col, int board[8][8]);

/* check whether the king is in check */
int check4Check(int board[8][8], int color, char piece);

/* check whether it is a checkmate situation */
int checkmate(int board[8][8], int color, char piece);

