#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)	//to read out an error message when an error comes
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;	//sockfd is the socker descriptor
				//portno is the por number
				//n is for checking legality with return values of socket programming
    struct sockaddr_in serv_addr; //a specific struct that has the addrress and port number
    struct hostent *server;	//holds information about the host server

    char buffer[256];	//making a buffer so the input stream works properly
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);	//take in the port number
    sockfd = socket(AF_INET, SOCK_STREAM, 0);	//creates a socketfd with the constants
						//socket(constant, constant, constant)
						//those values are always the same
    if (sockfd < 0) 	//sockfd returns value less that zero if it doesnt work
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);	//gethostbyname does what it sounds like
					//stores in the host entity structure
    if (server == NULL) {		//checks if the server is actually saved
        fprintf(stderr,"ERROR, no such host\n");	//if not prints error
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));	//used to set all socket struct
							//values to null
    serv_addr.sin_family = AF_INET;			//always make sin .family AF_INET
    bcopy((char *)server->h_addr,			//copies network byte strings from o 
         (char *)&serv_addr.sin_addr.s_addr,		//one string to another
         server->h_length);
    serv_addr.sin_port = htons(portno); //converts portno to network byte order
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) //if connect() is less that zero, meaning connection failed, then return a negative number
        error("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,256);	//makes all values of the buffer null
    fgets(buffer,255,stdin); //gets a value to but in teh buffer string
    n = write(sockfd,buffer,strlen(buffer));//writes in nbytes the string you want to send
    if (n < 0) 
         error("ERROR writing to socket");	//error handling, returns -1 if fails
    bzero(buffer,256);		//resets the buffer to null
    n = read(sockfd,buffer,255);	//reads the thing you wrote in to the buffer to server output
    if (n < 0) 		//error handling since read returns -1 if failed
         error("ERROR reading from socket");
    printf("%s\n",buffer);	//prints out what you typed
    close(sockfd);		//closes the socket meaning its the end of communation
    return 0;			//returns to end program
}
