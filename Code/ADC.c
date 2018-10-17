#include "defines.h"
#include <util/delay.h>
#include "ADC.h"
#include "memory_map.h"


uint8_t ADC_read_channel(CHANNEL c)
{
	get_mem()[ADC] = c;
	_delay_ms(1);
	return (get_mem()[ADC] & 0x00ff);
}