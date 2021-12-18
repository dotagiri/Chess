#######################################################################
# Homework Assignment 5, for EECS 22, Winter 2020
#
#
# Makefile: Makefile for HW 5
#
#######################################################################

# Variables
FLAGS = -ansi -std=c99 -Wall -g

# Default target
all: MovieLab

######################### Generate object files #######################
# Target for FileIO.o
FileIO.o: FileIO.c FileIO.h Constants.h 
	gcc -c $(FLAGS) FileIO.c -o FileIO.o 
# Target for DIPs.o
DIPs.o: DIPs.c DIPs.h Constants.h
	gcc -c $(FLAGS) DIPs.c -o DIPs.o 
# Target for Image.o
Image.o: Image.c Image.h
	gcc -c $(FLAGS) Image.c -o Image.o
	
# Target for other object files

#Target for ImageList.o
ImageList.o: ImageList.c ImageList.h
	gcc -c $(FLAGS) ImageList.c -o ImageList.o

#Target for Movie.o
Movie.o: Movie.c Movie.h
	gcc -c $(FLAGS) Movie.c -o Movie.o 

#Target for MovieLab.o
MovieLab.o: MovieLab.c FileIO.h DIPs.h Movie.h Constants.h Image.h MovieIO.h IterativeFilter.h
	gcc -c $(FLAGS) MovieLab.c -o MovieLab.o

#Target for MovieIO.o
MovieIO.o: MovieIO.c MovieIO.h Constants.h
	gcc -c $(FLAGS) MovieIO.c -o MovieIO.o

#Target for IterativeFilter.o
IterativeFilter.o: IterativeFilter.c IterativeFilter.h
	gcc -c $(FLAGS) IterativeFilter.c -o IterativeFilter.o

######################### Generate the executable #####################
# Target for MovieLab

MovieLab: MovieLab.o FileIO.o DIPs.o Movie.o Image.o ImageList.o MovieIO.o IterativeFilter.o
	gcc -lm $(FLAGS) -L. FileIO.o DIPs.o Movie.o Image.o ImageList.o MovieIO.o IterativeFilter.o MovieLab.o -o MovieLab

###############################  others  ##############################
# Target for clean
clean:
	rm -f *o *.yuv MovieLab  
