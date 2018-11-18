#include "../lib/defines.h"
#include "pwm.h"
#include <avr/io.h>
#include <avr/interrupt.h>


void pwm_init()
{
    cli();

    // PE3 output. --> pin5 atmega/shield
    DDRE   |= (1 << PE3);
    TCCR3A = (1 << COM3A1);

    // Speaker
    //DDRL   |= (1 << PL3) | (1 << PL4) | (1 << PL5);
    //TCCR5A =  (1 << COM5A1) | (1 << COM5B1) | (1 << COM5C1);

    /* Mode 14 - Fast PWM */
    TCCR3A |= (1 << WGM31);
    TCCR3B |= (1 << WGM33) | (1 << WGM32);

    /* Mode 14 - Fast PWM */
    //TCCR5A |= (1 << WGM51);
    //TCCR5B |= (1 << WGM53) | (1 << WGM52);

    /*Prescale, 8*/
    TCCR3B |= (1 << CS31);
    //TIMSK3 |= (1 << OCIE3A);
    //TCCR5B |= (1 << CS51);

    ICR3 = 39999;
    //ICR5 = 39999;

    //OCR5A = 20000;
    //OCR5B = 20000;
    //OCR5C = 20000;
    sei();

    pwm_set_angle(0);
    //pwm_stop_frequency();
}



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



void pwm_set_frequency(float frequency)
{
    ICR5 = (uint16_t)(F_CPU / (2.0 * 8.0 * frequency) - 1.0);
    OCR5A  = ICR5 >> 1;
}

void pwm_stop_frequency()
{
    TCCR5B &= ~((1 << CS50) | (1 << CS51) | (1 << CS52));
}

void pwm_start_frequency()
{
    TCCR5B |= ((0 << CS50) | (1 << CS51) | (0 << CS52));
}

