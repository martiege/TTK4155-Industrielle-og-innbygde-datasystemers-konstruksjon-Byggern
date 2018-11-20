#ifndef DAC_H
#define DAC_H
#include <stdint.h>

/***********************************
Digital to Analog Converter (DAC)

Implements sending a 0-5V signal
corresponding to a 0-255 bit signal,
to set the motor speed using 
the TWI.h module. 


***********************************/
/*Provides 0-5V analog signal to the motor through I2C bus*/

void DAC_send_speed(uint8_t val);


#endif