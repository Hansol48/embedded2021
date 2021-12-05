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

int fd = 0;
int buttonPath;
int msgID;
int buttonThFunc;

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

int buttonInit(void)
{
	if (probeButtonPath(buttonPath) == 0)
		return 0;
	fd = open (buttonPath, O_RDONLY);
	msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
	pthread_creat(buttonThFunc, NULL);
	return 1;
}
