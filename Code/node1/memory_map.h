#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include "../lib/defines.h"
#include <util/delay.h>

/******************************************
Memory map module

Implements ability to use external
memory, with specifications for 
SRAM, OLED data, OLED command and
ADC.

Also implements enums for 
easy use of the addressing 
and channel masks utilized.  

Includes the private variable
memory, which allows for 
accsess to external memory.

The functions implemented are:

	memory_read_ADC(CHANNEL c)
	
		Returns the value found
		at CHANNEL c, as described
		in the datasheet for 
		ADC0844.
		
	memory_write_oled_command(uint8_t com)
		
		Writes the OLED command com to
		the OLED. 
	
	memory_write_oled_data(uint8_t com)
	
		Writes the OLED data com to
		the OLED. 
		
	memory_write_sram_data(uint16_t address,
						   uint8_t data)
	
		Writes the parameter data to the
		SRAM address. 
		
	memory_read_sram_data(uint16_t address)
	
		Reads the value stored at the 
		SRAM address. 

******************************************/

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


uint8_t memory_read_ADC(CHANNEL c);

void memory_write_oled_command(uint8_t com);

void memory_write_oled_data(uint8_t com);

void memory_write_sram_data(uint16_t address, uint8_t data);

uint8_t memory_read_sram_data(uint16_t address);


#endif