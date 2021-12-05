#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/msg.h>
#include "myMessage.h"

int main (void)
{   
    char command[200];

    structMyMsg messageTxData;
    int msgQueue = msgget((key_t)MY_MESSAGE_ID, IPC_CREAT|0666); // 없으면 만들고, 만들게 된다면 누구나 읽고 쓰기가 가능하게 만든다.

    if (msgQueue == -1) // 실패했을경우
    {
        printf ("Cannot get msgQueueID, Return!\r\n");
        return -1;
    }

    
    while (1)
    {
        printf("");
	    gets(command);	


        sleep(1); // 1초마다
        snprintf(messageTxData.piggyBack, sizeof(messageTxData.piggyBack)-1, "%s", command); //버퍼 크기보다 1만큼 작을때까지만 printf를 해준다.
        messageTxData.messageType = 1; // 1 is good enough

        printf("\t%s\r\n");
        msgsnd(msgQueue, &messageTxData, sizeof(messageTxData.piggyBack), 0); //piggyBack 사이즈만큼만 보낸다. 그리고 받는쪽에서 우편함이 꽉 차있다면 무한대로 기다린다.
    }
}