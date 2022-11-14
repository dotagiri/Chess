#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "ChessRules.h"
#include "menu.h"
#include "moves.h"
#include "pvc.h"
#include "pvp.h"

//this is the main function for producing the chess game

int main(void)
{
	
	int choice = 0;
	
	do {
	choice = menu_returned_value ();
	
	if (choice == 1)
		playerVSplayer();
	else if (choice == 2)
		playerVScomputer (choice);
	else if (choice == 3)
		playerVScomputer (choice);
	else if (choice == 4)
		playerVScomputer (choice);
	else if (choice == 5)
		playerVScomputer (choice);
	else if (choice == 6)
		playerVScomputer (choice);
	else if (choice == 7)	
		playerVScomputer (choice);
	else if (choice == 8)
		ChessRules();
	else if (choice == 0)	
		printf ("Invalid choice, please try again \n");
	} while (choice < 0 || choice > 8);
/*	
	int initial_x, initial_y;
	int final_x, final_y;
	
	while (a == 1)
	{
	int i = 0 ; 
				*/
	/* counter: even is white, odd is black */
	/*
	printf("Enter the x y coordinates of the piece you want to move(in the form \"x y\": ");		
	scanf("%d %d", &initial_x, &initial_y);
	printf("Enter the x y coordinates of the place you want the piece to end up at(in the form \"x y\": ");
	scanf("%d %d", &final_x, &final_y);
	
	move (board [8][8], initial_x, initial_y, final_x, final_y);
	
	
	a = checkmate (board[8][8], color, piece);

	i = i + 1 
	}
		*/
	return 0;
}
