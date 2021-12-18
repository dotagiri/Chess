#include <stdio.h>
#include <stdlib.h>
#include "ChessRules.h"
#include "menu.h"
#include "moves.h"
#include "board.h"
#include "pvp.h"
#include "pvc.h"
#include "conversion.h"
#include <assert.h>

typedef struct moveslist MLIST;
typedef struct all_moves MOVES;


	struct all_moves
	{
		int piece;
		int x_old;
		int y_old;
		int board_new[8][8];
		int x_new;
		int y_new;
		int board_value;	//the value of the board in its current state based on our algorithm
		MOVES *next;		// thje next of the new moves from the previous board state
		MOVES *prev;		//the next move of the new moves for the previous board state
		MLIST *list;	//list of all next moves	

		MLIST *future;	//to see the future moves based on the current board state in this structure which is incidentall called board_new

	};

	struct moveslist
	{	
		MOVES *first;
		MOVES *last;
		int length;

	};


void DeleteMove(MOVES *move);

MOVES *CreateMove(void);

void DeleteMovesList(MLIST * list);

MLIST *CreateMovesList(void);

void AppendMove(MLIST *list, MOVES *move);

		//now we need to make a function that literally gets all the moves
