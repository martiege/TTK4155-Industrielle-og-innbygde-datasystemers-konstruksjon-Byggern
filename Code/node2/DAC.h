#ifndef DAC_H
#define DAC_H
#include <stdint.h>

/***********************************
Digital to Analog Converter (DAC)

Implements sending a 0-5V signal
corresponding to a 0-255 bit signal,
to set the motor speed using 
the TWI.h module. 

The functions implemented are:

	DAC_send_speed(uint8_t val)
	
		Sets the current DAC signal
		to the voltage value by the
		formula 5 * val / 256. 

***********************************/

void DAC_send_speed(uint8_t val);


#endif