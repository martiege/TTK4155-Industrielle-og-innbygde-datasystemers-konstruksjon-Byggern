#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include <stdio.h>

enum ADDR 
{
	OLED_command = 0x1000, 
	OLED_data    = 0x1200, 
	ADC          = 0x1400, 
	SRAM         = 0x1800
};

volatile char* get_mem();

void memory_write_oled_command(uint8_t com);

void memory_write_oled_data(uint8_t com);

#endif