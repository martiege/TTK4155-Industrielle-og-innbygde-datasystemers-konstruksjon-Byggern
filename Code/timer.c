#include "defines.h"
#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>


void set_angle(int16_t angle)
{
    if (angle > 90)
    {
        angle = 90;
    }

    if (angle < -90)
    {
        angle = -90;
    }

    float duty = 1.5 - (float)angle / 180;

    if (duty <= 2.0 && duty >= 1.0)
    {
        OCR1A = duty * ICR1 / 20;
    }  
}


void set_duty_cycle(float percentage)
{
    if (percentage <= 100 && percentage >= 0)
    {
        OCR1A = ((percentage / 100.0) * (1.0 / 20.0) + 1.0 / 20.0) * ICR1;
    }
    
}

void timer_init()
{
    cli();

    // PB5 output
    DDRB   |= (1 << DDB5);
    TCCR1A = (1 << COM1A1);
    
    /*Mode 14 - Fast PWM*/
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << WGM12);

    /*Prescale, 8*/
    TCCR1B = (1 << CS11);

    ICR1 = 19999;

    sei();

    //set_angle(0);
}

/*
Set duty cycle: ICRn

P.155: Set OCnA/OCnB/OCnC on compare match, 
clear OCnA/OCnB/OCnC at BOTTOM (inverting mode)


*/

