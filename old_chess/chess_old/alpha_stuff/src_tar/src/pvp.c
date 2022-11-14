#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "moves.h"

int playerVSplayer(void)
{
	//need to make the board first


	int initial_x, initial_y;
	
	int end_x, end_y;



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



	

	while(1)
	{

	
		printf("Enter the x y coorrdinates of the peice you want to move(in the form \" x y\": ");
				
		scanf("%d %d", &initial_x, &initial_y);

		printf("Enter the x y coordinates of the place you want the peice to end up( in the form \" x y \": ");

		scanf("%d %d", &end_x, &end_y);

		move( board, initial_x, initial_y, end_x, end_y);

		displayBoard(board);
		
		write2Log(board[initial_x][initial_y], initial_x , initial_y, end_x, end_y);



	}


}
