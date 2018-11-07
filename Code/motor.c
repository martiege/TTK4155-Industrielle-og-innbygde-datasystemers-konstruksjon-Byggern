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
    (1 << PH1) | 
    (1 << PH3) | 
    (1 << PH4) |
    (1 << PH5) | 
    (1 << PH6) 
  ;

    PORTH |= (1 << PH4);
}


int16_t motor_encoder_read()
{
    // !OE low
    PORTH &= ~(1 << PH5);
    // SEL low -> get high byte
    PORTH &= ~(1 << PH3);
    // wait 20 microseconds
    _delay_us(20);
    // read MSB and left shift
    int16_t encoder = (PINK << 8);
    // set SEL high to get low byte
    PORTH |= (1 << PH3);
    // wait 20 microseconds
    _delay_us(20);
    // read LSB
    encoder |= PINK;
    // toggle !RST to reset encoder
    PORTH ^= (1 << PH6);
    // !OE high
    PORTH |= (1 << PH5);
    
    return encoder;
}


void motor_set_speed(int8_t speed)
{
    printf("Speed %d\n", speed);
    if(speed < 0)
    {
        printf("Negative\n");
        //motor_set_dir(0);
        PORTH |= (1 << PH1);
        //printf("PINH %x\n", PINH&(1 << PH1));
        DAC_send_speed((uint8_t)(-speed));
    }
    else
    {   
        printf("Positive\n");
        //motor_set_dir(1);
        PORTH &= ~(1 << PH1);
        //printf("PINH %x\n", PINH & (1 << PH1));
        DAC_send_speed((uint8_t)speed);
    } 
    
}


void motor_set_dir(uint8_t dir)
{
    if (dir)
    {
        PINH |= (1 << PH1);
    }
    else
    {
        PINH &= ~(1 << PH1);
    }
}
