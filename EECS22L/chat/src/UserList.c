// UserList.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "UserList.h"


User* CreateUser(const char key[20], const char value[20])
{
	User* user = malloc(sizeof(User));
	assert(user != NULL);
	
	strcpy(user->key, key);
	strcpy(user->value, value);

	return user;
}


void DeleteUser(User* user)
{
	free(user);
}


Node* CreateNode(User* user)
{
	Node* node = malloc(sizeof(Node));
	assert(node != NULL);

	node->user = user;

	for (unsigned int i = 0; i < 20; ++i){
		node->friendsList[i] = NULL;
	}

	node->next = NULL;

	return node;	
}


void DeleteNode(Node* node)
{
	DeleteUser(node->user);
	free(node);
}


UserList* CreateUserList(void)
{
	UserList* userList = malloc(sizeof(UserList));
	assert(userList != NULL);

	userList->head = NULL;
	userList->length = 0;

	return userList;
}


void DeleteUserList(UserList* userList)
{
	Node* current = userList->head;
	Node* next;

	while (current){
		next = current->next;
		DeleteNode(current);
		current = next;
	}

	free(userList);
}


unsigned int addUser(UserList* userList, const char key[20], const char value[20])
{
	if (contains(userList, key) == 0){
		User* user = CreateUser(key, value);

		if (userList->head == NULL){
			userList->head = CreateNode(user);
			++userList->length;
		}

		else {
			Node* current = userList->head;

			while (current->next != NULL){
				current = current->next;
			}

			current->next = CreateNode(user);
			++userList->length;
		}

		return 1;
	}

	return 0;
}


unsigned int contains(UserList* userList, const char key[20])
{
	Node* current = userList->head;

	while (current != NULL){
		if (strcmp(current->user->key, key) == 0){
			return 1;
		}
		
		current = current->next;
	}

	return 0;
}


unsigned int removeUser(UserList* userList, const char key[20])
{
	if (contains(userList, key) == 1){
		Node* current = userList->head;

		if (strcmp(current->user->key, key) == 0){
			userList->head = userList->head->next;
			DeleteNode(current);
			--userList->length;

			return 1;
		}

		else {
			Node* nextNode = current->next;

			while (strcmp(nextNode->user->key, key) != 0){
				current = nextNode;
				nextNode = nextNode->next;
			}

			current->next = nextNode->next;
			DeleteNode(nextNode);
			--userList->length;

			return 1;
		}
	}

	return 0;
}


unsigned int addFriend(UserList* userList, const char username[20], const char friendName[20])
{
	if (contains(userList, username) == 1 && contains(userList, friendName) == 1){
		Node* userNode = userList->head;
		Node* friendNode = userList->head;

		while (strcmp(userNode->user->key, username) != 0){
			userNode = userNode->next;
		}

		if (friendsListFull(userNode->friendsList) == 1){
			return 2;
		}

		if (hasFriend(userNode->friendsList, friendName) == 0){
			while(strcmp(friendNode->user->key, friendName) != 0){
				friendNode = friendNode->next;
			}

			addToFriendsList(userNode->friendsList, friendNode->user);
			return 1;
		}

		return 0;
	}

	return 0;
}


void addToFriendsList(User* friendsList[20], User* friend)
{
	for (unsigned int i = 0; i < 20; ++i){
		if (friendsList[i] == NULL){
			friendsList[i] = friend;
			break; 
		}
	}
}


unsigned int hasFriend(User* friendsList[20], const char friendName[20])
{
	for (unsigned int i = 0; i < 20; ++i){
		if (friendsList[i] != NULL && strcmp(friendsList[i]->key, friendName) == 0){
			return 1;	
		}
	}

	return 0;
}


unsigned int removeFriend(UserList* userList, const char username[20], const char friendName[20])
{
	if (contains(userList, username) == 1 && contains(userList, friendName) == 1){
		Node* userNode = userList->head;

		while (strcmp(userNode->user->key, username) != 0){
			userNode = userNode->next;
		}

		if (hasFriend(userNode->friendsList, friendName) == 1){
			removeFromFriendsList(userNode->friendsList, friendName);
			return 1;
		}

		return 0;
	}

	return 0;
}


void removeFromFriendsList(User* friendsList[20], const char friendName[20])
{
	for (unsigned int i = 0; i < 20; ++i){
		if (friendsList[i] != NULL && strcmp(friendsList[i]->key, friendName) == 0){
			friendsList[i] = NULL;
			break;
		}
	}
}


unsigned int friendsListFull(User* friendsList[20])
{
	for (unsigned int i = 0; i < 20; ++i){
		if (friendsList[i] == NULL){
			return 0;
		}
	}

	return 1;
}


unsigned int friendsListSize(User* friendsList[20])
{
	unsigned int size = 0;

	for (unsigned int i = 0; i < 20; ++i){
		if (friendsList[i] != NULL){
			++size;
		}
	}

	return size;
}


char* value(UserList* userList, const char key[20])
{
	if (contains(userList, key) == 1){
		Node* current = userList->head;

		while (strcmp(current->user->key, key) != 0){
			current = current->next;
		}

		return current->user->value;
	}

	return NULL;
}


unsigned int length(UserList* userList)
{
	return userList->length;
}
