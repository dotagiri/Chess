# Makefile: GUI example clock server with corresponding client
# Rainer Doemer, 2/22/17 (based on simple ClockServer example)

# compiler flags for GTK usage
GTKINC	= `pkg-config --cflags gtk+-2.0`
GTKLIBS	= `pkg-config --libs gtk+-2.0`

# general compiler flags
#DEBUG	= -g -DDEBUG
DEBUG	= -O2
CFLAGS	= -Wall -ansi $(DEBUG) $(GTKINC) -c
LFLAGS	= -Wall -ansi $(DEBUG) $(GTKLIBS)

# targets
all: GTK_ClockClient GTK_ClockServer

clean:
	rm -f *.o
	rm -f GTK_ClockClient GTK_ClockServer

test:
	@echo "To run the examples, first start the server in one terminal,"
	@echo "then start one (or multiple) client(s) in another."
	@echo
	@echo "For example:"
	@echo "crystalcove% ./GTK_ClockServer 10000"
	@echo "crystalcove% ./GTK_ClockClient crystalcove 10000"

GTK_ClockClient.o: GTK_ClockClient.c
	gcc GTK_ClockClient.c $(CFLAGS) -o GTK_ClockClient.o

GTK_ClockClient: GTK_ClockClient.o
	gcc GTK_ClockClient.o $(LFLAGS) -o GTK_ClockClient

GTK_ClockServer.o: GTK_ClockServer.c
	gcc GTK_ClockServer.c $(CFLAGS) -o GTK_ClockServer.o

GTK_ClockServer: GTK_ClockServer.o
	gcc GTK_ClockServer.o $(LFLAGS) -o GTK_ClockServer

# EOF
