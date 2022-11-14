#include "aigetmoves.h"



void ai(int board[8][8], int color)
{
	//color is -1 for black
	//color is 1 for white
	//
	//call the ai function for the ai to make a move for the corresponding color		
		
	MLIST *list = CreateMovesList();

	int x_initial = 0;
	
	int y_initial = 0;
	
	int x_end = 0;
		
	int y_end = 0;
		
	//int maximum = 0;

	list = getmoves(board, list, color);


	assert(list);

	MOVES *x;

	//MOVES *y;

	x = list -> first;
		
	//displayBoard(list->first-> board_new);

/*	while( x != NULL)
	{	
		y = x -> next;
		
		if(x -> board_value > maximum && color == 1)
		{
			maximum = x -> board_value;
			
			x_initial = x -> x_old;
			y_initial = x -> y_old;
			
			x_end = x -> x_new;
			y_end = x -> y_new;
		}
		else if( x -> board_value < maximum && color == -1)
		{
			maximum = x -> board_value;
			
			x_initial = x -> x_old;
			y_initial = x -> y_old;
			
			x_end = x -> x_new;
			y_end = x -> y_new;


		}
		
		x = y;

	}
	*/

	x_initial = x -> x_old;
	y_initial = x -> y_old;
	x_end = x -> x_new;
	y_end = x -> y_new;
	


 

	
	move(board, x_initial, y_initial, x_end, y_end);


}









