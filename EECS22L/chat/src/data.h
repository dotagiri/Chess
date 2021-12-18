// data.h

#ifndef DATA_H
#define DATA_H

#include "UserList.h"


void writeUserListToDatabase(UserList* userList);

void writeFriendsList(FILE* fp, User* friendsList[20], const unsigned int size);

UserList* readDatabase();

unsigned int lineCount(char* filename);

#endif // DATA_H
