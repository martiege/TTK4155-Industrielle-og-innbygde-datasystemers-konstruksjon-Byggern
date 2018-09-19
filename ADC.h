#ifndef ADC_H
#define ADC_H

#include <stdlib.h>

/*

PB[nederste rad, pin 3] - left slider
PD[øverste rad, pin 1] - right slider

*/

typedef enum CHANNEL 
{
	CH1 = 0b0100, 
	CH2 = 0b0101, 
	CH3 = 0b0110, 
	CH4 = 0b0111
} CHANNEL;


int ADC_read_channel(CHANNEL c);

#endif