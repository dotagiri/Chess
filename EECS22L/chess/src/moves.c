/*************************************************
 * Changes made:
 * 04/24/2020 - Daisuke -  added checkPawn function, 
 * 			   added out of bounds condiitonal to checkLegal,
 * 			   removed out of bounds if in every function (checkPiece) 
 * 04/25/2020 - Daisuke -  debugged checkPawn	
 * 04/25/2020 - Hao - finished check4Check()
 * 05/01/2020 - Hao - update checkKing()
 * 05/02/2020 - Hao - update all the repeated portion of code in the function
 * 05/02/2020 - Daisuke - added capture to checkPawn
 * 05/03/2020 - Daisuke updated checkPawn
 * 05/08/2020 - Hao - fix a bug in check4Check()
 * 05/09/2020 - Daisuke - fixing checkPawn
 * */


#include "moves.h"
#include <stdlib.h>
#include <stdio.h>
#include "special_moves.h"
#include "setFlag.h"
#include "aigetmoves.h"

/* check diagonal direction */
int diagonalDirection(int prevRow, int prevCol, int nextRow, int nextCol){
    int direction=0; 
    /* check the legality of diagonal down right */
    for(int x=1;x<8;x++){
        if((prevRow+x==nextRow)&&(prevCol+x==nextCol)&&(prevRow+x<8)&&(prevCol+x<8)){
                direction=1;
//                printf("The piece is moving diagonally down to the right.\n");
        }
    }

    /*check the legality of diagonal down left*/
    for(int x=1;x<8;x++){
        if((prevRow+x==nextRow)&&(prevCol-x==nextCol)&&(prevRow+x<8)&&(prevCol+x>=0)){
                direction=2;
//                printf("The piece is moving diagonally down to the left.\n");
        }
    }

    /*check the legality of diagonal up left*/
    for(int x=1;x<8;x++){
        if((prevRow-x==nextRow)&&(prevCol-x==nextCol)&&(prevRow+x>=0)&&(prevCol+x>=0)){
                direction=3;
//                printf("The piece is moving diagonally up to the left.\n");
        }
    }

    /* check the legality of diagonal up right */
    for(int x=1;x<8;x++){
        if((prevRow-x==nextRow)&&(prevCol+x==nextCol)&&(prevRow+x>=0)&&(prevCol+x<8)){
                direction=4;
//                printf("The piece is moving diagonally up to the right.\n");
        }
    }
    if(direction==0){
//	printf("The move is not diagonal.\n");
    }
    return direction;
}

/* check legality of diagonal move*/
int checkDiagonal(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
    int direction=diagonalDirection(prevRow, prevCol, nextRow, nextCol);
    if(direction<1||direction>4){
//	printf("The move is not diagonal.\n");
	return 0; /* out of range */
    }
    int diagonalBlock=0;
    if(direction==1){
	diagonalBlock=diagonalDownRightBlock(board, prevRow, prevCol, nextRow, nextCol);
    }
    else if(direction==2){
	diagonalBlock=diagonalDownLeftBlock(board, prevRow, prevCol, nextRow, nextCol);
    }
    else if(direction==3){
	diagonalBlock=diagonalUpLeftBlock(board, prevRow, prevCol, nextRow, nextCol);
    }
    else if(direction==4){
	diagonalBlock=diagonalUpRightBlock(board, prevRow, prevCol, nextRow, nextCol);
    }
    return diagonalBlock;
    
}

/* check blocked pieces in diagonally down to the right*/
int diagonalDownRightBlock(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
    for(int x=1;x<8;x++){
	if(board[prevRow+x][prevCol+x]!=0){
	    if(prevRow+x==nextRow&&prevCol+x==nextCol&&board[prevRow][prevCol]*board[nextRow][nextCol]<=0){
//                printf("It's a valid move.\n");
                return 1;
            }
            else{   
//                printf("Blocked piece in the diagonal down right.\n");
                return 0;
            }
	}
        else if(board[prevRow+x][prevCol+x]==0){
            if(prevRow+x==nextRow&&prevCol+x==nextCol&&prevRow+x<8&&prevCol+x<8){
//                printf("It is a valid move.\n");
                return 1;
            }
	}
    }
    return 0;
}

/* check blocked pieces in diagonally down to the left */
int diagonalDownLeftBlock(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
    for(int x=1;x<8;x++){
        if(board[prevRow+x][prevCol-x]!=0){
            if(prevRow+x==nextRow&&prevCol-x==nextCol&&board[prevRow][prevCol]*board[nextRow][nextCol]<=0){
//                printf("It's a valid move.\n");
                return 1;
            }
            else{
//                printf("Blocked piece in the diagonal down left.\n");
                return 0;
            }
	}
        else if(board[prevRow+x][prevCol-x]==0){
            if(prevRow+x==nextRow&&prevCol-x==nextCol&&prevRow+x<8&&prevCol+x>=0){
//                printf("It is a valid move.\n");
                return 1;
           }
        }
    }
    return 0;
}

/* check blocked pieces in diagonally up to the left*/
int diagonalUpLeftBlock(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
    for(int x=1;x<8;x++){
        if(board[prevRow-x][prevCol-x]!=0){
            if(prevRow-x==nextRow&&prevCol-x==nextCol&&board[prevRow][prevCol]*board[nextRow][nextCol]<=0){
//                printf("It's a valid move.\n");
                return 1;
            }
            else{
//                printf("Blocked piece in the diagonal up left.\n");
                return 0;
            }
        }
        else if(board[prevRow-x][prevCol-x]==0){
            if(prevRow-x==nextRow&&prevCol-x==nextCol&&prevRow+x>=0&&prevCol+x>=0){
//                printf("It is a valid move.\n");
                return 1;
            }
        }
    }
    return 0;

}
 
/* check blocked pieces in diagonally up to the right*/
int diagonalUpRightBlock(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
    for(int x=1;x<8;x++){
        if(board[prevRow-x][prevCol+x]!=0){
            if(prevRow-x==nextRow&&prevCol+x==nextCol&&board[prevRow][prevCol]*board[nextRow][nextCol]<=0){
//                printf("It's a valid move for bishop.\n");
                return 1;
            }
            else{
//                printf("Blocked piece in the diagonal up right.\n");
                return 0;
            }
        }
        else if(board[prevRow-x][prevCol+x]==0){
            if(prevRow-x==nextRow&&prevCol+x==nextCol&&prevRow+x>=0&&prevCol+x<8){
//                printf("It is a valid move.\n");
                return 1;
            }
        }
    }
    return 0;    
}

/* check horizontal */
int checkHorizontal(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
    if((prevRow==nextRow) && (prevCol!=nextCol)){
        /* check the legality when the piece moves horizontally to the right*/
        if(prevCol-nextCol<0){
            for(int x=prevCol+1;x<=nextCol;x++){
                if((board[prevRow][x]!=0)&&(x!=nextCol)){
//                    printf("There is a piece blocking its way on its right.\n");
                    return 0;
                }
                else if(x==nextCol){
                    if(board[nextRow][nextCol]*board[prevRow][prevCol]>0){
//                        printf("There is an ally piece in the final position.\n");
                        return 0;
                    }
                }
            }
//            printf("It's a legal move.\n");
            return 1;
        }
        /* check the legality when the piece moves horizontally to the left*/
        else if(prevCol-nextCol>0){
            for(int x=prevCol-1;x>=nextCol;x--){
                if((board[prevRow][x]!=0)&&(x!=nextCol)){
//                    printf("There is a piece blocking its way on its left.\n");
                    return 0;
                }
                else if(x==nextCol){
                    if(board[nextRow][nextCol]*board[prevRow][prevCol]>0){
//                        printf("There is an ally piece in the final position.\n");
                        return 0;
                    }
                }
            }
//            printf("It's a legal move.\n");
            return 1;
        }
    }
    return 0;
}

/* check vertical */
int checkVertical(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
    /* check the legality when queen moves vertically */
    if((prevCol==nextCol)&&(prevRow!=nextRow)){
        /* check the legality when the piece moves vertically downward */
        if(prevRow-nextRow<0){
            for(int x=prevRow+1;x<=nextRow;x++){
                if((board[x][prevCol]!=0)&&(x!=nextRow)){
//                    printf("There is a piece blocking its way at its bottom.\n");
                    return 0;
                }
                else if(x==nextRow){
                    if(board[nextRow][nextCol]*board[prevRow][prevCol]>0){
//                        printf("There is an ally piece in the final position.\n");
                        return 0;
                    }
                }
            }
//            printf("It's a legal move.\n");
            return 1;
        }
        /* check the legality when the piece moves vertially upward */
        else if(prevRow-nextRow>0){
            for(int x=prevRow-1;x>=nextRow;x--){
                if((board[x][prevCol]!=0)&&(x!=nextRow)){
//                    printf("There is a piece blocking its way at its top.\n");
                    return 0;
                }
                else if(x==nextRow){
                    if(board[nextRow][nextCol]*board[prevRow][prevCol]>0){
//                        printf("There is an ally piece in the final position.\n");
                        return 0;
                    }
                }
            }
//            printf("It's a legal move.\n");
            return 1;
        }
    }
    return 0;

}

unsigned int checkAllyOnPos(int board[8][8], const int currRow, const int currCol, const int nextRow, const int nextCol)
{
	if (board[currRow][currCol] == 6 && board[nextRow][nextCol] > 0){
		return 1;
	}

	else if (board[currRow][currCol] == -6 && board[nextRow][nextCol] < 0){
		return 1;
	}

	return 0;
}


unsigned int checkEnemyOnPos(int board[8][8], const int currRow, const int currCol, const int nextRow, const int nextCol)
{
	if (board[currRow][currCol] == 6 && board[nextRow][nextCol] < 0){
		return 1;
	}

	else if (board[currRow][currCol] == -6 && board[nextRow][nextCol] > 0){
		return 1;
	}

	return 0;
}


unsigned int checkFrontalBlockage(int board[8][8], const int currRow, const int currCol, const int nextRow)
{
	// For white pieces
	if (nextRow - currRow < 0){
		for (unsigned int i = currRow - 1; i > nextRow; --i){
			if (board[i][currCol] != 0){
				return 1;
			}
		}
	}

	// For black pieces
	else if (nextRow - currRow > 0){
		for (unsigned int i = currRow + 1; i < nextRow; ++i){
			if (board[i][currCol] != 0){
				return 1;
			}
		}
	}

	return 0;
}


/* moves a piece from one location on the board to the next */
int move(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
   int checkM=-1;
   int check=-1;
   int wK=-1;
   int wRR=-1;
   int wLR=-1;
   int bK=-1;
   int bRR=-1;
   int bLR=-1;
   int x= checkLegal(board[prevRow][prevCol],board,prevRow,prevCol,nextRow,nextCol);
   if(x==1){
	if(board[prevRow][prevCol]==5&&prevRow==7&&nextRow==7&&prevCol==4&&nextCol==6){
	    board[7][6]=5;
	    board[7][5]=1;
	    board[7][7]=0;
	    board[7][4]=0;
	    wK=movedWKing(1);
	    wRR=movedWRRook(1);
	    printf("King side castling for white is legal.\n");    
	}
	else if(board[prevRow][prevCol]==5&&prevRow==7&&nextRow==7&&prevCol==4&&nextCol==2){
	    board[7][2]=5;
            board[7][3]=1;
            board[7][0]=0;
            board[7][4]=0;
	    wK=movedWKing(1);
	    wLR=movedWLRook(1);
	    printf("Queen side castling for white is legal.\n");
	}
	else if(board[prevRow][prevCol]==-5&&prevRow==0&&nextRow==0&&prevCol==4&&nextCol==6){
	    board[0][6]=-5;
            board[0][5]=-1;
            board[0][7]=0;
            board[0][4]=0;
	    bK=movedBKing(1);
	    bRR=movedBRRook(1);
	    printf("King side castling for black is legal.\n");
	}
	else if(board[prevRow][prevCol]==-5&&prevRow==0&&nextRow==0&&prevCol==4&&nextCol==2){
	    board[0][2]=-5;
            board[0][3]=-1;
            board[0][0]=0;
            board[0][4]=0;
	    bK=movedBKing(1);
	    bLR=movedBLRook(1);
	    printf("Queen side castling for black is legal.\n");
	}
	else{
	    board[nextRow][nextCol]=board[prevRow][prevCol];
	    board[prevRow][prevCol]=0;
	}
	whitePawnPromotion(board);
	blackPawnPromotion(board);			
	check=check4Check(board);
	
	if(check==3){
	    printf("Both are in check.\n");
	}
	else if(check==2){
	    printf("White is in check.\n");
	}
	else if(check==1){
	    printf("Black is in check.\n");
	}
	checkM=checkmate(board);
/*	if(checkmate2(board,-1)==2){
	    printf("Black in checkmate.\n");
	}

	if(checkmate2(board,1)==1){
	    printf("White in checkmate.\n");
	}
*/	
	return 1;
   }
   else{
	printf("Not able to move a piece.\n");	
   	return 0;
   }
    return 0;
}

/* check whether a move is legal */
int checkLegal(int piece,int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
    int n=0;
    int flag=-1;
    if( prevRow<0 || prevRow>7 || prevCol<0 || prevCol>7 || nextRow<0 || nextRow>7 || nextCol<0 || nextCol>7){ /*out of bounds check*/
	printf("Position is out of bound.\n");
        return 0;
    	} /*fi*/ 
	
    if(piece==1||piece==-1){
	n=checkRook(board,prevRow,prevCol,nextRow, nextCol);
    	if(n==1){
	    if(piece==1||piece==-1){
		if(prevRow==7&&prevCol==0){
		    flag=movedWLRook(1);
		    return 1;
		}
		else if(prevRow==7&&prevCol==7){
		    flag=movedWRRook(1);
		    return 1;
		}
		else if(prevRow==0&&prevCol==0){
		    flag=movedBLRook(1);
		    return 1;
		}
		else if(prevRow==0&&prevCol==7){
		    flag=movedBRRook(1);
		    return 1;
		}
		return 1;
	    }
	}
	else if(n==0){
	    return 0;
	}
    }
    else if(piece==2||piece==-2){
    	n=checkKnight(board,prevRow,prevCol,nextRow, nextCol);
        if(n==1){
            return 1;
        }
        else if(n==0){
            return 0;
        }

    }
    else if(piece==3||piece==-3){
        n=checkBishop(board,prevRow,prevCol,nextRow, nextCol);
        if(n==1){
            return 1;
        }
        else if(n==0){
            return 0;
        }

    }
    else if(piece==4||piece==-4){
        n=checkQueen(board,prevRow,prevCol,nextRow, nextCol);
        if(n==1){
            return 1;
        }
        else if(n==0){
            return 0;
        }

    }
    else if(piece==5||piece==-5){
        n=checkKing(board,prevRow,prevCol,nextRow, nextCol);
        if(n==1){
	    if(piece==5){
	    	flag=movedWKing(1);
            	return 1;
	    }
	    else if(piece==-5){
		flag=movedBKing(1);
		return 1;
	    }
        }
	else if(n==2){
	    return 1;
	}
        else if(n==0){
            return 0;
        }

    }
    else if(piece==6||piece==-6){
        n=checkPawn(board,prevRow,prevCol,nextRow, nextCol);
        if(n==1){
            return 1;
        }
        else if(n==0){
            return 0;
        }

    }

    return 0;
}


/* check the legality of the pawn move */
unsigned int newCheckPawn(int board[8][8], int currRow, int currCol, int nextRow, int nextCol)
{
	if (checkPawnMovesForward(board[currRow][currCol], currRow, currCol, nextRow, nextCol) == 0){
		return 0;
	}

	if (checkAllyOnPos(board, currRow, currCol, nextRow, nextCol) == 1){
		return 0;
	}

	// Attempt to move more than two spaces.
	if (abs(nextRow - currRow) > 2){
		return 0;
	}

	// Two Spaces
	else if (abs(nextRow - currRow) == 2){
		if (checkDoubleStep(board, currRow, currCol, nextRow, nextCol) == 0){
			return 0;
		}
	}

	// One space
	else if (abs(nextRow - currRow) == 1){
		if (checkSingleStep(board, currRow, currCol, nextRow, nextCol) == 0){
			return 0;
		}
	}

	return 1;
}


unsigned int checkPawnMovesForward(const int piece, const int currRow, const int currCol, const int nextRow, const int nextCol)
{
	if (piece == 6 && nextRow - currRow < 0){
		return 1;
	}

	else if (piece == -6 && nextRow - currRow > 0){
		return 1;
	}

	return 0;
}


unsigned int checkDoubleStep(int board[8][8], const int currRow, const int currCol, const int nextRow, const int nextCol)
{
	if (abs(nextCol - currCol) != 0){
		return 0;
	}	

	if (checkFrontalBlockage(board, currRow, currCol, nextRow) == 1){
		return 0;
	}

	if (checkEnemyOnPos(board, currRow, currCol, nextRow, nextCol) == 1){
		return 0;
	}

	if (board[currRow][currCol] == 6 && currRow != 6){
		return 0;
	}

	else if (board[currRow][currCol] == -6 && currRow != 1){
		return 0;
	}

	return 1;
}


unsigned int checkSingleStep(int board[8][8], const int currRow, const int currCol, const int nextRow, const int nextCol)
{
	if (abs(nextCol - currCol) > 1){
		return 0;
	}

	// One diagonal step
	else if (abs(nextCol - currCol) == 1){
		if (checkEnemyOnPos(board, currRow, currCol, nextRow, nextCol) == 0){
			return 0;
		}
	}

	// One forward step
	else if (abs(nextCol - currCol) == 0){
		if (checkEnemyOnPos(board, currRow, currCol, nextRow, nextCol) == 1){
			return 0;
		}
	}

	return 1;
}


/* check legality of pawn movement, return 1 for legal and 0 for illegal*/
int checkPawn(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
	int x;
	int flag = 0;

	if (board[prevRow][prevCol] != 6 && board[prevRow][prevCol] != -6){ //check if the piece is a pawn
		return 0;
		} /*fi*/
	/*for white*/
	if (board[prevRow][prevCol]>0){ 
		if (prevRow == 6 && nextRow < prevRow-2){ //check if pawn moves more than 2 spaces from starting position
			return 0;
			} /*fi*/

		else if (prevRow != 6 && nextRow < prevRow-1){ //check if pawn moves more than 1 space
			return 0;
			} /*fi*/
		else if (board[nextRow][nextCol]>0){
			return 0;
			}

		else if (nextRow - prevRow > 0){
			return 0;
			}

		for (x=prevRow-1; x>=nextRow; x--){ //for every space moved
			if (board[x][prevCol] != 0 && x != nextRow){ /*check for piece*/
				return 0;
				} /*fi*/
			else if(x == nextRow){ /*checks for ally */
				if(board[nextRow][nextCol]*board[prevRow][prevCol]>0){
					return 0;
					} /*fi*/
				} /*fi*/
			} /*rof*/
		
		/*white capturing black*/
		if (board[nextRow][nextCol]<0){
			//diagonal left
			if (nextRow == prevRow-1 && nextCol == prevCol-1){ 
				return 1;
				}/*fi*/
			//diagonal right
			else if (nextRow == prevRow-1 && nextCol == prevCol+1){
				return 1;
				} /*fi*/	
			else{
				return 0;
				} /*esle*/
			} /*fi*/
		/*whiteEnpassant*/
		flag = whiteEnPassant(board, prevRow, prevCol, nextRow, nextCol);
		if (flag == 1){
			board[nextRow+1][nextCol] = 0;
			return 1;				
			} /*fi*/ 
		} /*fi*/ 
	/*for black*/
	if (board[prevRow][prevCol]<0){
		if (nextRow == prevRow-1){
			return 0;}
		else if(prevRow == 1 && nextRow > prevRow+2){ //check if pawn moves more than 2 spaces from starting
			return 0;
			} /*fi*/

		else if (prevRow != 1 && nextRow > prevRow+1){ //check if pawn moves more than 1 space
			return 0;
			} /*fi*/
		  
		else if (board[nextRow][nextCol]<0){
			return 0;
			}
		else if (nextRow - prevRow < 0){
			return 0;
			}
		for (x=prevRow+1; x<=nextRow; x++){ //for every space moved
			if(board[x][prevCol]!=0 && x!= nextRow){ //if there is piece in square
				return 0;	
				} /*fi*/
			else if (x == nextRow){ /*check for ally piece*/
				if(board[nextRow][nextCol]*board[prevRow][prevCol]>0){
					return 0;
					} /*fi*/
				}/*fi*/
			}/*rof*/
		
		/*black captures white*/	
		if (board[nextRow][nextCol]>0){
			//diagonal left
			if (nextRow == prevRow+1 && nextCol == prevCol-1){ 
				return 1;
				}/*fi*/
			//diagonal right
			else if (nextRow == prevRow+1 && nextCol == prevCol+1){
				return 1;
				} /*fi*/
			else{
				return 0;
				} /*esle*/
			} /*fi*/
		flag = blackEnPassant(board, prevRow, prevCol, nextRow, nextCol);
		if (flag == 1){
			board[nextRow-1][nextCol] = 0;
			return 1;				
			} /*fi*/ 
		} /*fi*/
	

	/*cannot move diagonally if not capturing*/	
	if (prevCol != nextCol) {
		return 0;
		} /*fi*/

	return 1;
}/*end of checkPawn*/

/* check the legality of the king move; return 1 for legal and 0 for illegal */
int checkKing(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
    
    if ( board[prevRow][prevCol] != 5 &&  board[prevRow][prevCol] != -5 ){
//	printf("Moving piece is not king.\n");
	return 0;

    }

    int rowCondition = prevRow - nextRow;
    int colCondition = prevCol - nextCol;

    /* check legality for vertical movement */
    if ( (rowCondition == 1 || rowCondition == -1)&&(colCondition==0)&&(board[prevRow][prevCol]*board[nextRow][nextCol]<=0) ) {
//	printf("Legal vertical move.\n");
        return 1;
    }

    /* check legality for horizontal movement */
    if( (colCondition == 1 || colCondition == -1)&&(rowCondition==0)&&(board[prevRow][prevCol]*board[nextRow][nextCol]<=0) ) {
//	printf("Legal horizontal move.\n");
        return 1;
    }

    /* check legality for diagonal down left */
    if((colCondition ==1||colCondition==-1)&&(rowCondition==1||rowCondition==-1)&&(board[prevRow][prevCol]*board[nextRow][nextCol]<=0)){
//	printf("Legal diagonal move.\n");
	return 1;
    }

    /* check for castling */
    if(castleKingSide(board,prevRow,prevCol,nextRow,nextCol)==1){
	return 2;
    }
    else if(castleQueenSide(board,prevRow,prevCol,nextRow,nextCol)==1){
	return 2;
    }

//    printf("It is not a legal move for king.\n");
    return 0;
}

/* check the legality of the knight move; return 1 for legal and 0 for illegal */
int checkKnight(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol) {
    if ( board[prevRow][prevCol] != 2 &&  board[prevRow][prevCol] != -2 ){
//	printf("Moving piece is not knight.\n");
	return 0;
    }

    int rowCondition = prevRow - nextRow;
    int colCondition = prevCol - nextCol;

    if(((rowCondition==1||rowCondition==-1)&&(colCondition==2||colCondition==-2) )||((rowCondition==2||rowCondition==-2)&&(colCondition==1||colCondition==-1))){
	if(board[prevRow][prevCol]*board[nextRow][nextCol]<=0){
//        	printf("It is a legal move for knight.\n");
		return 1;
        }
        else if(board[prevRow][prevCol]*board[nextRow][nextCol]>0){
//		printf("There is an ally piece.\n");
                return 0;
        }
    }
        return 0;
}

/* check the legality of the rook move; return 1 for legal and 0 for illegal */
int checkRook(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol) {
    if(board[prevRow][prevCol] != 1 &&  board[prevRow][prevCol] != -1 ){
//	printf("Moving piece is not rook.\n");
        return 0;
    }
    int verticalCheck=0;
    int horizontalCheck=0;
    /*check vertical move*/
    verticalCheck=checkVertical(board,prevRow,prevCol,nextRow,nextCol);
    /* check horizontal move*/
    horizontalCheck=checkHorizontal(board,prevRow,prevCol,nextRow,nextCol);
    
    if(verticalCheck==1&&horizontalCheck==0){
	return 1;
    }
    else if(verticalCheck==0&&horizontalCheck==1){
	return 1;
    }
    else{
	return 0;
    }
    return 0;
} /*end of checkRook*/

/* check the legality of the bishop move; return 1 for legal and 0 for illegal */
int checkBishop(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol) {
    if ( board[prevRow][prevCol] != 3 &&  board[prevRow][prevCol] != -3 ){
//        printf("Moving piece is not bishop.\n");
        return 0;
    }
    /* check diagonal move*/
    int check=checkDiagonal(board,prevRow, prevCol, nextRow, nextCol);
    if(check==0){
//	printf("Illegal move for bishop.\n");
	return 0;
    }
    else if(check==1){
//	printf("Legal move for bishop.\n");
	return 1;
    }    
    return 0;
} /*end of checkBishop*/ 

/* check the legality of the queen move */
int checkQueen(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
    if ( board[prevRow][prevCol] != 4 &&  board[prevRow][prevCol] != -4 ){
//        printf("Moving piece is not queen.\n");
        return 0;
    }

    int verticalCheck=0;
    int horizontalCheck=0;
    int diagonalCheck=0;

    /*check diagonal move*/
    diagonalCheck=checkDiagonal(board,prevRow,prevCol,nextRow,nextCol);
    /*check vertical move*/
    verticalCheck=checkVertical(board,prevRow,prevCol,nextRow,nextCol);
    /* check horizontal move*/
    horizontalCheck=checkHorizontal(board,prevRow,prevCol,nextRow,nextCol);

    if(verticalCheck==1&&horizontalCheck==0&&diagonalCheck==0){
        return 1;
    }
    else if(verticalCheck==0&&horizontalCheck==1&&diagonalCheck==0){
        return 1;
    }
    else if(verticalCheck==0&&horizontalCheck==0&&diagonalCheck==1){
        return 1;
    }
    else{
	return 0;
    }

    return 0;
} /*end of checkQueen*/

/* check whether the king is in check (returns 1 if black king is in check,2 if white king is in check,0 if it isn’t)*/
int check4Check(int board[8][8]){

    /* check whether white king is in check */
    int whiteInCheck=0;
    int rowWKing=-1;
    int colWKing=-1;

    /* check the current position of white king */
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            if(board[y][x]==5){
                rowWKing=y;
                colWKing=x;
            }
        }
    }
    if(rowWKing<0||rowWKing>7||colWKing>7||colWKing<0){
//        printf("White King is not on the board.\n");
	return 0;
    }
    
    /* check whether each black pieces are attacking white king */
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
	    if(board[y][x]<0){
	        if(checkLegal(board[y][x],board,y,x,rowWKing,colWKing)==1){
		    whiteInCheck=1;
		}
	    }
	}
    }
    


    /* check whether black king is in check */
    int blackInCheck=0;
    int rowBKing=-1;
    int colBKing=-1;

    /* check the current position of black king */
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            if(board[y][x]==-5){
                rowBKing=y;
                colBKing=x;
            }
        }
    }
    if(rowBKing<0||rowBKing>7||colBKing>7||colBKing<0){
//        printf("Black king is not on the board.\n");
	return 0;
    }

    /* check whether each white pieces are attacking black king */
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
	    if(board[y][x]>0){
	    	if(checkLegal(board[y][x],board,y,x,rowBKing,colBKing)==1){
		    blackInCheck=1;
		}
	    }
        }
    }
    if(whiteInCheck==1&&blackInCheck==1){
	return 3;
    }
    else if(whiteInCheck==1&&blackInCheck==0){
	return 2;
    }

    else if(blackInCheck==1&&whiteInCheck==0){
	return 1;
    }
    else{
	return 0;
    }
    return 0;
}



int checkmate(int board[8][8])
{	
    int side = 0;
    if(check4Check(board)==3){
	side=3;
    }
    else if(check4Check(board)==2){
	side=2;
    }
    else if(check4Check(board)==1){
	side=1;
    }
    else if(check4Check(board)==0){
	side=0;
	return 0;
    }
    int rowWKing=-1;
    int colWKing=-1;
    int rowBKing=-1;
    int colBKing=-1;
    int copyBoard[8][8];
    int checkMove=-1;
    int wCheckMate=1;
    int bCheckMate=1;
//    if(side==2||side==3){
	for(int x=0;x<8;x++){
            for(int y=0;y<8;y++){
            	if(board[y][x]==5){
                    rowWKing=y;
                    colWKing=x;
            	}
            }
    	}
        if(rowWKing<0||rowWKing>7||colWKing>7||colWKing<0){
//            printf("White King is not on the board.\n");
            return 0;
    	}

	for(int r=0;r<8;r++){
            for(int c=0;c<8;c++){
                 copyBoard[r][c]=board[r][c];
            }
        }

	for(int y=0;y<8;y++){
	    for(int x=0;x<8;x++){
		if(board[y][x]>0){
		    for(int j=0;j<8;j++){
			for(int i=0;i<8;i++){
			    if(moveTwo(copyBoard,y,x,j,i)==1){
				for(int r=0;r<8;r++){
        			    for(int c=0;c<8;c++){
            				copyBoard[r][c]=board[r][c];
        			    }
    				}
				checkMove=moveTwo(copyBoard,y,x,j,i);
				if(check4Check(copyBoard)!=2&&check4Check(copyBoard)!=3){
//				    printf("There is a move to get out of check for white.\n");
				    wCheckMate=0;
				}
			    }
			    for(int r=0;r<8;r++){
                                for(int c=0;c<8;c++){
                                    copyBoard[r][c]=board[r][c];
                                }
                            }
			}
		    }
		}
	    }
	}
//    }

    for(int r=0;r<8;r++){
        for(int c=0;c<8;c++){
            copyBoard[r][c]=board[r][c];
        }
    }
//    if(side==1||side==3){
	for(int x=0;x<8;x++){
            for(int y=0;y<8;y++){
                if(board[y][x]==-5){
                    rowBKing=y;
                    colBKing=x;
                }
            }
        }
        if(rowBKing<0||rowBKing>7||colBKing>7||colBKing<0){
//            printf("Black King is not on the board.\n");
            return 0;
        }
        for(int y=0;y<8;y++){
            for(int x=0;x<8;x++){
                if(board[y][x]<0){
                    for(int j=0;j<8;j++){
                        for(int i=0;i<8;i++){
                            if(moveTwo(copyBoard,y,x,j,i)==1){
                                for(int r=0;r<8;r++){
                                    for(int c=0;c<8;c++){
                                        copyBoard[r][c]=board[r][c];
                                    }
                                }
                                checkMove=moveTwo(copyBoard,y,x,j,i);
                                if(check4Check(copyBoard)!=1&&check4Check(copyBoard)!=3){
//                                    printf("There is a move to get out of check for black.\n");
                                    bCheckMate=0;
                                }
                            }
			    for(int r=0;r<8;r++){
                                for(int c=0;c<8;c++){
                                    copyBoard[r][c]=board[r][c];
                                }
                            }
                        }
                    }
                }
            }
        }
//    }
    if(bCheckMate==1){
	printf("White Wins!\n");
    }
    else if(wCheckMate==1){
	printf("Black Wins!\n");
    }    

    return 1;
}/*end of checkmate*/
/*EOF*/

int moveTwo(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
   int check=-1;
   int wK=-1;
   int wRR=-1;
   int wLR=-1;
   int bK=-1;
   int bRR=-1;
   int bLR=-1;
   int x= checkLegal(board[prevRow][prevCol],board,prevRow,prevCol,nextRow,nextCol);
   if(x==1){
        if(board[prevRow][prevCol]==5&&prevRow==7&&nextRow==7&&prevCol==4&&nextCol==6){
            board[7][6]=5;
            board[7][5]=1;
            board[7][7]=0;
            board[7][4]=0;
            wK=movedWKing(1);
            wRR=movedWRRook(1);
//            printf("King side castling for white is legal.\n");
        }
        else if(board[prevRow][prevCol]==5&&prevRow==7&&nextRow==7&&prevCol==4&&nextCol==2){
            board[7][2]=5;
            board[7][3]=1;
            board[7][0]=0;
            board[7][4]=0;
            wK=movedWKing(1);
            wLR=movedWLRook(1);
//            printf("Queen side castling for white is legal.\n");
        }
        else if(board[prevRow][prevCol]==-5&&prevRow==0&&nextRow==0&&prevCol==4&&nextCol==6){
            board[0][6]=5;
            board[0][5]=1;
            board[0][7]=0;
            board[0][4]=0;
            bK=movedBKing(1);
            bRR=movedBRRook(1);
//            printf("King side castling for black is legal.\n");
        }
        else if(board[prevRow][prevCol]==-5&&prevRow==0&&nextRow==0&&prevCol==4&&nextCol==2){
            board[0][2]=5;
            board[0][3]=1;
            board[0][0]=0;
            board[0][4]=0;
            bK=movedBKing(1);
            bLR=movedBLRook(1);
//            printf("Queen side castling for black is legal.\n");
        }
        else{
            board[nextRow][nextCol]=board[prevRow][prevCol];
            board[prevRow][prevCol]=0;
        }
        whitePawnPromotion(board);
        blackPawnPromotion(board);
        check=check4Check(board);
        if(check==3){
//            printf("Both are in check.\n");
        }
        else if(check==2){
//            printf("White is in check.\n");
        }
        else if(check==1){
//            printf("Black is in check.\n");
        }
        return 1;
   }
   else{
//        printf("Not able to move a piece.\n");
        return 0;
   }
    return 0;
}	

/*EOF*/	
