// data.c

#include <string.h>
#include <stdio.h>
#include "data.h"


void writeUserListToDatabase(UserList* userList)
{
	FILE* fp = fopen("database.txt", "w+");
	Node* currentNode = userList->head;

	while (currentNode != NULL){
		fprintf(fp, "(%s:%s)->", currentNode->user->key, currentNode->user->value);
		writeFriendsList(fp, currentNode->friendsList, friendsListSize(currentNode->friendsList));
		currentNode = currentNode->next;
	}

	fclose(fp);
}


void writeFriendsList(FILE* fp, User* friendsList[20], const unsigned int size)
{
	char allFriends[size][20];
	unsigned int index = 0;

	if (size == 0){
		fprintf(fp, "%c", '\n');
	}

	else {
		for (unsigned int i = 0; i < 20; ++i){
			if (friendsList[i] != NULL){
				strcpy(allFriends[index++], friendsList[i]->key);
			}
		}

		for (unsigned int i = 0; i < size; ++i){
			fprintf(fp, "%s%c", allFriends[i], i == size - 1 ? '\n' : ',');
		}
	}
}


UserList* readDatabase()
{
	UserList* userList = CreateUserList();

	char filename[13] = "database.txt";
	unsigned int numOfLines = lineCount(filename);
	char tokenArr[numOfLines][22][20];

	for (unsigned int i = 0; i < numOfLines; ++i){
		for (unsigned int j = 0; j < 22; ++j){
			strcpy(tokenArr[i][j], "");
		}
	}

	FILE* fp = fopen(filename, "r");

	for (unsigned int i = 0; i < numOfLines; ++i){
		unsigned int index = 0;

		char str[450];
		fgets(str, 450, fp);
				
		char* token = strtok(str, "(:");

		while (token != NULL){
			strcpy(tokenArr[i][index++], token);
			token = strtok(NULL, ")->,\n");
		}
	}

	for (unsigned int i = 0; i < numOfLines; ++i){
		addUser(userList, tokenArr[i][0], tokenArr[i][1]);	
	}

	for (unsigned int i = 0; i < numOfLines; ++i){
		for (unsigned int j = 2; j < 22; ++j){
			if (strcmp(tokenArr[i][j], "") != 0){
				addFriend(userList, tokenArr[i][0], tokenArr[i][j]);
			}
		}
	}

	return userList;
}


unsigned int lineCount(char* filename)
{
	FILE* fp = fopen(filename, "r");

	unsigned int count = 0;
	char c;

	for (c = getc(fp); c != EOF; c = getc(fp)){
		if (c == '\n'){
			++count;
		}
	}

	fclose(fp);

	return count;
}


int main(void)
{
/*	UserList* userList = CreateUserList();
	
	addUser(userList, "Raymond Yu", "EECS22L");
	addUser(userList, "user1", "324242");
	addUser(userList, "QV Dang", "EECS22L");
	addUser(userList, "Vivek Hatte", "EECS22L");
	addUser(userList, "Justin Han", "EECS22L");
	addUser(userList, "Daisuke Otagiri", "EECS22L");
	addUser(userList, "Hao Ming Chiang", "EECS22L");

	Node* current = userList->head;

	removeUser(userList, "user1");

	while (current != NULL){
		printf("%s ", current->user->key);
		printf("%s\n", value(userList, current->user->key));
		current = current->next;
	}

	printf("%d\n", length(userList));

	printf("%d\n", addFriend(userList, "Raymond Yu", "QV Dang"));
	printf("%d\n", addFriend(userList, "Raymond Yu", "Vivek Hatte"));
	printf("%d\n", addFriend(userList, "Raymond Yu", "Justin Han"));
	printf("%d\n", addFriend(userList, "Raymond Yu", "Daisuke Otagiri"));
	printf("%d\n", addFriend(userList, "Raymond Yu", "Hao Ming Chiang"));

	printf("%d\n", removeFriend(userList, "Raymond Yu", "QV Dang"));
		
	writeUserListToDatabase(userList);
	DeleteUserList(userList);
*/

	UserList* userList2 = readDatabase();

	Node* current = userList2->head;

	while (current != NULL){
		printf("%s ", current->user->key);
		printf("%s\n", value(userList2, current->user->key));
		
		for (unsigned int i = 0; i < 20; ++i){
			if (current->friendsList[i] != NULL){
				printf("%s\n", current->friendsList[i]->key);
			}
		}

		current = current->next;
	}

	printf("%d\n", length(userList2));

	DeleteUserList(userList2);

	return 0;
}
