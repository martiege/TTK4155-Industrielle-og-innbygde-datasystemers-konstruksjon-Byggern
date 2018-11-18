#include "ADC.h"

uint8_t ADC_read_channel(CHANNEL c)
{
	return memory_read_ADC(c);
}