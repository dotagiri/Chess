/* client2.c: simple interactive TCP/IP client program
 * based on: http://www.linuxhowtos.org/data/6/client.c
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
    int SocketFD,	/* socket file descriptor */
	PortNo;		/* port number */
    struct sockaddr_in
	ServerAddress;	/* server address we connect with */
    struct hostent
	*Server;	/* server host */
    char SendBuf[256];	/* message buffer for sending a message */
    char RecvBuf[256];	/* message buffer for receiving a response */

    printf("%s: Starting...\n", argv[0]);
    if (argc < 3)
    {   fprintf(stderr, "Usage: %s hostname port\n", argv[0]);
	exit(10);
    }
#ifdef DEBUG
    printf("%s: Looking up host %s on the network...\n", argv[0], argv[1]);
#endif
    Server = gethostbyname(argv[1]);	//gets the server to connect to 
    if (Server == NULL)
    {   fprintf(stderr, "%s: no such host named '%s'\n", argv[0], argv[1]);
        exit(10);
    }
    PortNo = atoi(argv[2]);	//converts the command line arg to the portno
#ifdef DEBUG
    printf("%s: Using port %d...\n", argv[0], PortNo);
#endif
    if (PortNo <= 2000)	//error handing
    {   fprintf(stderr, "%s: invalid port number %d, should be greater 2000\n",
		argv[0], PortNo);
        exit(10);
    }
#ifdef DEBUG
    printf("%s: Creating a socket...\n", argv[0]);
#endif
    SocketFD = socket(AF_INET, SOCK_STREAM, 0);	//creates a socket descriptor
    if (SocketFD < 0)				//error checking for socket
    {   FatalError(argv[0], "socket creation failed");
    }
#ifdef DEBUG
    printf("%s: Preparing the server address...\n", argv[0]);
#endif
    memset(&ServerAddress, 0, sizeof(ServerAddress));	//sets everything in the serveraddress struct to NULL or zero 
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(PortNo);
    memcpy(&ServerAddress.sin_addr.s_addr,
		Server->h_addr_list[0], Server->h_length);	//sets all the values in the server to prerecorded values
    printf("%s: Connecting to the server...\n", argv[0]);
    if (connect(SocketFD, (struct sockaddr*)&ServerAddress,		//connects the socket to socket to server
		sizeof(ServerAddress)) < 0)
    {   FatalError(argv[0], "connecting to server failed");	//if failes then its fatal and ends program
    }

    do{ printf("%s: enter a message to send to the server,\n"				//while loop to keep getting inputs
		"         or 'bye' to quit this client,\n"
		"         or 'shutdown' to quit both server and client:\n"
		"message: ", argv[0]);
	fgets(SendBuf, sizeof(SendBuf), stdin);
	l = strlen(SendBuf);
	if (SendBuf[l-1] == '\n')
	{   SendBuf[--l] = 0;	//sets the \n to a null
	}
	if (l)	//ifl exists or is not zero basically
	{   printf("%s: Sending message '%s'...\n", argv[0], SendBuf);
	    n = write(SocketFD, SendBuf, l);	//writes the message
	    if (n < 0)
	    {   FatalError(argv[0], "writing to socket failed");	//error handling
	    }
#ifdef DEBUG
	    printf("%s: Waiting for response...\n", argv[0]);
#endif
	    n = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);	//read the value from teh recieve buffer
	    if (n < 0) 
	    {   FatalError(argv[0], "reading from socket failed");
	    }
	    RecvBuf[n] = 0;	//sets it to zero
	    printf("%s: Received response: %s\n", argv[0], RecvBuf);	//response recieved from the server
	}
    } while(  (0 != strcmp("server bye", RecvBuf))		//checks if the you write bye or shut down to quit the program
	    &&(0 != strcmp("server shutdown", RecvBuf)));
    printf("%s: Exiting...\n", argv[0]);
    close(SocketFD);	//closes the client socket
    return 0;
}

/* EOF client2.c */

