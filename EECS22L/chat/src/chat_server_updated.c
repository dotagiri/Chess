#include "Chat.h" 

int clientCount = 0;	//number of active clients doesnt reduce thouhg when a client leaves, possible bug

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;	//initializes the use of multiple threads for this program
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;		//thread conditional variable

struct client	//structure for the client to hold all the data necessary to send to a different client
{
	int index;
	char name[20];
	int sockID;
	struct sockaddr_in clientAddr;
	int len;

};

struct client Client[1024];	//details about the clients, the struct is shown above and holds all the details about a client
pthread_t thread[1024];	//number of threads allowed, or in this case number of users allowed to be on the server at once since each thread opens a new user

void * ExchangeData(void * ClientDetail)
{

	struct client* clientDetail = (struct client*) ClientDetail;	//takes teh void pointed of the clients details and puts it in the struct
	int index = clientDetail -> index;	//makes index easier access for later
	int client_Socket = clientDetail -> sockID;	//makes teh client socket id easier access for later
	char name[30];

	strcpy(name, clientDetail -> name);	//name of client in the name array

	printf("Client %d connected.\n",index + 1);	//states that the client has been created

	while(1)
	{

		char data[1024];	//data array to send messages
		int read = recv(client_Socket,data,1024,0);	//reads data from a socket
		data[read] = '\0';	//makes the last value after the items read to a null value so that it will signify the end of the string

		char output[1024];	//output array

		if(strcmp(data,"USERS") == 0)	//if users is typed in, it returns the users that are online
		{

			int l = 0;

			for(int i = 0 ; i < clientCount ; i ++)
			{

				if(i != index)
					l += snprintf(output + l,1024,"Client %d %s is at socket %d.\n",i + 1, Client[i].name, Client[i].sockID);
					//l is the number of values written in so that the output buffer will not write over itself

			}

			send(client_Socket,output,1024,0);//sends the data to the client
			continue;

		}
		if(strcmp(data,"SEND") == 0)	//if the user wants to send data to another user
		{

			read = recv(client_Socket,data,1024,0);	//gets the data from one of the clients
			data[read] = '\0';	//makes the last value of that data array a blank space so the program know when the string ends
						//this will be the number portion
						
			int id = atoi(data) - 1;	//converts the id to an integer

			read = recv(client_Socket,data,1024,0); //takes the actual string written in and puts it in the data
	//		data[read] = '\0';	//makes the string come to an end after the string actually ends
			
			strcat(data, name);

			printf("The data is %s", data);
	//		data[read + strlen(name)] = '\0';		
						//read returns teh number of bytes recieve, and since it is in char, that works out perfectly meaning that the last value's index
						//is just before the value of read
	//		send(Client[id].sockID, name ,30,0);
	//
			send(Client[id].sockID,data,1024,0); //sends the data to the client that the first client wanted to send it to			

		}
	/*	if(strcmp(data,"NAME") == 0)
		{
			read = recv(client_Socket,data,1024,0);
			data[read] = '\0';

			printf("The name is %s\n", data);


			for(int j = 0; j < read; j++)
			{
				Client[index].name[j] = data[j];
				printf("Name set to %s\n" , Client[index].name);

			}

			printf("Name set to %s\n" , Client[index].name);
					
		}	*/

	}

	return NULL;

}

int main()
{

	int serverSocket = socket(PF_INET, SOCK_STREAM, 0);

	struct sockaddr_in serverAddr;

	serverAddr.sin_family = AF_INET;	//sets all the values to constants
	serverAddr.sin_port = htons(3333);
	serverAddr.sin_addr.s_addr = htons(INADDR_ANY);


	if(bind(serverSocket,(struct sockaddr *) &serverAddr , sizeof(serverAddr)) == -1) 
	{
		printf("Binding failed\n");
		return 0;

	}

	if(listen(serverSocket,1024) == -1)	//takes in 1024 users to listen to 
	{
		printf("Failed to listen\n");
		return 0;

	} 

	printf("Server started listenting on port 3333 ...........\n");	//prints this statement if nothing else has failed

	while(1)	//need to set the name before the exchange of data starts. you cant access memory and change it if there are threads open that are also trying to access that data
	{	//forever loop to open up threads for every new user and to accept all the new users that decide to open a client

		
		if (clientCount == 1024)	//this is the max number of clients and threads openable so if the client number ever reaches this limit, terminate the program
		{		
			printf("This is the max number of clients. None others will be accepted\n");
			continue;
		}
		else
		{	
			Client[clientCount].sockID = accept(serverSocket, (struct sockaddr*) &Client[clientCount].clientAddr, &Client[clientCount].len);//accepts in any new user
			Client[clientCount].index = clientCount;
		
			if(Client[clientCount].sockID != 0)
			{
				
				while(1)
				{
					char data[1024];	//data array to send messages
					int read = recv(Client[clientCount].sockID, data,1024,0);	//reads data from a socket
					data[read] = '\0';	//makes the last value after the items read to a null value so that it will signify the end of the string
				
					printf("The data is: %s\n", data);	
					if(read != 0 && read != -1)
					{
						strcpy(Client[clientCount].name , data);
						break;
					}
				}

				printf("The name saved is: %s\n", Client[clientCount].name);
			}
	
			pthread_create(&thread[clientCount], NULL, ExchangeData, (void *) &Client[clientCount]);	//creates a thread for each of the users

			clientCount ++; //increments the number of users that are active
			
			printf("The number of clients is %d\n", clientCount); //prints out the number of clients that are online in this server
		} 
	}

	for(int i = 0 ; i < clientCount ; i ++)
	{
		pthread_join(thread[i],NULL);	//deletes the threads based on teh number of threads running for the amount of clients
	}
}








