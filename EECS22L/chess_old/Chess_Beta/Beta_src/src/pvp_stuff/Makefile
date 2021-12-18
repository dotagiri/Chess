
all: pvp.o board.o moves.o pvc.o main.o menu.o ChessRules.o
	gcc moves.o pvp.o board.o main.o pvc.o menu.o ChessRules.o -g -o pvp_final -ansi -std=c99 -Wall

pvp.o: pvp.c
	gcc -c pvp.c -g  -o pvp.o -ansi -std=c99 -Wall
  
board.o: board.c board.h
	gcc -c board.c -g -o board.o -ansi -std=c99 -Wall

moves.o: moves.c moves.h
	gcc -c moves.c -g -o moves.o -ansi -std=c99 -Wall

menu.o: menu.c menu.h
	gcc -c menu.c -g -o menu.o -ansi -std=c99 -Wall

main.o: main.c pvp.h
	gcc -c main.c -g -o main.o -ansi -std=c99 -Wall

ChessRules.o: ChessRules.c ChessRules.h
	gcc -c ChessRules.c -g -o ChessRules.o -ansi -std=c99 -Wall

pvc.o: pvc.c pvc.h
	gcc -c pvc.c -g -o pvc.o -ansi -std=c99 -Wall




clean:
	rm *o
	
#gcc -c FileIO.c -g  -o FileIO.o -ansi -std=c99 -Wall
