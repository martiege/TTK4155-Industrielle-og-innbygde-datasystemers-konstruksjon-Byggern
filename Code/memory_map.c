#include "memory_map.h"


static volatile char* memory = (char *) 0x0000;

volatile char* get_mem()
{
	return memory; 
}

void memory_write_oled_command(uint8_t com)
{
	memory[OLED_command] = com;
}

void memory_write_oled_data(uint8_t com)
{
	memory[OLED_data] = com;
}
