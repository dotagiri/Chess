# Makefile: Makefile for Team 13 Chess Program

# Variables
EXEC = chess aitesting
CC = gcc
CFLAGS = -ansi -std=c99 -Wall -g -c # with debugging feature
LFLAGS = -ansi -std=c99 -Wall -g 
OBJECTS = $(addprefix bin/, conversion.o  pvp.o board.o moves.o pvc.o main.o menu.o ChessRules.o aimoves.o aigetmoves.o ai.o special_moves.o setFlag.o)

# Default target
all: bin/chess

######################## Generate object files ########################
bin/%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@

######################### Generate executable #########################
# Target for ChessGame
bin/chess: $(OBJECTS)
	$(CC) $(LFLAGS) $^ -o $@

#Target for aitesting
bin/aitest: $(OBJECTS)
	$(CC) $(LFLAGS) $^ -o $@

############################### others ################################
# Target for clean
clean:
	rm -f bin/*.o bin/*.txt bin/chess


