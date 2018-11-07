#include "ADC.h"



uint8_t ADC_read_channel(CHANNEL c)
{
	/*
	get_mem()[ADC] = c;
	_delay_ms(1);

	uint8_t val = (get_mem()[ADC] & 0x00ff);
	*/
	uint8_t val = memory_read_ADC(c);
	printf("ADC value: %d\n", val);
	return val;
}