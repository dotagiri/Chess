/********DO NOT MODIFY THIS SECTION************
 * 
 * EECS 22 : Advanced C Programming
 * Winter 2020, Prof. Quoc-Viet Dang
 * 
 * HW1  : Bingo Simulator
 * Template file : Bingo.c
 * 
 * Created on Jan 5, 2020, 10:56 PM by Bo Tsai <bo.tsai@uci.edu>
 */
/**********************************************
 
// Enter your name, last name and UCInet ID below://
 * 
 * *****************************
 * First Name : Daisuke  
 * Last Name: Otagiri
 * UCInet ID: dotagiri
 *
 */

#include <stdio.h>
#include <stdlib.h>
/*Declare your function definitions in the section below*/
/*You may add other functions if needed*/
/*********************************************************/
/* * int bingoCalled - compares caller number and board and checks for bingo
   * main - opens and reads file, calls other functions */

/*********************************************************/

/*Declare your global variables below (if any)*/
/**************************************************/
int i,j,k,p;
int players = 0;
int board_dimension = 0; 
int max_dimension = 256;
int max_players = 10;
int max_characters = 64;
/**************************************************/

/* (you can add or remove from thisM  "\x1B[0m"
 */ 
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"


/*File open and read function*/
void bingoCalled (char name[players][max_characters], int board[players][board_dimension][board_dimension], int caller)
{
	int counter = 0;
	int bingoChecker[players];
	printf("Begin Bingo Game!");
	for (p=0;p<caller;p++){
		printf("Caller called %d",caller);
		for (i=0; i<players; i++){
			
			if (bingoChecker[players] == 1){	
				printf("*** %s Bingo! ***\n", name[i]);
				printf("%d",board[i][j][k]);
				printf("The game result:\n");
				printf("%d", caller);
				while (bingoChecker[i]==1){
					printf(" %s",name[i]);
				} /* end of while*/
				exit(1); /*end the game if someone won*/
				} /*fi*/
			else {
				printf("*** %s ***",name[i]);
				}			
			for (j=0;j<board_dimension;j++){
				for(k=0; k<board_dimension ;k++) {
					if (caller == board[i][j][k]){
						board[i][j][k] = -1;
						counter = counter + 1;
						if (counter==board_dimension){	/*caller matches size of board then soemone must have bingo*/
							bingoChecker[i]=1;	/*Marks player with Bingo*/
							counter = 0;
						} /*fi*/
					printf("%d",board[i][j][k]);
					} /*rof*/
				}/*rof*/
			} /*rof*/
		}/*rof*/
	}/*rof*/
}
	 
int main(int argc, char** argv) {
	/*variable declarations*/
	int board_dimension = 0; 
	int max_dimension = 256;
	int max_players = 10;
	int max_characters = 64;

	FILE *fp;
	
	/*File reading*/
	fp = fopen("BingoInput.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "Can't open input file BingoInput.txt!\n");
		exit (1);
	}/*fi*/

	fscanf(fp,"%d %d", &players, &board_dimension);
	if (players > max_players ){
		printf("Cannot have more than 10 players");
		exit(1);
		} /*fi*/
	else if (board_dimension>max_dimension){
		printf("Board size cannot exceed 256x256!");
		exit(1);
		} /*fi*/
	
	char name[players][max_characters];
	int board[players][board_dimension][board_dimension];
	int caller[board_dimension];
	int bingoChecker[players];

	for (i=0; i<players;i++){
		bingoChecker[i]=0;
		} /*rof*/
	
	for (i=0; i<players; i++){
		fgets(name[i], max_characters,fp); /*get name of every player*/
		printf("%s",name[i]); /*print out name*/
		for (j=0;j<board_dimension;j++){
			for(k=0; k<board_dimension ;k++) {
				fscanf(fp, "%d",&board[i][j][k]);
				printf("%d",board[i][j][k]);
				} /*rof*/
			}/*rof*/
		} /*rof*/
	
	/*read caller numbers*/
	for(i=0;i<board_dimension; i++){
		fscanf(fp,"%d",&caller[i]);
		}/*rof*/
	
	printf("\n");
	fclose(fp);
	return (0);
}

/* EOF */
