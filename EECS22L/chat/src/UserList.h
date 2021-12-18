// UserList.h

#ifndef USERLIST_H
#define USERLIST_H

// Structures
typedef struct UserList UserList;
typedef struct User User;
typedef struct Node Node;


struct UserList
{
	Node* head;
	unsigned int length;
};


struct Node
{
	User* user;
	User* friendsList[20];
	Node* next;
};


struct User
{
	char key[20];
	char value[20];
};


// Function Declarations
User* CreateUser(const char key[20], const char value[20]);

void DeleteUser(User* user);

Node* CreateNode(User* user);

void DeleteNode(Node* node);

UserList* CreateUserList(void);

void DeleteUserList(UserList* userList);

unsigned int addUser(UserList* userList, const char key[20], const char value[20]);

unsigned int contains(UserList* userList, const char key[20]);

unsigned int removeUser(UserList* userList, const char key[20]);

unsigned int addFriend(UserList* userList, const char username[20], const char friendName[20]);

void addToFriendsList(User* friendsList[20], User* friend);

unsigned int hasFriend(User* friendsList[20], const char friendName[20]);

unsigned int removeFriend(UserList* userList, const char username[20], const char friendName[20]);

void removeFromFriendsList(User* friendsList[20], const char friendName[20]);

unsigned int friendsListFull(User* friendsList[20]);

unsigned int friendsListSize(User* friendsList[20]);

char* value(UserList* userList, const char key[20]);

unsigned int length(UserList* userList);


#endif // USERLIST_H
