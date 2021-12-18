/**************************************************
 * Changes made:
 * 04/24/2020 - Daisuke -  added checkPawn function, 
 * 			   added out of bounds condiitonal to checkLegal,
 * 			   removed out of bounds if in every function (checkPiece) 
 * 04/25/2020 - Daisuke -  debugged checkPawn	
 *
 *
 *
 *
 *
 *
 * */


#include "moves.h"
#include <stdlib.h>
#include <stdio.h>

/* moves a piece from one location on the board to the next */
int move(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
    int x= checkLegal(board[prevRow][prevCol],board,prevRow,prevCol,nextRow,nextCol);
    if(x==1){
	board[nextRow][nextCol]=board[prevRow][prevCol];
	board[prevRow][prevCol]=0;
    }
    else{
	printf("Not able to move a piece.\n");	
    }
    return 0;
}

/* check whether a move is legal */
int checkLegal(int piece,int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
    int n=0;

    if( prevRow<0 || prevRow>7 || prevCol<0 || prevCol>7 || nextRow<0 || nextRow>7 || nextCol<0 || nextCol>7){ /*out of bounds check*/
	printf("Position is out of bound.\n");
        return 0;
    	} /*fi*/ 
	
    if(piece==1||piece==-1){
	n=checkRook(board,prevRow,prevCol,nextRow, nextCol);
    	if(n==1){
	    return 1;
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
/* check legality of pawn movement, return 1 for legal and 0 for illegal*/

int checkPawn(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
	int x;

	/*i,j = the move function that returns the position*/
	if (board[prevRow][prevCol] != 6 && board[prevRow][prevCol] != -6){ //check if the piece is a pawn
		printf("Moving piece is not a pawn.\n");
		return 0;
		} /*fi*/
	if (prevCol != nextCol){ /*make sure column remains the same*/
		printf("Move is invalid!");
		return 0;
		} /*fi*/
	if (board[prevRow][prevCol]>0){ /*for white*/
		if (prevRow == 6 && nextRow < prevRow-2){ //check if pawn moves more than 2 spaces from starting position
			printf("Move is invalid!");
			return 0;
			} /*fi*/
		else{ 
			printf("Move is valid!");
			return 1; 
			} /*esle*/	

		if (prevRow != 6 && nextRow > prevRow-1){ //check if pawn moves more than 1 space
			printf("Move is invalid!");
			return 0;
			} /*fi*/

		else{ 
			printf("Move is valid!");
			return 1; 
			} /*esle*/
	
		for (x=prevRow; x<nextRow; x++){ //for every space moved
			if((board[x][nextCol]!=0)){ //checks if there is a piece in the square
				printf("There is an ally piece blocking its way!\n");
				return 0;
				} /*fi*/
			else{ return 1; }
			} /*rof*/
		} /*fi*/	
	if (board[prevRow][prevCol]<0){ /*for black*/
		if (prevRow == 1 && nextRow > prevRow+2){ //check if pawn moves more than 2 spaces from starting
			printf("Move is invalid!");
			return 0;
			} /*fi*/
		else{
			printf("Move is valid!");
			return 1;
			} /*esle*/

		if (prevRow != 1 && nextRow > prevRow+1){ //check if pawn moves more than 1 space
			printf("Move is invalid!");
			return 0;
			} /*fi*/
		else{
			printf("Move is valid!");
			return 1;
			} /*esle*/

		for (x=prevRow; x<nextRow; x++){ //for every space moved
			if(board[x][nextCol]!=0){ //if there is piece in square
				printf("There is an ally piece blocking its way!\n");
				return 0;	
				} /*fi*/
			else{ return 1; }
			}/*rof*/
		} /*fi*/
	return 1;
	}/*end of checkPawn*/
/* check the legality of the king move; return 1 for legal and 0 for illegal */
int checkKing(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
    
    if ( board[prevRow][prevCol] != 5 &&  board[prevRow][prevCol] != -5 ){
	printf("Moving piece is not king.\n");
	return 0;
    }


    int rowCondition = prevRow - nextRow;
    int colCondition = prevCol - nextCol;

    /* check legality for vertical movement */
    if ( rowCondition != 1 && rowCondition != -1 ) {
	printf("Illegal vertical move.\n");
        return 0;
    }

    /* check legality for horizontal movement */
    if( colCondition != 1 && colCondition != -1 ) {
	printf("Illegal horizontal move.\n");
        return 0;
    }

    /* check whether there is any ally pieces */
    if(board[prevRow][prevCol]*board[nextRow][nextCol]>0){
	printf("There is an ally piece.\n");
        return 0;
    }
    printf("It is a legal move for king.\n");
    return 1;
}

/* check the legality of the knight move; return 1 for legal and 0 for illegal */
int checkKnight(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol) {
    if ( board[prevRow][prevCol] != 2 &&  board[prevRow][prevCol] != -2 ){
	printf("Moving piece is not knight.\n");
	return 0;
    }


    int rowCondition = prevRow - nextRow;
    int colCondition = prevCol - nextCol;

    if(((rowCondition==1||rowCondition==-1)&&(colCondition==2||colCondition==-2) )||((rowCondition==2||rowCondition==-2)&&(colCondition==1||colCondition==-1))){
	if(board[prevRow][prevCol]*board[nextRow][nextCol]<=0){
        	printf("It is a legal move for knight.\n");
		return 1;
        }
        else if(board[prevRow][prevCol]*board[nextRow][nextCol]>0){
		printf("There is an ally piece.\n");
                return 0;
        }
    }
        return 0;
}

/* check the legality of the rook move; return 1 for legal and 0 for illegal */
int checkRook(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol) {
    if(board[prevRow][prevCol] != 1 &&  board[prevRow][prevCol] != -1 ){
	printf("Moving piece is not rook.\n");
        return 0;
    }

     if(((prevRow==nextRow) && (prevCol!=nextCol)) || ((prevCol==nextCol)&&(prevRow!=nextRow))){
	
	/* check the legality when the rook moves horizontally */
	if((prevRow==nextRow) && (prevCol!=nextCol)){
		/* check the legality when rook moves horizontally to the right*/
		if(prevCol-nextCol<0){
			for(int x=prevCol+1;x<=nextCol;x++){
				if((board[prevRow][x]!=0)&&(x!=nextCol)){
					printf("There is a piece blocking its way on its right.\n");
					return 0;
				}
				else if(x==nextCol){
					if(board[nextRow][nextCol]*board[prevRow][prevCol]>0){
					printf("There is an ally piece in the final position.\n");	
					return 0;
					}
				}
			}
			printf("It's a legal move for rook.\n");
			return 1;
		}
		/* check the legality when rook moves horizontally to the left*/
		else if(prevCol-nextCol>0){
			for(int x=prevCol-1;x>=nextCol;x--){
                		if((board[prevRow][x]!=0)&&(x!=nextCol)){
                         		printf("There is a piece blocking its way on its left.\n");
					return 0;
                                }
				else if(x==nextCol){
					if(board[nextRow][nextCol]*board[prevRow][prevCol]>0){
						printf("There is an ally piece in the final position.\n");
						return 0;
					}
				}
			}
			printf("It's a legal move for rook.\n");
                	return 1;
		}
	}
	/* check the legality when rook moves vertically */
	else if((prevCol==nextCol)&&(prevRow!=nextRow)){
		/* check the legality when rook moves vertically downward */
		if(prevRow-nextRow<0){
			for(int x=prevRow+1;x<=nextRow;x++){
                                if((board[x][prevCol]!=0)&&(x!=nextRow)){
                                        printf("There is a piece blocking its way at its bottom.\n");
					return 0;
                                }
                                else if(x==nextRow){
                                        if(board[nextRow][nextCol]*board[prevRow][prevCol]>0){
                                                printf("There is an ally piece in the final position.\n");
						return 0;
                                        }
                                }
                        }
			printf("It's a legal move for rook.\n");
                	return 1;
		}
		/* check the legality when rook moves vertially upward */
		else if(prevRow-nextRow>0){
			for(int x=prevRow-1;x>=nextRow;x--){
                                if((board[x][prevCol]!=0)&&(x!=nextRow)){
                                        printf("There is a piece blocking its way at its top.\n");
					return 0;
                                }
                                else if(x==nextRow){
                                        if(board[nextRow][nextCol]*board[prevRow][prevCol]>0){
                                                printf("There is an ally piece in the final position.\n");
						return 0;
                                        }
                                }
                        }
			printf("It's a legal move for rook.\n");
                        return 1;
		}
	}
    }
    return 0;
} /*end of checkRook*/

/* check the legality of the bishop move; return 1 for legal and 0 for illegal */
int checkBishop(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol) {
    if ( board[prevRow][prevCol] != 3 &&  board[prevRow][prevCol] != -3 ){
        printf("Moving piece is not bishop.\n");
        return 0;
    }

    
    int direction=0; /*determine the direction of the diagonal */

    /*locate whether the final position is in the direction of the diagonal*/
    /* check the legality of diagonal down right */
    for(int x=1;x<8;x++){
	if((prevRow+x==nextRow)&&(prevCol+x==nextCol)&&(prevRow+x<8)&&(prevCol+x<8)){
		direction=1;
		printf("Bishop is moving diagonally down to the right.\n");
	}	
    }

    /*check the legality of diagonal down left*/
    for(int x=1;x<8;x++){
	if((prevRow+x==nextRow)&&(prevCol-x==nextCol)&&(prevRow+x<8)&&(prevCol+x>=0)){
		direction=2;
		printf("Bishop is moving diagonally down to the left.\n");
	}	
    }
    
    /*check the legality of diagonal up left*/
    for(int x=1;x<8;x++){
        if((prevRow-x==nextRow)&&(prevCol-x==nextCol)&&(prevRow+x>=0)&&(prevCol+x>=0)){
                direction=3;
        	printf("Bishop is moving diagonally up to the left.\n");
	}
    }

    /* check the legality of diagonal up right */
    for(int x=1;x<8;x++){
        if((prevRow-x==nextRow)&&(prevCol+x==nextCol)&&(prevRow+x>=0)&&(prevCol+x<8)){
                direction=4;
                printf("Bishop is moving diagonally up to the right.\n");
        }
    }
    
    /* check whether there is any blocked piece */
    if(direction==1){
	for(int x=1;x<8;x++){
		if(board[prevRow+x][prevCol+x]!=0){
			if(prevRow+x==nextRow&&prevCol+x==nextCol&&board[prevRow][prevCol]*board[nextRow][nextCol]<=0){
				printf("It's a valid move for bishop.\n");
				return 1;
			}
			else{
				printf("Blocked piece in the diagonal down right.\n");
				return 0;
			}
		}
	}
    }
    else if(direction==2){
	for(int x=1;x<8;x++){
                if(board[prevRow+x][prevCol-x]!=0){
                        if(prevRow+x==nextRow&&prevCol-x==nextCol&&board[prevRow][prevCol]*board[nextRow][nextCol]<=0){
                                printf("It's a valid move for bishop.\n");
                                return 1;
                        }
                        else{
                                printf("Blocked piece in the diagonal down left.\n");
                                return 0;
                        }
                }
        }
    }
    else if(direction==3){
	for(int x=1;x<8;x++){
                if(board[prevRow-x][prevCol-x]!=0){
                        if(prevRow-x==nextRow&&prevCol-x==nextCol&&board[prevRow][prevCol]*board[nextRow][nextCol]<=0){
                                printf("It's a valid move for bishop.\n");
                                return 1;
                        }
                        else{
                                printf("Blocked piece in the diagonal up left.\n");
                                return 0;
                        }
                }
        }
    }
    else if(direction==4){
	for(int x=1;x<8;x++){
                if(board[prevRow-x][prevCol+x]!=0){
                        if(prevRow-x==nextRow&&prevCol+x==nextCol&&board[prevRow][prevCol]*board[nextRow][nextCol]<=0){
                        	printf("It's a valid move for bishop.\n");
                                return 1;
                        }
                        else{
                                printf("Blocked piece in the diagonal up right.\n");
                                return 0;
                        }
                }
        }
    }
    else if(direction==0){
	printf("Move is not diagonal which is illegal for bishop.\n");
	return 0;
    }
    return 0;
} /*end of checkBishop*/ 

/* check the legality of the queen move */
int checkQueen(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
    if ( board[prevRow][prevCol] != 4 &&  board[prevRow][prevCol] != -4 ){
        printf("Moving piece is not queen.\n");
        return 0;
    }

    /* check whether the initial and final position is in the range of the board */
    if( prevRow<0 || prevRow>7 || prevCol<0 || prevCol>7 || nextRow<0 || nextRow>7 || nextCol<0 || nextCol>7){
        printf("Position is out of bound.\n");
        return 0;
    }
    
    /* check the legality when the queen moves horizontally */
    if((prevRow==nextRow) && (prevCol!=nextCol)){
	/* check the legality when queen moves horizontally to the right*/
        if(prevCol-nextCol<0){
            for(int x=prevCol+1;x<=nextCol;x++){
                if((board[prevRow][x]!=0)&&(x!=nextCol)){
                    printf("There is a piece blocking its way on its right.\n");
                    return 0;
                }
                else if(x==nextCol){
                    if(board[nextRow][nextCol]*board[prevRow][prevCol]>0){
                        printf("There is an ally piece in the final position.\n");
                        return 0;
                    }
                }
            }
            printf("It's a legal move for queen.\n");
            return 1;
	}
        /* check the legality when queen moves horizontally to the left*/
        else if(prevCol-nextCol>0){
	    for(int x=prevCol-1;x>=nextCol;x--){
                if((board[prevRow][x]!=0)&&(x!=nextCol)){
                    printf("There is a piece blocking its way on its left.\n");
                    return 0;
                }
                else if(x==nextCol){
                    if(board[nextRow][nextCol]*board[prevRow][prevCol]>0){
                        printf("There is an ally piece in the final position.\n");
                        return 0;
                    }
                }
            }
            printf("It's a legal move for queen.\n");
            return 1;
        }
    }
    
    /* check the legality when queen moves vertically */
    else if((prevCol==nextCol)&&(prevRow!=nextRow)){
        /* check the legality when queen moves vertically downward */
        if(prevRow-nextRow<0){
            for(int x=prevRow+1;x<=nextRow;x++){
                if((board[x][prevCol]!=0)&&(x!=nextRow)){
                    printf("There is a piece blocking its way at its bottom.\n");
                    return 0;
                }
                else if(x==nextRow){
                    if(board[nextRow][nextCol]*board[prevRow][prevCol]>0){
                        printf("There is an ally piece in the final position.\n");
                        return 0;
                    }
                }
            }
            printf("It's a legal move for queen.\n");
            return 1;
	}          
        /* check the legality when queen moves vertially upward */
        else if(prevRow-nextRow>0){
            for(int x=prevRow-1;x>=nextRow;x--){
                if((board[x][prevCol]!=0)&&(x!=nextRow)){
                    printf("There is a piece blocking its way at its top.\n");
                    return 0;
                }
                else if(x==nextRow){
                    if(board[nextRow][nextCol]*board[prevRow][prevCol]>0){
                        printf("There is an ally piece in the final position.\n");
                        return 0;
                    }
                }
            }
            printf("It's a legal move for queen.\n");
            return 1;
        }
    }

    int direction=0; /*determine the direction of the diagonal */

    /*locate whether the final position is in the direction of the diagonal*/
    /* check the legality of diagonal down right */
    for(int x=1;x<8;x++){
        if((prevRow+x==nextRow)&&(prevCol+x==nextCol)&&(prevRow+x<8)&&(prevCol+x<8)){
                direction=1;
                printf("Queen is moving diagonally down to the right.\n");
        }
    }

    /*check the legality of diagonal down left*/
    for(int x=1;x<8;x++){
        if((prevRow+x==nextRow)&&(prevCol-x==nextCol)&&(prevRow+x<8)&&(prevCol+x>=0)){
                direction=2;
                printf("Queen is moving diagonally down to the left.\n");        }
    }

    /*check the legality of diagonal up left*/
    for(int x=1;x<8;x++){
        if((prevRow-x==nextRow)&&(prevCol-x==nextCol)&&(prevRow+x>=0)&&(prevCol+x>=0)){
                direction=3;
                printf("Queen is moving diagonally up to the left.\n");
        }
    }

    /* check the legality of diagonal up right */
    for(int x=1;x<8;x++){
        if((prevRow-x==nextRow)&&(prevCol+x==nextCol)&&(prevRow+x>=0)&&(prevCol+x<8)){
                direction=4;
                printf("Queen is moving diagonally up to the right.\n");
        }
    }

    /* check whether there is any blocked piece */
    if(direction==1){
        for(int x=1;x<8;x++){
                if(board[prevRow+x][prevCol+x]!=0){
                        if(prevRow+x==nextRow&&prevCol+x==nextCol&&board[prevRow][prevCol]*board[nextRow][nextCol]<=0){
                                printf("It's a valid move for queen.\n");
                                return 1;
                        }
                        else{
                                printf("Blocked piece in the diagonal down right.\n");
                                return 0;
                        }
                }
        }
    }
    else if(direction==2){
        for(int x=1;x<8;x++){
                if(board[prevRow+x][prevCol-x]!=0){
                        if(prevRow+x==nextRow&&prevCol-x==nextCol&&board[prevRow][prevCol]*board[nextRow][nextCol]<=0){
                                printf("It's a valid move for queen.\n");
                                return 1;
                        }
                        else{
                                printf("Blocked piece in the diagonal down left.\n");
                                return 0;
                        }
                }
        }
    }
    else if(direction==3){
        for(int x=1;x<8;x++){
                if(board[prevRow-x][prevCol-x]!=0){
                        if(prevRow-x==nextRow&&prevCol-x==nextCol&&board[prevRow][prevCol]*board[nextRow][nextCol]<=0){
                                printf("It's a valid move for queen.\n");
                                return 1;
                        }
                        else{
                                printf("Blocked piece in the diagonal up left.\n");
                                return 0;
                        }
                }
        }
    }
    else if(direction==4){
        for(int x=1;x<8;x++){
                if(board[prevRow-x][prevCol+x]!=0){
                        if(prevRow-x==nextRow&&prevCol+x==nextCol&&board[prevRow][prevCol]*board[nextRow][nextCol]<=0){
                                printf("It's a valid move for queen.\n");
                                return 1;
                        }
                        else{
                                printf("Blocked piece in the diagonal up right.\n");
                                return 0;
                        }
                }
        }
    }
    else if(direction==0){
        printf("Move is not diagonal which is illegal for queen.\n");
        return 0;
    }

    return 0;
} /*end of checkQueen*/

/*EOF*/	
