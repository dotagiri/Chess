# Makefile: Makefile for Team 13 Chess Program

# Variables
EXEC = chess
CC = gcc
CFLAGS = -ansi -std=c99 -Wall -g -c # with debugging feature
LFLAGS = -ansi -std=c99 -Wall -g 

# Default target
all: chess

######################## Generate object files ########################
conversion.o: conversion.h conversion.c
	$(CC) $(CFLAGS) conversion.c -o conversion.o

pvc.o: pvc.c
	$(CC) $(CFLAGS) pvc.c -o pvc.o
	
pvp.o: pvp.c
	$(CC) $(CFLAGS) pvp.c -o pvp.o
  
board.o: board.h board.c	
	$(CC) $(CFLAGS) board.c -o board.o

moves.o: moves.h moves.c
	$(CC) $(CFLAGS) moves.c -o moves.o

special_moves.o: special_moves.h special_moves.c conversion.h
	$(CC) $(CFLAGS) special_moves.c -o special_moves.o

menu.o: menu.h menu.c
	$(CC) $(CFLAGS) menu.c -o menu.o

main.o: pvp.h main.c
	$(CC) $(CFLAGS) main.c -o main.o

ChessRules.o: ChessRules.h ChessRules.c
	$(CC) $(CFLAGS) ChessRules.c -o ChessRules.o

######################### Generate executable #########################
# Target for ChessGame
chess: conversion.o pvp.o board.o moves.o pvc.o main.o menu.o ChessRules.o
	$(CC) $(LFLAGS) conversion.o pvp.o board.o moves.o pvc.o main.o menu.o ChessRules.o -o chess

############################### others ################################
# Target for clean
clean:
	rm -f *.o $(EXEC)	
