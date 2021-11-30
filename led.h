#ifndef _LED_H_
#define _LED_H_
int ledLiblnit(void);
int ledOnOff(int ledNum, int ofOff);
int ledStatus (void);
int ledLibExit(void);
int ledValue(void);

#define LED_DRIVER_NAME
"/dev/periled"

#endif _LED_H_
