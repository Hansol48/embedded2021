#include "textlcd.h"
#include <stdlib.h>
#include <sys/mman.h>
#include <asm/fcntl.h>
#include <stdio.h>

#ifndef __TEXTLCD_DRV_H__
#define __TEXTLCD_DRV_H__

#define LINE_NUM			2
#define COLUMN_NUM			16	

#define  LINE_BUFF_NUM 	(COLUMN_NUM + 4)  // for dummy 

#define  MODE_CMD	0
#define  MODE_DATA	1

#define  CMD_DISPLAY_MODE		0x10
	#define  BIT_DISPLAY_MODE_CURSOR_DISP	0x01
	#define  BIT_DISPLAY_MODE_CURSOR_BLINK	0x02
	#define  BIT_DISPLAY_MODE_DISP_ENABLE	0x04

#define  CMD_CURSOR_MOVE_MODE	0x11
	#define CURSOR_MOVE_MODE_ENABLE		0x01
	#define CURSOR_MOVE_MODE_RIGHT_DIR	0x02

#define  CMD_CURSOR_MOVE_POSITION	0x12
	#define  CURSOR_MOVE_X_MASK		0x3F
	#define  CURSOR_MOVE_Y_MASK		0xC0
	
#define  CMD_WRITE_STRING			0x20	
	#define CMD_DATA_WRITE_BOTH_LINE	0
	#define CMD_DATA_WRITE_LINE_1		1
	#define CMD_DATA_WRITE_LINE_2		2
	
#define  CMD_TEST_GPIO_HIGH			0x30
#define  CMD_TEST_GPIO_LOW			0x31

int stTextLCD, cmd, cmdData, reserved;

typedef struct TextLCD_tag 
{
	unsigned char cmd; //
	unsigned char cmdData;  
	unsigned char reserved[2];
	
	char	TextData[LINE_NUM][LINE_BUFF_NUM];
}stTextLCD,*pStTextLCD;


#endif//  __TEXTLCD_DRV_H__

int main(int argc, char **argv)
{
	unsigned int linenum = 0;
	stTextLCD stlcd;
	int fd;
	int len;
	memset(&stlcd,0,sizeof(stTextLCD));
			if (argc < 3)
			{
			perror ("Args number is less than 2\n");
			doHelp();
			return 1;
			}
			linenum = strtol(argv[1], NULL,10);
			printf("linenum: %d\n", linenum);
			if (linenum ==1)
				stlcd.cmdData = CMD_DATA_WRITE_LINE_1;
			else if (linenum ==2)
				stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
			else {
				printf("linenum : %d wrong . range(1~2)\n", linenum);
				return 1; }
			len = strlen(argv[2]);
			if (len > COLUMN_NUM)
				memcpy(stlcd.TextData[stlcd.cmdData - 1], argv[2], COLUMN_NUM);
			else
				memcpy(stlcd.TextData[stlcd.cmdData - 1], argv[2], len);

			stlcd.cmd = CMD_WRITE_STRING;
			fd = open(TEXTLCD_DRIVER_NAME,O_RDWR);
			if (fd < 0)
			{
				perror("driver (//dev//peritextlcd) open error.\n");
				return 1;
			}
			write (fd,&stlcd,sizeof(stTextLCD));
			close(fd);
			return 0;
}

