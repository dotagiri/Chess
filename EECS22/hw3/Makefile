#Makefile: PhotoLab

all: PhotoLab PhotoLabTest

# generating object files

PhotoLab.o: PhotoLab.c Constants.h DIPs.h Advanced.h FileIO.h
	gcc -c -Wall -ansi -std=c99 PhotoLab.c -o PhotoLab.o

PhotoLabTest.o: PhotoLab.c Constants.h DIPs.h Advanced.h FileIO.h
	gcc -c -DDEBUG -Wall -ansi -std=c99 PhotoLab.c -o PhotoLabTest.o

FileIO.o: FileIO.c FileIO.h Constants.h
	gcc -c -Wall -ansi -std=c99 FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Constants.h
	gcc -c -Wall -ansi -std=c99 DIPs.c -o DIPs.o

Advanced.o: Advanced.c Advanced.h Constants.h
	gcc -c -Wall -ansi -std=c99 Advanced.c -o Advanced.o

# generating library

libfilter.a: DIPs.o Advanced.o
	ar rc libfilter.a DIPs.o Advanced.o
	ranlib libfilter.a

# generating executable programs

PhotoLab: PhotoLab.o FileIO.o libfilter.a
	gcc -lm -Wall -ansi -std=c99 PhotoLab.o FileIO.o -L. -lfilter -o PhotoLab

PhotoLabTest: PhotoLabTest.o FileIO.o libfilter.a
	gcc -lm -Wall -ansi -std=c99 PhotoLabTest.o FileIO.o -L. -lfilter -o PhotoLabTest

clean:
	rm -f *.o
	rm -f PhotoLab
	rm -f PhotoLabTest

#EOF
