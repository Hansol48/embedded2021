#ifndef _MY_MESSAGE_H_
#define _MY_MESSAGE_H_

#define MY_MESSAGE_ID  1225
typedef struct
{
    long int messageType;
    char piggyBack[200];
} structMyMsg;

#endif