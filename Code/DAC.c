#include "DAC.h"
#include "TWI_Master.h"
#include "defines.h"

#include <util/delay.h>
#include <avr/interrupt.h>


void DAC_send_speed(uint8_t val)
{
    /*package with slave address 0101000, output = DAC0, value*/
    unsigned char package[3] = {(0b0101 << 4 ), 0x00 , val};
    TWI_Start_Transceiver_With_Data(package, 3);
    _delay_ms(1);
}

