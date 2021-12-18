/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)	//error messages in case anything goes wrong
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;	//creates portnumber, socked discriptor and newsocket
     socklen_t clilen;			//size of the address
     char buffer[256];			//a buffer created for input and output
     struct sockaddr_in serv_addr, cli_addr;	//2 structs for server and client made
     int n;				//to check if the socket functions are working
     if (argc < 2) {		//error to see if input is correct
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);	//creates a socket file descriptor
     if (sockfd < 0)		//error handling to see if socket was created 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));//sets struct serv_address to NULL
     portno = atoi(argv[1]);	//gets the port number from command line args
     serv_addr.sin_family = AF_INET;	//sets sin_family to the constant
     serv_addr.sin_addr.s_addr = INADDR_ANY;	//INADDR_ANY allows packets from everywhere
     serv_addr.sin_port = htons(portno);	//coverts from host byte to network byte
     if (bind(sockfd, (struct sockaddr *) &serv_addr,//binds the server to localhost address
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");	//error handling is server doesnt get bound
     listen(sockfd,5);	//waits for the client connect to this socket, the 5 means how many
			//people can send an message or data in 
     clilen = sizeof(cli_addr);	//holds length of the address
     newsockfd = accept(sockfd, 	//takes in the first socke request available
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0)	//error handling if the acceptance of a socket fails 
          error("ERROR on accept");
     bzero(buffer,256);	//sets all the vaflues in the buffer to a NULL network byte
     n = read(newsockfd,buffer,255);	//reads from a socket descriptor
     if (n < 0) error("ERROR reading from socket"); //error handling
     printf("Here is the message: %s\n",buffer);	//prints out a precursor to message
     n = write(newsockfd,"I got your message",18);	//prints out the message written by 
							//the client
     if (n < 0) error("ERROR writing to socket");	//error handling
     close(newsockfd);		//closes both the sockets
     close(sockfd);
     return 0;			//ends the function 
}
