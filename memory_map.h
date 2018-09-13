#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include <stdlib.h>


enum ADDR 
{
	OLED_command = 0x1000, 
	OLED_data = 0x1200, 
	ADC = 0x1400, 
	SRAM = 0x1800
};

volatile char* memory = (char *) 0x0000;



#endif