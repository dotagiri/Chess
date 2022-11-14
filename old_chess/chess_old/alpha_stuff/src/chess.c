#include <stdio.h>
#include <stdlib.h>

//this is the main function for producing the chess game

int main(void)
{
	/* the board is a 8x8 board with number values representing the pieces
 *
 *
 * 	it will look like board[8][8] = {{-1,-2,-3,-4,-5,-3,-2,-1},
 * 					 {-6,-6,-6,-6,-6,-6,-6,-6},
 * 					 { 0, 0, 0, 0, 0, 0, 0, 0},
 * 					 { 0, 0, 0, 0, 0, 0, 0, 0},
 * 					 { 0, 0, 0, 0, 0, 0, 0, 0},
 * 					 { 0, 0, 0, 0, 0, 0, 0, 0},
 * 					 { 6, 6, 6, 6, 6, 6, 6, 6},
 * 					 { 1, 2, 3, 4, 5, 3, 2, 1}};
				
					in this board:
					rook = 1
					knight = 2
					bishop = 3
					queen = 4
					king = 5
					pawns = 6
					if the peices are black it is a negative number instead of the same magnitude


	*/
	
	int board[8][8] = {{-1,-2,-3,-4,-5,-3,-2,-1},
  			   {-6,-6,-6,-6,-6,-6,-6,-6},
 			   { 0, 0, 0, 0, 0, 0, 0, 0},
  			   { 0, 0, 0, 0, 0, 0, 0, 0},
  			   { 0, 0, 0, 0, 0, 0, 0, 0},
  			   { 0, 0, 0, 0, 0, 0, 0, 0},
  			   { 6, 6, 6, 6, 6, 6, 6, 6},
  			   { 1, 2, 3, 4, 5, 3, 2, 1}};

	//printf("this is the value of the rook %d\n", board[7][7]);

	char s;

	int x,y;

	int initial_x, initial_y;
	
	int end_x, end_y;


	printf("Choose the game type\n");
	printf("Type p for pvp and c for pvc:");
	scanf("%c", &s);

	if (s == 'p')
	{
		printf("Player v player move started!!\n");
		
		while(1)
		{
			for( x = 0; x < 8; x++)
			{
				for( y = 0; y < 8; y++)
				{
					printf("%d ", board[x][y]);
				}
				printf("\n");
	
			}	
		
			printf("Enter the x y coordinates of the peice you want to move(in the form \" x y\": ");
			
			scanf("%d %d", &initial_x, &initial_y);

			printf("Enter the x y coordinates of the place you want the peice to end up( in teh form \" x y \": ");

			scanf("%d %d", &end_x, &end_y);


			board[end_y-1][end_x-1] = board[initial_y-1][initial_x-1];
			
			board[initial_y-1][initial_x-1] = 0;
				
		
		}

	}	
	else if ( s == 'c')
	{
		printf("Sorry computer mode has not been created yet :( \n");
	}	














}
