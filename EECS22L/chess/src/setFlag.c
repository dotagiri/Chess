// setFlag.c

#include "setFlag.h"

unsigned int movedWKing(const unsigned int operation){
    static unsigned int flag = 0;
    if(operation==1){
	flag=1;
    }
    return flag;
}

unsigned int movedWLRook(const unsigned int operation){
    static unsigned int flag = 0;
    if(operation==1){
        flag=1;
    }
    return flag;
}

unsigned int movedWRRook(const unsigned int operation){
    static unsigned int flag = 0;
    if(operation==1){
        flag=1;
    }
    return flag;
}

unsigned int movedBKing(const unsigned int operation){
    static unsigned int flag = 0;
    if(operation==1){
        flag=1;
    }
    return flag;
}

unsigned int movedBLRook(const unsigned int operation){
    static unsigned int flag = 0;
    if(operation==1){
        flag=1;
    }
    return flag;
}

unsigned int movedBRRook(const unsigned int operation){
    static unsigned int flag = 0;
    if(operation==1){
        flag=1;
    }
    return flag;
}
