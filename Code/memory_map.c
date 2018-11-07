#include "memory_map.h"


static volatile char* memory = (char *) 0x0000;

volatile char* get_mem()
{
	return memory; 
}

     
uint8_t memory_read_ADC(CHANNEL c)
{
	memory[ADC] = c;
	_delay_ms(1);
	return (memory[ADC] & 0x00ff);
}


void memory_write_oled_command(uint8_t com)
{
	memory[OLED_command] = com;
}

void memory_write_oled_data(uint8_t com)
{
	//static volatile char* m = (char *) 0x1200;
	//*m = com;
	memory[OLED_data] = com;
}

