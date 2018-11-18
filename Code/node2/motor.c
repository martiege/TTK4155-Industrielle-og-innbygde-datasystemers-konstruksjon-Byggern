#include "../lib/defines.h"
#include <util/delay.h>
#include "../lib/UART.h"
#include "motor.h"
#include "DAC.h"



void motor_init()
{
    /*ADC8-15 (MJ2) as inputs*/
    DDRK = 0;

    /*MJ1 outputs*/
    DDRH |= 
    (1 << MOTOR_DIR) | 
    (1 << MOTOR_SEL) | 
    (1 << MOTOR_EN ) |
    (1 << MOTOR_OE ) | 
    (1 << MOTOR_RST) 
	;

    MOTOR_CONFIG |= (1 << MOTOR_EN);
	
	motor_reset();

    motor_set_speed(0);
    
    motor_speed = 0;
}


int16_t motor_encoder_read()
{
    // !OE low
    MOTOR_CONFIG &= ~(1 << MOTOR_OE);
    // SEL low -> get high byte
    MOTOR_CONFIG &= ~(1 << MOTOR_SEL);
    // wait 20 microseconds
    _delay_us(20);
    // read MSB and left shift
    int16_t encoder = (MOTOR_ENCODER << 8);
    // set SEL high to get low byte
    MOTOR_CONFIG |= (1 << MOTOR_SEL);
    // wait 20 microseconds
    _delay_us(20);
    // read LSB
    encoder |= MOTOR_ENCODER;
    // toggle !RST to reset encoder
    // motor_reset();
    // !OE high
    MOTOR_CONFIG |= (1 << MOTOR_OE);
    
    return encoder;
}

void motor_reset()
{
	MOTOR_CONFIG &= ~(1 << MOTOR_RST);
	_delay_us(20);
	MOTOR_CONFIG |= (1 << MOTOR_RST);
}

void motor_set_speed(int16_t speed)
{
    //printf("speed %d\n", speed);
    if(speed < -5)
    {
        if(speed > -50) speed = -50;
        //printf("Negative\n");
        motor_set_dir(0);
        DAC_send_speed((uint8_t)((-speed) & 0xFF));        
    }
    else if(speed > 5)
    {   
        if(speed < 50) speed = 50;
        //printf("Positive\n");
        motor_set_dir(1);
        DAC_send_speed((uint8_t)(speed & 0xFF));
    } 
    else{
        DAC_send_speed(0);
    }
}


void motor_set_dir(uint8_t dir)
{
    if (dir)
    {
		MOTOR_CONFIG |= (1 << PH1);
        //PINH |= (1 << PH1);
    }
    else
    {
		MOTOR_CONFIG &= ~(1 << PH1);
        //PINH &= ~(1 << PH1);
    }
}
