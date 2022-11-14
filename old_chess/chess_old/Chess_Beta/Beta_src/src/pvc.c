#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "moves.h"
#include "board.h"
#include "pvc.h"
#include "pvp.h"
//#include "ai.h"

/* Things needed
1) calling checkmate function and returning a value
2) incorporate AI function into the loops
*/
	
int playerVScomputer(int menu_returned_value)
{
	
	printf("Player vs Computer mode started\n"); 	

	int board[8][8] = 	{{-1,-2,-3,-4,-5,-3,-2,-1},
						{-6,-6,-6,-6,-6,-6,-6,-6},
						{ 0, 0, 0, 0, 0, 0, 0, 0},
						{ 0, 0, 0, 0, 0, 0, 0, 0},
						{ 0, 0, 0, 0, 0, 0, 0, 0},
						{ 0, 0, 0, 0, 0, 0, 0, 0},
						{ 6, 6, 6, 6, 6, 6, 6, 6},
						{ 1, 2, 3, 4, 5, 3, 2, 1}};
	displayBoard(board);

	char iChar_x = 0;		
	char iChar_y = 0;
	char fChar_x = 0;
	char fChar_y = 0;
	
	int initial_x, initial_y = 0;
	int final_x, final_y = 0;
	
	int level = 0;		//level determines easy, medium or hard
	int first = 0;		//first determines whether player or computer goes first
	int cpuColor = 0;	//cpuColor = 0 -> CPU is white, cpuColor = 1 -> CPU is black
	
	int a = 0;  		/* checks for checkmate, a = 0 means no checkmate, a = 1 means checkmate */
	int i = 0 ; 		/* counter: even is white, odd is black */
	int legal;			/* determines whether a move is legal or not */
	
	if (menu_returned_value == 2)
	{
		level = 1; //easy
		first = 1; //player is white and goes first
	}
	else if (menu_returned_value == 3)
	{
		level = 2; //medium
		first = 1; //player is white and goes first
	}
	else if (menu_returned_value == 4)
	{
		level = 3; //hard
		first = 1; //player is white and goes first
	}
	else if (menu_returned_value == 5)
	{
		level = 1; //easy
		first = 2; //player is black and goes second
	}
	else if (menu_returned_value == 6)
	{
		level = 2; //medium
		first = 2; //player is black and goes second
	}
	else if (menu_returned_value == 7)
	{
		level = 3; //hard
		first = 2; //player is black and goes second
	}
	
	
	//player moves FIRST loop
	if (first == 1)
	{
		cpuColor = 1; 	//for calling ai function, shows that CPU is black (second)
	
		while (a == 0)	// a = 0 -> no checkmate
		{			
		if (i % 2 == 0) /* player turn */
		{
			do
			{
			printf("Enter the x y coordinates of the piece you want to move(in the form \" x y\":\n");
				
			scanf(" %c", &iChar_x);
			scanf(" %c", &iChar_y);

			printf("The chess piece selected is at location %c%c \n",iChar_x, iChar_y);


			printf("Enter the x y coordinates of the place you want the piece to end up( in the form \" x y \": ");
			
			scanf(" %c", &fChar_x);
			scanf(" %c", &fChar_y);

			//conversion to the correct initial and end values
		
			initial_x = conversion_x(iChar_x); 	//column
			final_x = conversion_x(fChar_x);
			
			initial_y = conversion_y(iChar_y); 	//row
			final_y = conversion_y(fChar_y);
			
			} while (initial_x == 10 || initial_y== 10 || final_x == 10 || final_y == 10);
		
			//printf("%d %d %d %d \n", initial_y, initial_x, end_y, end_x);
			
			if(board[initial_y][initial_x] < 0)	//this checks the peice if its white or black 
			{
				printf("It is whites turn. Choose a white piece to move.\n");
				displayBoard(board);
				continue;
			}

			legal = move(board, initial_y, initial_x, final_y, final_x);
			
			if(legal == 0)
			{
				continue;
			}
	
			displayBoard(board);
		
			printf("%c%c moved to %c%c \n" , iChar_x, iChar_y, fChar_x, fChar_y);
			
			//a = checkmate (board, initial_x, initial_y);
			i = i + 1;		//counter increases to change turns 
		}
		
		if (i % 2 != 0 && level == 1) /* AI/computer easy turn*/
		{
			printf(" \nComputer Turn! \n");
			
			displayBoard(board);
			//a = checkmate (board, color, piece);
			i = i + 1;		//counter increases to change turns 
		}
		
		else if (i % 2 != 0 && level == 2) /* AI/computer medium turn*/
		{
			printf(" \nComputer Turn! \n");
			
			displayBoard(board);
			//a = checkmate (board, color, piece);
			i = i + 1;		//counter increases to change turns 
		}
		
		else if (i % 2 != 0 && level == 3) /* AI/computer hard turn*/
		{
			printf(" \nComputer Turn! \n");
			
			displayBoard(board);
			//a = checkmate (board, color, piece);
			i = i + 1;		//counter increases to change turns 
		} 
		
		}
	}
	
	//computer moves FIRST loop
	if (first == 2)
	{	
		cpuColor = 0; 	//for calling ai function, shows that CPU is white (first)
		i = i + 1;		// i starts off odd and computer starts first
		
		while (a == 0) 		// a = 0 -> no checkmate
		{
	
		if (i % 2 != 0 && level == 1) /* AI/computer easy turn*/
		{
			printf(" \nComputer Turn! \n");
			
			displayBoard(board);
			//a = checkmate (board, color, piece);
			i = i + 1;		//counter increases to change turns 
		}
		
		else if (i % 2 != 0 && level == 2) /* AI/computer medium turn*/
		{
			printf(" \nComputer Turn! \n");
			
			displayBoard(board);
			//a = checkmate (board, color, piece);
			i = i + 1;		//counter increases to change turns 
		}
		
		else if (i % 2 != 0 && level == 3) /* AI/computer hard turn*/
		{
			printf(" \nComputer Turn! \n");
			
			displayBoard(board);
			//a = checkmate (board, color, piece);
			i = i + 1;		//counter increases to change turns 
		}
		
		if (i % 2 == 0) /* player turn */
		{
			
			do {
			printf("Enter the x y coordinates of the piece you want to move(in the form \" x y\":\n");
				
			scanf(" %c", &iChar_x);
			scanf(" %c", &iChar_y);

			printf("The chess piece selected is at location %c%c \n",iChar_x, iChar_y);


			printf("Enter the x y coordinates of the place you want the piece to end up( in the form \" x y \": ");
			
			scanf(" %c", &fChar_x);
			scanf(" %c", &fChar_y);

			//conversion to the correct initial and end values
		
			initial_x = conversion_x(iChar_x); 	//column
			final_x = conversion_x(fChar_x);
			
			initial_y = conversion_y(iChar_y); 	//row
			final_y = conversion_y(fChar_y);
			
			} while (initial_x == 10 || initial_y == 10 || final_x == 10 || final_y == 10);
		
			//printf("%d %d %d %d \n", initial_y, initial_x, end_y, end_x);
			
			if(board[initial_y][initial_x] > 0)	//this checks the peice if its white or black 
			{
				printf("It is black's turn. Choose a black piece to move.\n");
				displayBoard(board);
				continue;
			}

			legal = move(board, initial_y, initial_x, final_y, final_x);
			
			if(legal == 0)
			{
				continue;
			}

			displayBoard(board);
		
			printf("%c%c moved to %c%c \n" , iChar_x, iChar_y, fChar_x, fChar_y);
		
			//a = checkmate (board, color, piece);
			i = i + 1;		//counter increases to change turns 
		}
		
		
		}
	}
	
	// need a return value later that determines whether player or computer won.
	return 0;
}
