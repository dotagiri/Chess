#include <stdio.h>
#include <stdlib.h>
#include "ChessRules.h"
#include "menu.h"
#include "moves.h"
#include "board.h"
#include "pvp.h"
#include "pvc.h"
#include "aimoves.h"

void DeleteMove(MOVES *entry)
{
	assert(entry);

	free(entry);
}
MOVES *CreateMove(void)
{

	MOVES *move;
	
	move = malloc(sizeof(MOVES));


	if(!move)
	{
		printf("nothing was allocated!!\n");
		return 0;
	}

	move -> piece = 0;
	move -> x_old = 0;
	move -> y_old = 0;
	//move -> board_new[8][8] = {0};
	move -> x_new = 0;
	move -> y_new = 0;
	move -> board_value = 0;
	
	move -> next = NULL;

	move -> prev = NULL;
		
	move -> list = NULL;
	
	move -> future = NULL;	


	return move;

}


void DeleteMovesList(MLIST * list)
{
	assert(list);

	MOVES *x, *y;

	x = list -> first;
	while( x != NULL)
	{	
		y = x -> next;
		DeleteMove(x);
		x = y;

	}
	free(list);

	list = NULL;

}



MLIST *CreateMovesList(void)
{
	MLIST *list;
	list = malloc(sizeof(MLIST));
	
	if(!list)
	{

	printf("No list was created!!\n");
	return(list);
	}
	
	list -> first = NULL;
	list -> last = NULL;	

	list -> length = 0;
	
	return(list);
}

void AppendMove(MLIST *list, MOVES *move)
{
	MOVES *m;

	assert(list);
	assert(move);
	
	int x = 0;
	int y = 0;


	m = CreateMove();

	m -> piece = move -> piece;
	m -> x_old = move -> x_old;
	m -> y_old = move -> y_old;
	m -> x_new = move -> x_new;
	m -> y_new = move -> y_new;
	m -> board_value = move -> board_value;

	for(x = 0; x < 8; x++)
	{
		for(y = 0; y < 8; y++)
		{
			m -> board_new[x][y] = move -> board_new[x][y];
		}
	}

	if(list -> last)
	{
		m -> list = list;
		list -> last -> next = m;
		m -> next = NULL;
		m -> prev = list -> last;
		list -> last = m;

	}	
	else
	{
		m -> list = list;
		
		m ->next = NULL;
		
		m -> prev = NULL;
		
		list -> first = m;
			
		list -> last = m;		

	}

	list -> length = list -> length + 1;



}

