#ifndef ADC_H
#define ADC_H

#include "../lib/defines.h"
#include "memory_map.h"

/*
Analog to Digital Converter (ADC)

Implements wrapper function for 
the memory_read_ADC function, 
as defined in the memory_map module.

The functions implemented are:

	ADC_read_channel(CHANNEL c)
	
		Wrapper function, reads 
		the value found at 
		CHANNEL c. 
	
*/

uint8_t ADC_read_channel(CHANNEL c);

#endif