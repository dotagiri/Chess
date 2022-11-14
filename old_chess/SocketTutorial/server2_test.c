/* server2.c: simple interactive TCP/IP server program
 * based on: http://www.linuxhowtos.org/data/6/server.c
 * extended by Rainer Doemer, 2/11/15
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>

/* #define DEBUG */	/* be very verbose */

void FatalError(const char *Program, const char *ErrorMsg)
{
    fputs(Program, stderr);
    fputs(": ", stderr);
    perror(ErrorMsg);
    fputs(Program, stderr);
    fputs(": Exiting!", stderr);
    exit(20);
} /* end of FatalError */

int main(int argc, char *argv[])
{
    int l, n;
    int ServSocketFD,	/* socket file descriptor for service */
	DataSocketFD,	/* socket file descriptor for data */
	PortNo;		/* port number */
    socklen_t ClientLen;
    struct sockaddr_in
	ServerAddress,	/* server address (this host) */
	ClientAddress;	/* client address we connect with */
    char RecvBuf[256];	/* message buffer for receiving a message */
    char SendBuf[256];	/* message buffer for sending a response */
    int Bye = 0,
	Shutdown = 0;

    printf("%s: Starting...\n", argv[0]);
    if (argc < 2)
    {   fprintf(stderr, "Usage: %s port\n", argv[0]);
	exit(10);
    }
    PortNo = atoi(argv[1]);	/* get the port number */
#ifdef DEBUG
    printf("%s: Using port %d...\n", argv[0], PortNo);
#endif
    if (PortNo <= 2000)
    {   fprintf(stderr, "%s: invalid port number %d, should be greater 2000\n",
		argv[0], PortNo);
        exit(10);
    }
#ifdef DEBUG
    printf("%s: Creating a socket to serve clients...\n", argv[0]);
#endif
    ServSocketFD = socket(AF_INET, SOCK_STREAM, 0);	//creates server socket file descriptor
    if (ServSocketFD < 0)
    {   FatalError(argv[0], "service socket creation failed");	//error handling server socket fd returns -1 if error occurs
    }
#ifdef DEBUG
    printf("%s: Preparing the server address...\n", argv[0]);
#endif
    memset(&ServerAddress, 0, sizeof(ServerAddress));	//sets the values in the serveraddress struct to NULL or zero
    ServerAddress.sin_family = AF_INET;			//there 3 next lines are constants that you should put in your server struct
    ServerAddress.sin_port = htons(PortNo);
    ServerAddress.sin_addr.s_addr = INADDR_ANY;		//INARRAY_ANY means that it takes in packets from any source
#ifdef DEBUG
    printf("%s: Assigning the server name to the socket...\n", argv[0]);
#endif
    if (bind(ServSocketFD, (struct sockaddr*)&ServerAddress,	//binds the server socket to the actual server details from the struct
		sizeof(ServerAddress)) < 0)
    {   FatalError(argv[0], "binding the server to a socket failed");	//error is the binding fails
    }
    printf("%s: Listening on port %d...\n", argv[0], PortNo);
    if (listen(ServSocketFD, 5) < 0)	/* max 5 clients in backlog */
    {   FatalError(argv[0], "listening on socket failed");
    }

    do{ Shutdown = 0;	//makes sure the shutdown procedure isnt executed since it is zero
	ClientLen = sizeof(ClientAddress);	//struct of the client
	DataSocketFD = accept(ServSocketFD, (struct sockaddr*)&ClientAddress,	//finds the socket of any client next in que and makes it ready for data transfer accross the two entities
		&ClientLen);
	if (DataSocketFD < 0)	//if the value is -1 it means that the new socket was not created
	{   FatalError(argv[0], "data socket creation (accept) failed");
	}
	printf("%s: Accepted connection from client.\n", argv[0]);
#ifdef DEBUG
	printf("%s: Client address:port = %u:%hu.\n", argv[0],
			ClientAddress.sin_addr.s_addr, ntohs(ClientAddress.sin_port));		//prints the client address and port number
#endifi							//NOTE: if a person connects with the server, anohter user cannot talk until this one is finished relaying its messages
	do{ Bye = 0;	//bye means the client ends and not the server. this loop acts when shutdown isnt initiated
	    n = read(DataSocketFD, RecvBuf, sizeof(RecvBuf)-1);	//reads in the data being written from the client socket
	    if (n < 0) 
	    {   FatalError(argv[0], "reading from data socket failed");		//error handling
	    }
	    RecvBuf[n] = 0;	//sets the buffer back to zero
	    printf("%s: Received message: %s\n", argv[0], RecvBuf);
	    if (0 == strcmp(RecvBuf, "bye"))	//checks if the message is bye, if so it ends this loop which is with this client
	    {   Bye = 1;
#ifdef DEBUG
		printf("%s: Received 'bye' message from client.\n", argv[0]);
#endif
		strncpy(SendBuf, "server bye", sizeof(SendBuf)-1);
		SendBuf[sizeof(SendBuf)-1] = 0;
	    }
	    else if (0 == strcmp(RecvBuf, "shutdown"))	//checks if the shutdown is initiated
	    {   Shutdown = 1;
#ifdef DEBUG
		printf("%s: Received 'shutdown' message from client.\n", argv[0]);
#endif
		strncpy(SendBuf, "server shutdown", sizeof(SendBuf)-1);
		SendBuf[sizeof(SendBuf)-1] = 0;
	    }
	    else
	    {   strncpy(SendBuf, "server echo ", sizeof(SendBuf)-1);	//echos the message that you sent
		SendBuf[sizeof(SendBuf)-1] = 0;
		strncat(SendBuf, RecvBuf, sizeof(SendBuf)-1-strlen(SendBuf));
	    }
	    l = strlen(SendBuf);
	    printf("%s: Sending response: %s.\n", argv[0], SendBuf);
	    n = write(DataSocketFD, SendBuf, l);		//writes the data to the client socket
	    if (n < 0)
	    {   FatalError(argv[0], "writing to data socket failed");
	    }
	} while(!Bye && !Shutdown);	//if bye or shutdown hasnt initiated it continues to run
	printf("%s: Received last message from client, closing data connection.\n", argv[0]);	//means that the current client connection has been terminated
	close(DataSocketFD);	//closes the socket connection with the current client

    } while(!Shutdown);	//if shutdown isnt initialted then it will keep running

    printf("%s: Shutting down.\n", argv[0]);
    close(ServSocketFD);	//closes the server if shutdown 
    return 0;
}

/* EOF server2.c */

