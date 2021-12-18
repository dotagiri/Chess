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

	while (getchar() != '\n');
	
	if (choice == 1)
		playerVSplayer();
	else if (choice == 2)
		playerVScomputer (choice);
	else if (choice == 3)
		playerVScomputer (choice);
	/*
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
	*/
	else if (choice == 8)
		ChessRules();
	else 	
		printf ("Invalid choice, please try again \n");
	} while (choice != 1 || choice != 2 || choice != 3);

	return 0;
}
