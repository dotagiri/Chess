#include "Chat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gtk/gtk.h>
#include "UserList.h"
#include "chat_gtk.h"

/*to get a list of the all the people on the server you just type USERS  and hit enter
 *
 * to send a message you need to type SEND then the client number then the message you want to send
 *
 * for example:
 *
 * This is what you would type
 *
 *USERS 
 * (a list of the poeple on the server along with thier socket number will appear)
 *
 * SEND 2 Hello
 *
 * The 2 is the client number, NOT THE  SOCKET number.
 * then you can just cfhekc the other client and see if the message has sent
 * and then you can send messages back and forth to yourself
 *
 * SIDE NOTE:
 * 
 * do not open to many of these on your own computer because it might cause issues.
 * since it is opening a thread for each new user, its makes the computer hella slow if you have like 5 clients open
 *
 *TO MAKE THE EXECUTABLES

	just type:
	
	gcc chat_client -o client -std=c99 -pthread

	gcc chat_server -o server -std=c99 -pthread
 *
 *
 */

void * getData(void * sockID)
{

	int client_Socket = *((int *) sockID);	//gets the client socket value from the socket id integer pointer

	while(1)
	{

		char data[1024];	//gets a data stream of 1024 characters
		int read = recv(client_Socket,data,1024,0);	//takes the incoming data from this socket
		data[read] = '\0';	//puts a the whitespace at the end of teh data stream, the read is the returned value of  recv which is the number of characters read in 
		printf("%s\n",data); //prints the data stream that was made

	}

}

int main()
{

	int client_Socket = socket(PF_INET, SOCK_STREAM, 0);	//create a socket for the client
	
	struct hostent *server;
	struct sockaddr_in serverAddr;		//structs needed for the server
//startr of copied
	server = gethostbyname("zuma.eecs.uci.edu");
    	if (server == NULL) 
	{
        	fprintf(stderr,"ERROR, no such host\n");
        	return 0;
    	}
    	bzero((char *) &serverAddr, sizeof(serverAddr));

    
	bcopy((char *)server->h_addr_list[0],(char *)&serverAddr.sin_addr.s_addr,server->h_length);	//makes sure that the server si always the zuma.eecs thing at the certain portno

//end of copied




	serverAddr.sin_family = AF_INET;	//constant that you put in for everything
	serverAddr.sin_port = htons(3333);	//random port number hard coded in 

	if(connect(client_Socket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == -1)	//connect will return negative one if the code does not work
	{
		printf("Connection failed\n");	
		printf("There maybe too many users online currently, try again at another time \n");
		return 0;
	}

	printf("Connection established ............\n");
	printf("INTRUCTIONS\n\n");
	printf("in order to get list of users online, type USERS\n");
	printf("In order to send a message type SEND (recieving client's number) and then the message you want to send all on the same line\n\n"); 
	printf("For example, if you are sending and there are 2 other clients that are numbered client 1 and 2 respectively, you have to type:\n");
	printf("SEND 2 Hello\n");
	printf("This will send the message to the second client\n");
	

	pthread_t thread;	//makes a thread variable
	pthread_create(&thread, NULL, getData, (void *) &client_Socket ); //creates a thread to get the data 

	while(1)
	{

		char input[1024];	//input character, has block scope so it dies at each iteration of the while loop
		scanf("%s",input);	//takes in the input from the user

		//only sends data if it is USERS or SEND, making sure that anything that occures with the server will be because of the correct key words

		if(strcmp(input,"USERS") == 0)	//strcmp returns zero if true
		{	

			send(client_Socket,input,1024,0);	//gets a list of users from the server

		}
		if(strcmp(input,"SEND") == 0)	//in order to send a message
		{

			send(client_Socket,input,1024,0);
			
			scanf("%s",input);
			send(client_Socket,input,1024,0);
			
			scanf("%[^\n]s",input);	//reads until the newline
			send(client_Socket,input,1024,0);

		}

	}


}
