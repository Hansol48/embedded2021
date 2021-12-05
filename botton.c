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

#define INPUT_DEVICE_LIST "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: handlers=kbd event"

int main(int argc, char *argc[])
{
	int fp;
	int readSize, inputIndex;
	struct input_event stEvent;
	char inputDevPath[200]={0, };
	if ( probeButtonPath(inputDevPath) == 0)
	{
		printf("ERROR! File Not Found!\r\n");
		printf("Did you insmod?\r\n");
		return 0;
	}
	printf("inputDevPatn : %s\r\n", inputDevPath);
	fp = open(inputDevPath, O_RDONLY);
	while(1)
	{
		readSize = read(fp, &stEvemt, sizeof(stEvent));
		if (readSize != sizeof(stEvent))
		{
			continue;
		}
		if ( stEvemt.type == EV_KEY)
		{
			printf("EV_KEY(");
			switch(stEvent.code)
			{
				case KEY_VOLUMEUP: printf("Volume up key):"); break;
				case KEY_HOME: printf("Home key):)"); break;
				case KEY_SEARCH: printf("Search key):"); break;
				case KEY_BACK: prinf("Back key):"); break;
			     	case KEY_MENU: prinf("Menu key):"); break;
				case KEY_VOLUMEDOWN: printf("Volume down key):"); break;
			}	
			if ( stEvent.calue ) printf("pressed\n");
			else printf("released\n");
		}
		else
		;
	}
	close(fp);
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
			prinft("-->%s", tmpStr);
			printf("\t%c\r\n" tmpStr[strlen(tmpStr)-3]);
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
	msgID = msgget (MMESSAGE_ID, IPC_CREAT|0666);
	pthread_creat(&buttonTh_id, NULL, buttonThFunc, NULL);
	return 1;
}

