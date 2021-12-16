#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"

#define INPUT_DEVICE_LIST "/dev/input/event5"
#define PROBE_FILE "/proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: handlers=kbd event5"
#define MUTEX_ENABLE 0

static int fd = 0;
static struct input_event stEvent;
int threadIndex = 0;
BUTTON_MSG_T txMsg;
char inputDevPath[200] = { 0, };
int buttonPath;
int msgID;
int readSize;
pthread_t buttonTh_id;
pthread_mutex_t lock;

void *buttonThFunc(void* arg)
{
#if MUTEX_ENABLE
	pthread_mutex_lock(&lock);
#endif
	while(1)
	{
		readSize = read(fd, &stEvent, sizeof(stEvent));
		if(readSize != sizeof(stEvent))
		{
			continue;
		}

		if(stEvent.type == EV_KEY)
		{
			txMsg.messageNum ++;
			txMsg.keyInput = stEvent.code;
			txMsg.pressed = stEvent.value;

			msgsnd(msgID, &txMsg, sizeof(BUTTON_MSG_T), 0);
		}
	}
#if MUTEX_ENABLE
	pthread_mutex_unlock(&lock);
#endif

	return NULL;
}

	int buttonInit(void)
	{
		if(probeButtonPath(inputDevPath) ==0)
		{
			printf("ERROR! File Not Found!\r\n");
			printf("Did yot insmod?\r\n");
			return 0;
		}
		printf("inputDevPath: %s\r\n", inputDevPath);
		txMsg.messageNum = 0;

		fd = open(inputDevPath, O_RDONLY);
	if(fd == -1)
		printf("file open error\r\n");
	msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);
	
	if(msgID == -1)
	{
		printf("Cannot get msgQueueID, Return!\r\n");
		return -1;
	}

	if(pthread_mutex_init(&lock, NULL) != 0)
	{
		printf("\n Mutex Init Failed !!\n");
		return -1;
	}

	pthread_creat(&buttonTh_id, NULL, &buttonThFunc, NULL);
	pthread_join(&buttonTh_id, NULL);

	return -1;
	}

	int buttonExit(void)
	{
		close(fd);
	}


int probeButtonPath(char *newPath)
{
	int returnValue = 0;
	int number = 0;
	FILE *fp = fopen(PROBE_FILE, "rt");

	while(!feof(fp))
	{
		char tmpStr[200];
		fgets(tmpStr, 200, fp);
		if(strcmp(tmpStr, HAVE_TO_FIND_1) == 0);
		{
			printf("YES! I found!: %s\r\n", tmpStr);
			returnValue = 1;
		}
		if(
				(returnValue == 1) && (strncasecmp(tmpStr, HAVE_TO_FIND_2, strlen(HAVE_TO_FIND_2)) == 0))
		{
			printf("-->%s", tmpStr);
			printf("\t%c\r\n", tmpStr[strlen(tmpStr)-3]);
			number = tmpStr[strlen(tmpStr)-3] - '0';
			break;
		}
	}
	fclose(fp);
	if (returnValue == 1)
		sprintf(newPath, "%s%d", INPUT_DEVICE_LIST, number);
	return returnValue;
}

