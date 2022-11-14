// special_moves.c

#include <stdio.h>
#include "conversion.h"
#include "special_moves.h"
#include "moves.h"
#include "setFlag.h"
 
int whiteEnPassant(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol)
{
	if((prevRow == 3) && (prevCol-1>=0) && (board[prevRow][prevCol-1]<0)
		&& (nextRow == prevRow-1) && (nextCol == prevCol-1)){ //diagonal left
		return 1;
		} /*fi*/
	else if ((prevRow == 3) && (prevCol+1 <= 7) && (board[prevRow][prevCol+1]<0) 
		&& (nextRow == prevRow-1) && (nextCol == prevCol+1)){ //diagonal right
		return 1;
		}
	else {
		return 0;
		}	
	return 0;
}

int blackEnPassant(int board[8][8], int prevRow, int prevCol, int nextRow, int nextCol)
{
	if((prevRow == 4) && (prevCol-1>=0) && (board[prevRow][prevCol-1]>0)
		&& (nextRow == prevRow+1) && (nextCol == prevCol-1)){ //diagonal left
		return 1;
		} /*fi*/
	else if ((prevRow == 4) && (prevCol+1 <= 7) && (board[prevRow][prevCol+1]>0) 
		&& (nextRow == prevRow+1) && (nextCol == prevCol+1)){ //diagonal right
		return 1;
		}
	else {
		return 0;
		}	
	return 0;
}

int castleKingSide(int board[8][8], const int currRow, const int currCol, const int nextRow, const int nextCol)
{   
    int boardOne[8][8];
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            boardOne[i][j]=board[i][j];
	}
    }
    /* check white side */
    if((movedWKing(0)==0)&&(movedWRRook(0)==0)&&(board[currRow][currCol]==5)&&(board[7][7]==1)&&(currRow==7)&&(nextRow==7)&&(currCol==4)&&(nextCol==6)&&(board[7][5]==0)&&(board[7][6]==0)){
	if(check4Check(board)==2||check4Check(board)==3){
//	    printf("Cannot castle. White is in check now.\n");
	    return 0;
	}
	boardOne[7][5]=1;
	boardOne[7][4]=0;
	if(check4Check(boardOne)==2||check4Check(boardOne)==3){
//	    printf("Cannot castle. White will be in check in its way.\n");
	    return 0;
	}
	boardOne[7][5]=0;
        boardOne[7][6]=1;
        if(check4Check(boardOne)==2||check4Check(boardOne)==3){
//            printf("Cannot castle. White will be in check after castling.\n");
	    return 0;
        }
//	printf("King side castling for white is legal.\n");
	return 1;
    }
    
    /* check black side */
    if((movedBKing(0)==0)&&(movedBRRook(0)==0)&&(board[currRow][currCol]==-5)&&(board[0][7]==-1)&&(currRow==0)&&(nextRow==0)&&(currCol==4)&&(nextCol==6)&&(board[0][5]==0)&&(board[0][6]==0)){
	if(check4Check(board)==1||check4Check(board)==3){
//	    printf("Cannot castle. Black is in check now.\n");
            return 0;
        }
        boardOne[0][5]=1;
        boardOne[0][4]=0;
        if(check4Check(boardOne)==1||check4Check(boardOne)==3){
//            printf("Cannot castle. Black will be in check in its way.\n");
	    return 0;
        }
        boardOne[0][5]=0;
        boardOne[0][6]=1;
        if(check4Check(boardOne)==1||check4Check(boardOne)==3){
//            printf("Cannot castle. Black will be in check after castling.\n");
	    return 0;
        }
//	printf("King side castling for black is legal.\n");
	return 1;
    }
//    printf("King side castling is illgal.\n");
    return 0;
}

int castleQueenSide(int board[8][8], const int currRow, const int currCol, const int nextRow, const int nextCol)
{
    int boardOne[8][8];
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            boardOne[i][j]=board[i][j];
        }
    }
    
    /* check white side */
    if((movedWKing(0)==0)&&(movedWLRook(0)==0)&&(board[currRow][currCol]==5)&&(board[7][0]==1)&&(currRow==7)&&(nextRow==7)&&(currCol==4)&&(nextCol==2)&&(board[7][1]==0)&&(board[7][2]==0)&&(board[7][3]==0)){
        if(check4Check(board)==2||check4Check(board)==3){
//            printf("Cannot castle. White is in check now.\n");
            return 0;
        }
        boardOne[7][3]=1;
        boardOne[7][4]=0;
        if(check4Check(boardOne)==2||check4Check(boardOne)==3){
//            printf("Cannot castle. White will be in check in its way.\n");
            return 0;
        }
        boardOne[7][3]=0;
        boardOne[7][2]=1;
        if(check4Check(boardOne)==2||check4Check(boardOne)==3){
//            printf("Cannot castle. White will be in check after castling.\n");
            return 0;
        }
//        printf("Queen side castling for white is legal.\n");
        return 1;
    }

    /* check black side */
    if((movedBKing(0)==0)&&(movedBLRook(0)==0)&&(board[currRow][currCol]==-5)&&(board[0][0]==-1)&&(currRow==0)&&(nextRow==0)&&(currCol==4)&&(nextCol==2)&&(board[0][1]==0)&&(board[0][2]==0)&&(board[0][3]==0)){
        if(check4Check(board)==1||check4Check(board)==3){
//            printf("Cannot castle. Black is in check now.\n");
            return 0;
        }
        boardOne[0][3]=1;
        boardOne[0][4]=0;
        if(check4Check(boardOne)==1||check4Check(boardOne)==3){
//            printf("Cannot castle. Black will be in check in its way.\n");
            return 0;
        }
        boardOne[0][3]=0;
        boardOne[0][2]=1;
        if(check4Check(boardOne)==1||check4Check(boardOne)==3){
//            printf("Cannot castle. Black will be in check after castling.\n");
            return 0;
        }
//        printf("Queen side castling for black is legal.\n");
        return 1;
    }
//    printf("Queen side castling is illegal.\n");
    return 0;
}

void whitePawnPromotion(int board[8][8])
{
	for (unsigned int i = 0; i < 8; ++i){
		if (board[0][i] == 6){
			printf("*** White Pawn Promotion! ***\n");
			board[0][i] = choosePiece(board, 0, i);		
		}
	}
}

void blackPawnPromotion(int board[8][8])
{
	for (unsigned int i = 0; i < 8; ++i){
		if (board[7][i] == -6){
			printf("*** Black Pawn Promotion! ***\n");
			board[7][i] = -choosePiece(board, 7, i);		
		}
	}
}

int choosePiece(int board[8][8], int row, int col)
{
	char chosenPiece = '\0';
	
	do {
		printf("Select a piece to replace your Pawn at %c%d (Q - queen, R - rook, B - bishop, N - knight): ", colIndex2ColLetter(col), arrayRow2ChessRow(row));

	scanf("%c", &chosenPiece);
	
	while (getchar() != '\n');
	} while (chosenPiece != 'Q' && chosenPiece != 'R' && chosenPiece != 'B' && chosenPiece != 'N');

	return newPiece(chosenPiece);
}

int newPiece(char piece)
{
	switch (piece){
		case 'Q':
			return 4;
		case 'R':
			return 1;
		case 'B':
			return 3;
		case 'N':
			return 2;
		default:
			return 0;
	}
}
