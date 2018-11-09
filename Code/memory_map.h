#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include "defines.h"
#include <stdio.h>
#include <util/delay.h>

typedef enum ADDR 
{
	OLED_command = 0x1000, 
	OLED_data    = 0x1200, 
	ADC          = 0x1400, 
	SRAM         = 0x1800
} ADDR;


typedef enum CHANNEL 
{
	CH1 = 0b0100, 
	CH2 = 0b0101, 
	CH3 = 0b0110, 
	CH4 = 0b0111
} CHANNEL;


volatile char* get_mem();

uint8_t memory_read_ADC(CHANNEL c);

void memory_write_oled_command(uint8_t com);

void memory_write_oled_data(uint8_t com);

void memory_write_sram_data(uint16_t address, uint8_t data);

uint8_t memory_read_sram_data(uint16_t address);


#endif