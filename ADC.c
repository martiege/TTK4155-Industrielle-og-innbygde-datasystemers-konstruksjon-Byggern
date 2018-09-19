#include <util/delay.h>
#include "ADC.h"
#include "memory_map.h"


int ADC_read_channel(CHANNEL c)
{
	memory[ADC] = c;
	_delay_ms(1);
	return (memory[ADC] & 0x00ff);
}