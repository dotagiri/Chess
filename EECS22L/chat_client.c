#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>

/*to get a list of the all the people on the server you just type LIST and hit enter
 *
 * to send a message you need to type SEND then the client number then the message you want to send
 *
 * for example:
 *
 * This is what you would type
 *
 * LIST
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


void * doRecieving(void * sockID){

	int clientSocket = *((int *) sockID);

	while(1){

		char data[1024];
		int read = recv(clientSocket,data,1024,0);
		data[read] = '\0';
		printf("%s\n",data);

	}

}

int main(){

	int clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	struct sockaddr_in serverAddr;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8080);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(connect(clientSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == -1) return 0;

	printf("Connection established ............\n");

	pthread_t thread;
	pthread_create(&thread, NULL, doRecieving, (void *) &clientSocket );

	while(1){

		char input[1024];
		scanf("%s",input);

		if(strcmp(input,"LIST") == 0){

			send(clientSocket,input,1024,0);

		}
		if(strcmp(input,"SEND") == 0){

			send(clientSocket,input,1024,0);
			
			scanf("%s",input);
			send(clientSocket,input,1024,0);
			
			scanf("%[^\n]s",input);
			send(clientSocket,input,1024,0);

		}

	}


}
