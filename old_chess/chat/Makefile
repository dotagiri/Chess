############################################################
# Makefile for Team 13 Project 2
############################################################

GTKINC = `pkg-config --cflags gtk+-2.0`
GTKLIBS = `pkg-config --libs gtk+-2.0`

EXEC = $(addprefix bin/, chat_server noGUIClient GUIClient)
CC = gcc
DEBUG = -DDEBUG

CFLAGS = -ansi -std=c99 -Wall $(DEBUG) $(GTKINC) -c
LFLAGS = -ansi -std=c99 -Wall $(DEBUG) $(GTKLIBS)

COBJECTS = $(addprefix bin/, chat_client.o)
SOBJECTS = $(addprefix bin/, chat_gtk.o chat_server.o UserList.o)
#Default target
all: $(EXEC)

# Objects Files
# ===========================================

# target to generate UserList.o
bin/UserList.o: src/UserList.h src/UserList.c
	$(CC) $(CFLAGS) src/UserList.c -o bin/UserList.o

bin/data.o: src/data.h src/UserList.h src/data.c
	$(CC) $(CFLAGS) src/data.c -o bin/data.o
	
# target to generate chat_client.o
bin/chat_client_final.o: src/chat_client_final.c src/Chat.h
	$(CC) $(CFLAGS) src/chat_client_final.c -o bin/chat_client_final.o -pthread

# target to generate chat_server.o
bin/chat_server_final.o: src/chat_server_final.c src/Chat.h
	$(CC) $(CFLAGS) src/chat_server_final.c -o bin/chat_server_final.o -pthread

#target to generate chat_gtk.o
bin/chat_gtk.o: src/chat_gtk.c src/chat_gtk.h src/UserList.h
	$(CC) src/chat_gtk.c $(CFLAGS) -o bin/chat_gtk.o -pthread

# Executables
# ===========================================

#bin/data: bin/data.o bin/UserList.o
#	$(CC)  $^ $(LFLAGS) -o $@

bin/chat_server: bin/chat_server_final.o
	$(CC)  $^ $(LFLAGS) -o $@

bin/noGUIClient: bin/chat_client_final.o
	$(CC) $^ $(LFLAGS) -o bin/noGUIClient

bin/GUIClient: bin/chat_gtk.o bin/UserList.o
	$(CC) $^ $(LFLAGS) -o bin/GUIClient

############################### others #################################
#Target for Tar
userTar:
	gtar cvzf Chat_Beta.tar.gz bin doc/Chat_UserManual.pdf README.md INSTALL.md COPYRIGHT

devTar:
	gtar cvzf Chat_Beta_src.tar.gz bin doc src README.md Makefile INSTALL.md COPYRIGHT

#Target for clean
clean:
	rm -f bin/*.o $(EXEC)
