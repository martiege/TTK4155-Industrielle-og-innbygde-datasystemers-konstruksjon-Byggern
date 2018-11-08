#include "defines.h"
#include "motor.h"
#include "DAC.h"

#include <util/delay.h>

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
    motor_reset()
    // !OE high
    MOTOR_CONFIG |= (1 << MOTOR_OE);
    
    return encoder;
}

void motor_reset()
{
	MOTOR_CONFIG &= ~(1 << PH6);
	_delay_us(20);
	MOTOR_CONFIG |= (1 << PH6);
}

void motor_set_speed(int8_t speed)
{
    printf("Speed %d\n", speed);
    if(speed < 0)
    {
        printf("Negative\n");
        //motor_set_dir(0);
        MOTOR_CONFIG |= (1 << PH1);
        //printf("PINH %x\n", PINH&(1 << PH1));
        DAC_send_speed((uint8_t)(-speed));
    }
    else
    {   
        printf("Positive\n");
        //motor_set_dir(1);
        MOTOR_CONFIG &= ~(1 << PH1);
        //printf("PINH %x\n", PINH & (1 << PH1));
        DAC_send_speed((uint8_t)speed);
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
