#include "defines.h"
#include "pwm.h"
#include <avr/io.h>
#include <avr/interrupt.h>


void pwm_set_angle(int8_t angle)
{
    if (angle > 90)
    {
        angle = 90;
    }

    if (angle < -90)
    {
        angle = -90;
    }

    float duty_f = 1.5 - (float)angle / 180; //float due to overflow when using int

    if (duty_f <= 2 && duty_f >= 1)
    {
        OCR3A = duty_f * ICR3 / 20;
    }  
}

void pwm_init()
{
    cli();

    // PE3 output. --> pin5 atmega/shield
    DDRE   |= (1 << DDE3);
    TCCR3A = (1 << COM3A1);
    
    /*Mode 14 - Fast PWM*/
    TCCR3A |= (1 << WGM31);
    TCCR3B |= (1 << WGM33) | (1 << WGM32);

    /*Prescale, 8*/
    TCCR3B |= (1 << CS31);
    //TIMSK3 |= (1 << OCIE3A);

    ICR3 = 39999;

    sei();

    pwm_set_angle(0);
}
