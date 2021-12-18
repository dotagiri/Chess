/**************************************************
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
 *
 * */


#include "moves.h"
#include <stdlib.h>
#include <stdio.h>

/* check diagonal direction */
int diagonalDirection(int prevRow, int prevCol, int nextRow, int nextCol){
    int direction=0; 
    /* check the legality of diagonal down right */
    for(int x=1;x<8;x++){
        if((prevRow+x==nextRow)&&(prevCol+x==nextCol)&&(prevRow+x<8)&&(prevCol+x<8)){
                direction=1;
                printf("The piece is moving diagonally down to the right.\n");
        }
    }

    /*check the legality of diagonal down left*/
    for(int x=1;x<8;x++){
        if((prevRow+x==nextRow)&&(prevCol-x==nextCol)&&(prevRow+x<8)&&(prevCol+x>=0)){
                direction=2;
                printf("The piece is moving diagonally down to the left.\n");
        }
    }

    /*check the legality of diagonal up left*/
    for(int x=1;x<8;x++){
        if((prevRow-x==nextRow)&&(prevCol-x==nextCol)&&(prevRow+x>=0)&&(prevCol+x>=0)){
                direction=3;
                printf("The piece is moving diagonally up to the left.\n");
        }
    }

    /* check the legality of diagonal up right */
    for(int x=1;x<8;x++){
        if((prevRow-x==nextRow)&&(prevCol+x==nextCol)&&(prevRow+x>=0)&&(prevCol+x<8)){
                direction=4;
                printf("The piece is moving diagonally up to the right.\n");
        }
    }
    if(direction==0){
	printf("The move is not diagonal.\n");
    }
    return direction;
}

/* check legality of diagonal move*/
int checkDiagonal(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
    int direction=diagonalDirection(prevRow, prevCol, nextRow, nextCol);
    if(direction<1||direction>4){
	printf("The move is not diagonal.\n");
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
                printf("It's a valid move.\n");
                return 1;
            }
            else{   
                printf("Blocked piece in the diagonal down right.\n");
                return 0;
            }
	}
        else if(board[prevRow+x][prevCol+x]==0){
            if(prevRow+x==nextRow&&prevCol+x==nextCol&&prevRow+x<8&&prevCol+x<8){
                printf("It is a valid move.\n");
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
                printf("It's a valid move.\n");
                return 1;
            }
            else{
                printf("Blocked piece in the diagonal down left.\n");
                return 0;
            }
	}
        else if(board[prevRow+x][prevCol-x]==0){
            if(prevRow+x==nextRow&&prevCol-x==nextCol&&prevRow+x<8&&prevCol+x>=0){
                printf("It is a valid move.\n");
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
                printf("It's a valid move.\n");
                return 1;
            }
            else{
                printf("Blocked piece in the diagonal up left.\n");
                return 0;
            }
        }
        else if(board[prevRow-x][prevCol-x]==0){
            if(prevRow-x==nextRow&&prevCol-x==nextCol&&prevRow+x>=0&&prevCol+x>=0){
                printf("It is a valid move.\n");
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
                printf("It's a valid move for bishop.\n");
                return 1;
            }
            else{
                printf("Blocked piece in the diagonal up right.\n");
                return 0;
            }
        }
        else if(board[prevRow-x][prevCol+x]==0){
            if(prevRow-x==nextRow&&prevCol+x==nextCol&&prevRow+x>=0&&prevCol+x<8){
                printf("It is a valid move.\n");
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
            printf("It's a legal move.\n");
            return 1;
        }
        /* check the legality when the piece moves horizontally to the left*/
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
            printf("It's a legal move.\n");
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
            printf("It's a legal move.\n");
            return 1;
        }
        /* check the legality when the piece moves vertially upward */
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
            printf("It's a legal move.\n");
            return 1;
        }
    }
    return 0;

}

/* moves a piece from one location on the board to the next */
int move(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
   
   int x= checkLegal(board[prevRow][prevCol],board,prevRow,prevCol,nextRow,nextCol);
   if(x==1){
	board[nextRow][nextCol]=board[prevRow][prevCol];
	board[prevRow][prevCol]=0;
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
	int validFlag;

	if (board[prevRow][prevCol] != 6 && board[prevRow][prevCol] != -6){ //check if the piece is a pawn
		printf("Moving piece is not a pawn.\n");
		return 0;
		} /*fi*/
	/*for white*/
	if (board[prevRow][prevCol]>0){ 
		if (prevRow == 6 && nextRow < prevRow-2){ //check if pawn moves more than 2 spaces from starting position
			printf("Move is invalid!\n");
			return 0;
			} /*fi*/
		else{ 
			validFlag = 1;
			} /*esle*/	

		if (prevRow != 6 && nextRow > prevRow-1){ //check if pawn moves more than 1 space
			printf("Move is invalid!\n");
			return 0;
			} /*fi*/

		else{ 
			validFlag = 1;
			} /*esle*/
		for (x=prevRow-1; x>=nextRow; x--){ //for every space moved
			if (board[x][prevCol] != 0 && x != nextRow){ /*check for piece*/
				printf("There is a piece blocking its way!\n");
				return 0;
				} /*fi*/
			else if(x == nextRow){ /*checks for ally */
				if(board[nextRow][nextCol]*board[prevRow][prevCol]>0){
					printf("There is an ally piece blocking its way!\n");
					return 0;
					} /*fi*/
				} /*fi*/
			} /*rof*/
		
		/*white capturing black*/
		if (validFlag == 1 && board[nextRow][nextCol]<0){ 
			board[nextRow][nextCol] = 6;
			printf("Move is valid!\n");
			return 1;
			}/*fi*/
		} /*fi*/
	
	/*for black*/
	if (board[prevRow][prevCol]<0){
		if (prevRow == 1 && nextRow > prevRow+2){ //check if pawn moves more than 2 spaces from starting
			printf("Move is invalid!\n");
			return 0;
			} /*fi*/
		else{
			validFlag = 1;
			} /*esle*/

		if (prevRow != 1 && nextRow > prevRow+1){ //check if pawn moves more than 1 space
			printf("Move is invalid!\n");
			return 0;
			} /*fi*/
		else{
			validFlag = 1;
			} /*esle*/
		
		for (x=prevRow+1; x<=nextRow; x++){ //for every space moved
			if(board[x][prevCol]!=0 && x!= nextRow){ //if there is piece in square
				printf("There is a piece blocking its way!\n");
				return 0;	
				} /*fi*/
			else if (x == nextRow){ /*check for ally piece*/
				if(board[nextRow][nextCol]*board[prevRow][prevCol]>0){
					printf("There is an ally piece blocking its way!\n");
					return 0;
					} /*fi*/
				}/*fi*/
			}/*rof*/
		
		/*black captures white*/	
		if (validFlag == 1 && board[nextRow][nextCol]>0){ 
			board[nextRow][nextCol] = -6;
			printf("Move is valid!\n");
			return 1;
			}/*fi*/
		} /*fi*/
	/*cannot move diagonally if not capturing*/	
	if (prevCol != nextCol) {
		printf("Move is invalid!\n");
		return 0;
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
    if ( (rowCondition == 1 || rowCondition == -1)&&(colCondition==0)&&(board[prevRow][prevCol]*board[nextRow][nextCol]<=0) ) {
	printf("Legal vertical move.\n");
        return 1;
    }

    /* check legality for horizontal movement */
    if( (colCondition == 1 || colCondition == -1)&&(rowCondition==0)&&(board[prevRow][prevCol]*board[nextRow][nextCol]<=0) ) {
	printf("Legal horizontal move.\n");
        return 1;
    }

    /* check legality for diagonal down left */
    if((colCondition ==1||colCondition==-1)&&(rowCondition==1||rowCondition==-1)){
	printf("Legal diagonal move.\n");
	return 1;
    }

    printf("It is not a legal move for king.\n");
    return 0;
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
        printf("Moving piece is not bishop.\n");
        return 0;
    }
    /* check diagonal move*/
    int check=checkDiagonal(board,prevRow, prevCol, nextRow, nextCol);
    if(check==0){
	printf("Illegal move for bishop.\n");
	return 0;
    }
    else if(check==1){
	printf("Legal move for bishop.\n");
	return 1;
    }    
    return 0;
} /*end of checkBishop*/ 

/* check the legality of the queen move */
int checkQueen(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol){
    if ( board[prevRow][prevCol] != 4 &&  board[prevRow][prevCol] != -4 ){
        printf("Moving piece is not queen.\n");
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
        printf("White King is not on the board.\n");
	return 0;
    }

    /* check whether each black pieces are attacking white king */
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            if(board[y][x]==-1){
                if(checkRook(board,y,x,rowWKing,colWKing)==1){
                    whiteInCheck=1;
                    printf("White king is attacked by the rook.\n");
                }
            }
            else if(board[y][x]==-2){
                if(checkKnight(board,y,x,rowWKing,colWKing)==1){
                    whiteInCheck=1;
                    printf("White king is attacked by the knight.\n");
                }
            }
            else if(board[y][x]==-3){
                if(checkBishop(board,y,x,rowWKing,colWKing)==1){
                    whiteInCheck=1;
                    printf("White king is attacked by the bishop.\n");
                }
            }
            else if(board[y][x]==-4){
                if(checkQueen(board,y,x,rowWKing,colWKing)==1){
                    whiteInCheck=1;
                    printf("White king is attacked by the queen.\n");
                }
            }
            else if(board[y][x]==-5){
                if(checkKing(board,y,x,rowWKing,colWKing)==1){
                    whiteInCheck=1;
                    printf("White king is attacked by the king.\n");
                }
            }
            else if(board[y][x]==-6){
                if(checkPawn(board,y,x,rowWKing,colWKing)==1){
                    whiteInCheck=1;
                    printf("White king is attacked by the pawn.\n");
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
        printf("Black king is not on the board.\n");
	return 0;
    }

    /* check whether each white pieces are attacking black king */
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            if(board[y][x]==1){
                if(checkRook(board,y,x,rowWKing,colWKing)==1){
                    blackInCheck=1;
                    printf("Black king is attacked by the rook.\n");
                }
            }
            else if(board[y][x]==2){
                if(checkKnight(board,y,x,rowWKing,colWKing)==1){
                    blackInCheck=1;
                    printf("Black king is attacked by the knight.\n");
                }
            }
            else if(board[y][x]==3){
                if(checkBishop(board,y,x,rowWKing,colWKing)==1){
                    blackInCheck=1;
                    printf("Black king is attacked by the bishop.\n");
                }
            }
            else if(board[y][x]==4){
                if(checkQueen(board,y,x,rowWKing,colWKing)==1){
                    blackInCheck=1;
                    printf("Black king is attacked by the queen.\n");
                }
            }
            else if(board[y][x]==5){
                if(checkKing(board,y,x,rowWKing,colWKing)==1){
                    blackInCheck=1;
                    printf("Black king is attacked by the king.\n");
                }
            }
            else if(board[y][x]==6){
                if(checkPawn(board,y,x,rowWKing,colWKing)==1){
                    blackInCheck=1;
                    printf("Black king is attacked by the pawn.\n");
                }
            }
        }
    }

    if(whiteInCheck==1&&blackInCheck==1){
        printf("Both in check.\n");
	return 3;
    }

    else if(whiteInCheck==1&&blackInCheck==0){
	printf("White is in check.\n");
	return 2;
    }

    else if(blackInCheck==1&&whiteInCheck==0){
        printf("Black is in check.\n");
	return 1;
    }
    else{
	printf("Exception.\n");
	return 0;
    }
    return 0;
}


int checkmate(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol)
{	
	//0 not in checkmate
	//1 in checkmate
	//5 = king	
	int x;

	int check = check4Check(board);
	if (check == 1){
		x = checkKing(board, prevRow, prevCol, nextRow, nextCol);
		if (x == 0){
			printf("There are no legal moves available\n");
			/*white wins*/
			if (board[prevRow][prevCol]==-5){
				printf("Game Over! White wins!\n");
				return 1;
				} /*fi*/
			/*black wins*/
			if(board[prevRow][prevCol] == 5){
				printf("Game Over! Black wins!\n");
				return 1;
				} /*fi*/
			} /*fi*/
		} /*fi*/
	else if(check != 0){
		return 0; 
		} /*esle*/
	return 0; 			
}/*end of checkmate*/
/*EOF*/	
