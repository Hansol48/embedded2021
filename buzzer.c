#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "buzzer.h"

int fd = 0;
char path[200];

int buzzerInit (void)
{
	fd=open (path, O_WRONLY);
	if (fd = -1)
	{
		printf("Open error\n");
		return 1;
	}
}

int buzzerPlaySong (int scale)
{
	buzzerEnable(1);


}

int buzzerStopSong (void)
{
	buzzerEnable(0);
	
}

int buzzerExit (void)
{
	close(fd);
}
