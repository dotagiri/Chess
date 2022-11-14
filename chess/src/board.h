// board.h

#ifndef BOARD_H
#define BOARD_H

void pieceRep(const int piece, char* representation);

void displayRow(int board[8][8], const int row);

void displayBoard(int board[8][8]);

void chessOutput(const int piece, const char prevChessCol, const int prevChessRow, const char newChessCol, const int newChessRow);

void write2Log(const int piece, const char prevChessCol, const int prevChessRow, const char newChessCol, const int newChessRow);

#endif
