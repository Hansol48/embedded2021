#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/msg.h>
#include "myMessage.h"

int main (void)
{
    char command[200];

    structMyMsg messageRxData;
    int msgQueue = msgget((key_t)MY_MESSAGE_ID, IPC_CREAT|0666); // 없으면 만들고, 만들게 된다면 누구나 읽고 쓰기가 가능하게 만든다.

    if (msgQueue == -1) // 실패했을경우
    {
        printf ("Cannot get msgQueueID, Return!\r\n");
        return -1;
    }


    while (1)
    {
        int returnValue = 0;
        returnValue = msgrcv(msgQueue, &messageRxData, sizeof(messageRxData.piggyBack), 0, IPC_NOWAIT);
        if (returnValue == -1) break; //There is no message at all
        printf ("%s\r\n", messageRxData.piggyBack);
    }
    

    while (1)
    {	
        int returnValue = 0;
        returnValue = msgrcv(msgQueue, &messageRxData, sizeof(messageRxData.piggyBack), 0, 0); //Wait here if no mesaage
        printf ("%s\r\n", messageRxData.piggyBack);
    }
}