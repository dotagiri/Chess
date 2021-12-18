// conversion.h

#ifndef CONVERSION_H
#define CONVERSION_H

int convertChess2Array(int* arrayRow, int* arrayCol, char colLetter, int rowNum);

int checkChessRowBounds(int rowNum);

int checkChessColBounds(char colLetter);

int colLetter2ColIndex(char colLetter);

char colIndex2ColLetter(int colIndex);

int arrayRow2ChessRow(int rowNum);

#endif
