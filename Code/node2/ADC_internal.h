#ifndef ADC_INTERNAL_H
#define ADC_INTERNAL_H

#include <stdint.h>

/*
Analog to Digital Converter (ADC)
internal for Node 2.

Implements ability to use the 
internal ADC on Node 2 to 
read the status of the 
IR sensor. 

*/

void ADC_internal_init();

uint16_t ADC_internal_status();

#endif