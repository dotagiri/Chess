#include "aigetmoves.h"


int main(void)
{
	int board[8][8] = {{-1,-2,-3,-4,-5,-3,-2,-1},
  			   {-6,-6,-6,-6,-6,-6,-6,-6},
 			   { 0, 0, 0, 0, 0, 0, 0, 0},
  			   { 0, 0, 0, 0, 0, 0, 0, 0},
  			   { 0, 0, 0, 0, 0, 0, 0, 0},
  			   { 0, 0, 0, 0, 0, 0, 0, 0},
  			   { 6, 6, 6, 6, 6, 6, 6, 6},
  			   { 1, 2, 3, 4, 5, 3, 2, 1}};

	MLIST *list = CreateMovesList();	


	getmoves(board, list, -1);


	return 0;


}
