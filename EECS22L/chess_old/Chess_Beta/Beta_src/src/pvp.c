#include <stdio.h>
#include <stdlib.h>
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



int playerVSplayer(void)
{
	//need to make the board first


	int initial_x, initial_y;
	
	int end_x, end_y;
	
	char i_x, e_x, i_y, e_y;


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


	int turn_counter = 2;	//turn counter  to see whose turn it is
	int legality = 0;

	while(1)
	{

		
			
		printf("Enter the x y coordinates of the piece you want to move(in the form \" x y\": ");
				
		scanf(" %c", &i_x);
		scanf(" %c", &i_y);

		printf("\nThe character values are %c %c \n",i_x, i_y);


		printf("\nEnter the x y coordinates of the place you want the piece to end up( in the form \" x y \": ");
			
		scanf(" %c", &e_x);
		scanf(" %c", &e_y);

		//conversion to the correct initial and end values
		
		initial_x = conversion_x(i_x); 	//column
		end_x = conversion_x(e_x);
		
		initial_y = conversion_y(i_y); 	//row
		end_y = conversion_y(e_y);
		
		//printf("%d %d %d %d \n", initial_y, initial_x, end_y, end_x);

		if( turn_counter % 2 == 0)	//this means that it is whites turn since it starts of whites turn 
		{
			if(board[initial_y][initial_x] < 0)	//this checks the peice if its white or black 
			{
				printf("It is whites turn. Choose a white piece to move.\n");
				displayBoard(board);
				continue;
			}
			else
			{
				;
			}
		}
		else if(turn_counter % 2 != 0) //sees if the turn is blacks turn
		{
			if(board[initial_y][initial_x] > 0)	//if the peice chosen is positive, then it is a white peice on a black turn which is wrong
			{
				printf("It is blacks turn. Choose a black piece to move.\n");
				displayBoard(board);
				continue;		//skips to the beginning of the while loop since it chose the wrong turn
			}
			else
			{
				;
			}
		}
		
		//illegal is zero
		//legal is one

		legality = move( board, initial_y, initial_x, end_y, end_x);

		if(legality == 0)
		{
			continue;
		}
			
		turn_counter++;

		displayBoard(board);
		
		printf("%c%c moved to %c%c \n" , i_x, i_y, e_x, e_y);
		
		//write2Log(board[end_x][end_y], initial_x , initial_y, end_x, end_y);



	}


}
