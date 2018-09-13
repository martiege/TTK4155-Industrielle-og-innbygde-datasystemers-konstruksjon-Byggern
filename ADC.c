#include "ADC.h"
#include "memory_map.h"

//volatile char* adc = (char *) 0x1400;

int ADC_read_channel(CHANNEL c)
{
	return memory[ADC + c];
	//return adc[c];
}