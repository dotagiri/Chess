// conversion.c

#include <stdio.h>
#include "conversion.h"

int convertChess2Array(int* arrayRow, int* arrayCol, char colLetter, int rowNum)
{
	if (checkChessColBounds(colLetter) == 1 && checkChessRowBounds(rowNum) == 1){
		*arrayRow = 8 - rowNum;
		*arrayCol = colLetter2ColIndex(colLetter);
		return 1;
	} 
	
	else {
		return 0;
	}
}

int checkChessRowBounds(int rowNum)
{
	if (rowNum >= 1 && rowNum <= 8){
		return 1;
	}

	else {
		printf("Chess row out of bounds.\n");
		return 0;
	}
}

int checkChessColBounds(char colLetter)
{
	if (colLetter >= 97 && colLetter <= 104){
		return 1;
	}

	else {
		printf("Chess column out of bounds.\n");
		return 0;
	}
}

int colLetter2ColIndex(char colLetter)
{
	switch(colLetter){
		case 'a':
			return 0;
		case 'b':
			return 1;
		case 'c':
			return 2;
		case 'd':
			return 3;
		case 'e':
			return 4;
		case 'f':
			return 5;
		case 'g':
			return 6;
		case 'h':
			return 7;
		default:
			return 8;
	}
}

char colIndex2ColLetter(int colIndex)
{
	switch(colIndex){
		case 0:
			return 'a';
		case 1:
			return 'b';
		case 2:
			return 'c';
		case 3:
			return 'd';
		case 4:
			return 'e';
		case 5:
			return 'f';
		case 6:
			return 'g';
		case 7:
			return 'h';
		default:
			return '\0';
	}
}

int arrayRow2ChessRow(int rowNum)
{
	switch(rowNum){
		case 0:
			return 8;
		case 1:
			return 7;
		case 2:
			return 6;
		case 3:
			return 5;
		case 4:
			return 4;
		case 5:
			return 3;
		case 6:
			return 2;
		case 7:
			return 1;
		default:
			return 0;
	}
}
