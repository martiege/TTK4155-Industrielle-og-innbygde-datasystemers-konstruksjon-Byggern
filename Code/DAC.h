#ifndef DAC_H
#define DAC_H
#include <stdint.h>


/*Provides 0-5V analog signal to the motor through I2C bus*/

void DAC_send_pos(uint8_t val);


#endif