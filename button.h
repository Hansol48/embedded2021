#ifndef _BUTTON_H_
#define _BUTTON_H_

#define MESSAGE_ID 1225
typedef struct
{
	long int messageNum;
	int keyInput;
	int pressed;
} BUTTON_MSG_T;

void *buttonThFunc(void *arg);
int buttonInit(void);
int buttonExit(void);
int probeButtonPath(char *newPath);
#endif
