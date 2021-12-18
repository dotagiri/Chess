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
    {   FatalError(argv[0], "service socket creation failed");
    }
#ifdef DEBUG
    printf("%s: Preparing the server address...\n", argv[0]);
#endif
    memset(&ServerAddress, 0, sizeof(ServerAddress));
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(PortNo);
    ServerAddress.sin_addr.s_addr = INADDR_ANY;
#ifdef DEBUG
    printf("%s: Assigning the server name to the socket...\n", argv[0]);
#endif
    if (bind(ServSocketFD, (struct sockaddr*)&ServerAddress,
		sizeof(ServerAddress)) < 0)
    {   FatalError(argv[0], "binding the server to a socket failed");
    }
    printf("%s: Listening on port %d...\n", argv[0], PortNo);
    if (listen(ServSocketFD, 5) < 0)	/* max 5 clients in backlog */
    {   FatalError(argv[0], "listening on socket failed");
    }

    do{ Shutdown = 0;
	ClientLen = sizeof(ClientAddress);
	DataSocketFD = accept(ServSocketFD, (struct sockaddr*)&ClientAddress,
		&ClientLen);
	if (DataSocketFD < 0)
	{   FatalError(argv[0], "data socket creation (accept) failed");
	}
	printf("%s: Accepted connection from client.\n", argv[0]);
#ifdef DEBUG
	printf("%s: Client address:port = %u:%hu.\n", argv[0],
			ClientAddress.sin_addr.s_addr, ntohs(ClientAddress.sin_port));
#endif
	do{ Bye = 0;
	    n = read(DataSocketFD, RecvBuf, sizeof(RecvBuf)-1);
	    if (n < 0) 
	    {   FatalError(argv[0], "reading from data socket failed");
	    }
	    RecvBuf[n] = 0;
	    printf("%s: Received message: %s\n", argv[0], RecvBuf);
	    if (0 == strcmp(RecvBuf, "bye"))
	    {   Bye = 1;
#ifdef DEBUG
		printf("%s: Received 'bye' message from client.\n", argv[0]);
#endif
		strncpy(SendBuf, "server bye", sizeof(SendBuf)-1);
		SendBuf[sizeof(SendBuf)-1] = 0;
	    }
	    else if (0 == strcmp(RecvBuf, "shutdown"))
	    {   Shutdown = 1;
#ifdef DEBUG
		printf("%s: Received 'shutdown' message from client.\n", argv[0]);
#endif
		strncpy(SendBuf, "server shutdown", sizeof(SendBuf)-1);
		SendBuf[sizeof(SendBuf)-1] = 0;
	    }
	    else
	    {   strncpy(SendBuf, "server echo ", sizeof(SendBuf)-1);
		SendBuf[sizeof(SendBuf)-1] = 0;
		strncat(SendBuf, RecvBuf, sizeof(SendBuf)-1-strlen(SendBuf));
	    }
	    l = strlen(SendBuf);
	    printf("%s: Sending response: %s.\n", argv[0], SendBuf);
	    n = write(DataSocketFD, SendBuf, l);
	    if (n < 0)
	    {   FatalError(argv[0], "writing to data socket failed");
	    }
	} while(!Bye && !Shutdown);
	printf("%s: Received last message from client, closing data connection.\n", argv[0]);
	close(DataSocketFD);

    } while(!Shutdown);

    printf("%s: Shutting down.\n", argv[0]);
    close(ServSocketFD);
    return 0;
}

/* EOF server2.c */

