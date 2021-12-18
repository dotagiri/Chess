#include <stdio.h>
#include <stdlib.h>

#include "conversion.h"
#include "board.h"
#include "moves.h"

int conversion_x(char x_value)
{	
	switch(x_value)
	{
		case 'a':
			return 0;
			break;
		case 'b':
			return 1;
			break;
		case 'c':
			return 2;
			break;
		case 'd':
			return 3;
			break;
		case 'e':
			return 4;
			break;
		case 'f':
			return 5;
			break;
		case 'g':
			return 6;
			break;
		case 'h':
			return 7;
			break;
		default:
			return 10;
			break;
	}	
		

}
	
int conversion_y(char y_value)
{
	switch(y_value)
	{
		case '8':
			return 0;
			break;
		case '7':
			return 1;
			break;
		case '6':
			return 2;
			break;
		case '5':
			return 3;
			break;
		case '4':
			return 4;
			break;
		case '3':
			return 5;
			break;
		case '2':
			return 6;
			break;	
		case '1':
			return 7;
			break;
		default:
			return 10;
			break;
	}	

}

void getAndConvertChessPos(const char* description, int* arrayRow, int* arrayCol)
{
	char chessCol;
	int chessRow;

	do {	
		printf("%s", description);
		
		scanf("%c%d", &chessCol, &chessRow);

		while (getchar() != '\n');
	} while (convertChess2Array(arrayRow, arrayCol, chessCol, chessRow) == 0);
}

int checkValidSelection(const int turn, int board[8][8], const int row, const int col)
{
	if (turn % 2 == 0){
		if (board[row][col] <= 0){
			printf("Please choose a white piece.\n");
			return 0;
		}
	}

	else if (turn % 2 == 1){
		if (board[row][col] >= 0){
			printf("Please choose a black piece.\n");
			return 0;
		}
	}

	return 1;
}

int a = 0;		//checking to see if checkmate occured or not (a=1 -> checkmate)

int playerVSplayer(void)
{
	//need to make the board first
	FILE* fp = fopen("log.txt", "w+");
	fclose(fp);

	int currCol, currRow, nextCol, nextRow;

	printf("PVP mode started\n"); 	

	int board[8][8] = {{-1,-2,-3,-4,-5,-3,-2,-1},
  			   {-6,-6,-6,-6,-6,-6,-6,-6},
 			   { 0, 0, 0, 0, 0, 0, 0, 0},
  			   { 0, 0, 0, 0, 0, 0, 0, 0},
  			   { 0, 0, 0, 0, 0, 0, 0, 0},
  			   { 0, 0, 0, 0, 0, 0, 0, 0},
  			   { 6, 6, 6, 6, 6, 6, 6, 6},
  			   { 1, 2, 3, 4, 5, 3, 2, 1}};
	displayBoard(board);


	int turn = 0;	//turn counter  to see whose turn it is
	int legality = 0;
	//int test = 0;

	while (1)
	{	
		if (turn % 2 == 0){
			printf("\n*** WHITE'S TURN ***\n");
		}

		else if (turn % 2 == 1){
			printf("\n*** BLACK'S TURN ***\n");
		}
		
		do {
			getAndConvertChessPos("Enter the position of the piece you want to move: ", &currRow, &currCol);
		} while (checkValidSelection(turn, board, currRow, currCol) == 0);

		getAndConvertChessPos("Enter the position you want to move to: ", &nextRow, &nextCol);

		//illegal is zero
		//legal is one

		legality = move( board, currRow, currCol, nextRow, nextCol);

		if(legality == 0)
		{
			continue;
		}
			
		++turn;			
			
		displayBoard(board);
				
		chessOutput(board[nextRow][nextCol], colIndex2ColLetter(currCol), arrayRow2ChessRow(currRow), colIndex2ColLetter(nextCol), arrayRow2ChessRow(nextRow));
		
		a = checkmate (board);
		if (a == 1)
			return 0;
	}
	

	return 0;
}
