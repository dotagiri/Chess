#include "aigetmoves.h"

MLIST *getmoves(int board[8][8], MLIST *list, int color)
{
	//first need to copy the board onto a copy oboard so that if we manipulate it, it wont actually change since it is pass by reference
	//
	int x;
	int y;
	int j;
	int i;
	int h;
	int k;
	int **copy_board;
	copy_board = malloc(8*sizeof(int*));
	for(i=0;i<8;i++) 
	copy_board[i] = malloc(8*sizeof(int));


	copy_board = BoardCopy(board, copy_board);
	
	int reset_board[8][8];

	

	for(x = 0; x < 8; x++)
	{	
		for(y = 0; y < 8; y++)
		{
			reset_board[x][y] = copy_board[x][y]; //board to be manipulated and reset over and over again tosee if moves are legal		
		}
	}  
	
	//now the board copy is made we can manipulate the copy board and return it to the original board position 

	//we need to get the moves of the color that we are playing for. So the representation of the color is in the integer that is passed in. -1 means that its black and 1 means that its white


	MOVES *mov = CreateMove(); //move is created. we need to make sure that we put it in the list of moves that we will have

					//	void AppendMove(MLIST *list, MOVES *move); gonna need to alter the one struct here and keep adding it to the list with the different board
					//	and piece values

	for(x = 0; x < 8; x++)
	{
		for(y = 0; y < 8; y++)
		{
			if(board[x][y] != 0 && board[x][y] < 0 && color == -1)	//checks for BLACK PEICES MOVES ONLY FOR NOW
			{
				mov -> piece = board[x][y];
				mov -> x_old = x;
				mov -> y_old = y;


				for(i = 0; i < 8; i++)	//going to look through the board for all possible moves and if it finds a valid one then it appends to the list of all moves
				{
					for(j = 0; j < 8; j++)
					{
						if( i == x && j == y)	//if wrapper to make sure it doesnt add the same position in the possible list of new moves
						{
							;
						}
						else
						{
							//need to get the returned value of move function. and if it is legal then we add that move to the list of possible moves
							if(checkLegal(mov -> piece, reset_board, mov -> x_old, mov -> y_old, i, j) == 1)	//changed from checklegal to seeing if moving is legal
							{
								mov -> x_new = i;//if it is legal we move the piece in the new spot and put the new board in the move structure which we put in list of moves
								mov -> y_new = j;
	
								move(reset_board, mov -> x_old, mov -> y_old, mov -> x_new, mov -> y_new);		//now we need to move the piece and save the board								
								//int move(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

								if(check4Check(reset_board) == 1)	//makes sure that the move it makes doesnt put itself in check
								{
									;
								}
								else
								{
									mov -> board_value = board_evaluate(reset_board);
									
									for(h = 0; h < 8; h++)
									{
										for(k = 0; k < 8; k++)
										{
											mov -> board_new[h][k] = reset_board[h][k];			
										}
									}
								
									//printf("\nThe board value now is: %d\n", mov -> board_value);								
		
									AppendMove(list, mov);
									
								}

								for(h = 0; h < 8; h++)
								{	
									for(k = 0; k < 8; k++)
									{
										reset_board[h][k] = copy_board[h][k]; //board to be manipulated and reset over and over again tosee if moves are legal		
									}
								}	

//then we need to reset the board for the next iteration to see for other legal moves

							}
						}
					}
				}
			}
			else if( board[x][y] != 0 && board[x][y] > 0 && color == 1)
			{
				mov -> piece = board[x][y];
				mov -> x_old = x;
				mov -> y_old = y;


				for(i = 0; i < 8; i++)	//going to look through the board for all possible moves and if it finds a valid one then it appends to the list of all moves
				{
					for(j = 0; j < 8; j++)
					{
						if( i == x && j == y)	//if wrapper to make sure it doesnt add the same position in the possible list of new moves
						{
							;
						}
						else
						{
							//need to get the returned value of move function. and if it is legal then we add that move to the list of possible moves
							if(checkLegal(mov -> piece, reset_board, mov -> x_old, mov -> y_old, i, j) == 1)
							{
								mov -> x_new = i;//if it is legal we move the piece in the new spot and put the new board in the move structure which we put in list of moves
								mov -> y_new = j;
	
								move(reset_board, mov -> x_old, mov -> y_old, mov -> x_new, mov -> y_new);		//now we need to move the piece and save the board								
								//int move(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol);

								mov -> board_value = board_evaluate(reset_board);
								
								if(check4Check(reset_board) == 2)	//makes sure that a move doesnt put itself in check
								{
									;
								}
								else
								{
									for(h = 0; h < 8; h++)
									{
										for(k = 0; k < 8; k++)
										{
											mov -> board_new[h][k] = reset_board[h][k];			
										}
									}
									
							//		printf("The board value now is: %d", mov -> board_value);								
		
									AppendMove(list, mov);
								}

								for(h = 0; h < 8; h++)
								{	
									for(k = 0; k < 8; k++)
									{
										reset_board[h][k] = copy_board[h][k]; //board to be manipulated and reset over and over again tosee if moves are legal		
									}
								}	

//then we need to reset the board for the next iteration to see for other legal moves
							}
						}
					}
				}
			}		
		}
	}
	
	DeleteMove(mov);
	
	//printf("\n\nThere are the number of moves possible: %d\n\n", list ->length);	

	for(i = 0; i < 8; ++i)
	{
		free(copy_board[i]);
	}
	
	free(copy_board);

	/*
	if(list -> length == 0)
	{
		printf("\n\nWow i just lost!! :0 \n\n");
	}
	*/
	return list;
	
}






int board_evaluate(int board[8][8])
{
	//there are lots of value systems that could make the game or break it
	//the ones that i intend to use is as follows:
	//each peice has a value behind their capture with the king obviously worth the most as a kill
	/*
 		pawn = 1 point
		knight = 3 points
		bishop = 3 points
		rook = 5 points
		queen = 9 points
		king = inifinite points, but in this case i will just make it worth 10,000 points since we cannot use the infinite value

	*/

	//there is also positional advantage. if the board is more open for one side, then thier board value should technically be more. now there is no real way to solve this other than seeing the position and checking if the original places dont have the peices that they originally had on them, which may take lots of time. so i will just check for if the 2 rows has peices in them, and if they are open spaces then 1 point is awarded to that side. This means that at the start of the game, each team has 0 points for positional prowess.
	//obviously having you queen in the open is worth move and moving your king is not a good move unless its a castle. I will cover the case for the king where his movement is not worth much unless he castles.
	//
	//
	//
	//

	int board_value = 0;
	int x = 0;	//to go through the values of the board
	int y = 0;

	for(x = 0; x < 8; x++)		//giving points for positional advantage
	{	
		for(y = 0; y < 8; y++)
		{
			board_value = piecevalue(board[x][y]) + board_value;
			
			if (piecevalue(board[x][y]) == 0 &&  x < 2)	
			{
				board_value = board_value - 1;

			}
			else if( piecevalue(board[x][y]) == 0 && x > 5)
			{
				board_value = board_value + 1;

			}
			
			if(check4Check(board) == 1)
			{
				board_value = 500 + board_value;
			}
			else if(check4Check(board) == 2)
			{
				board_value = board_value - 500;	
			}
			else
			{
				;
			}

		}
	}
		
	return board_value;
} 
int piecevalue(int piece)
{
	switch(piece)
	{
		case -1:
			return -5;
			break;
		case -2:
			return -3;
			break;
		case -3:
			return -3;
			break;
		case -4:
			return -9;
			break;
		case -5:
			return -10000;
			break;
		case -6:
			return -1;
			break;
		case 1:
			return 5;
			break;
		case 2:
			return 3;
			break;
		case 3:
			return 3;
			break;
		case 4:
			return 9;
			break;
		case 5:
			return 10000;
			break;
		case 6:
			return 1;
			break;
		case 0:
			return 0;
			break;

	}
	
	printf("no piece value was returned");	
	return 0;

}
int **BoardCopy(int og[8][8], int **new1)
{
	int x = 0;
	int y = 0;
	
	for(x = 0; x < 8 ; x++)
	{
		for( y = 0; y < 8 ; y++)
		{
			new1[x][y] = og[x][y];

		}

	}

	return new1;

}
int checkmate2(int board[8][8], int color)
{
	//make a list of all the moves possible. dont add the move to the list if it leaves the king in check for that color. if the lenth of the list is zero then return
	//return 1 for black in checkmate
	//return 2 for white in checkmate
	//
	
	MLIST *list = CreateMovesList();

	if(color == -1)
	{
		list = getmoves(board,list, color);
		
		if(list->length == 0)
		{
			DeleteMovesList(list);
			return 2;	//the black king is in the checkmate
		}

	}	
	else if(color == 1)
	{
		list = getmoves(board,list, color);
		if( list->length == 0)
		{
			
			DeleteMovesList(list);
			return 1;	//the white king is in checkmate

		}	

	}
	
	DeleteMovesList(list);
	return 0;
	
	
}
