#include "defines.h"
#include "pwm.h"
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

    float duty_f = 1.5 - (float)angle / 180;
    //printf("duty: %d\n", (uint32_t)(duty_f*1000));
    //long int duty = 15 * ICR3 / 200 - angle * ICR3 / (20 * 180);
    // overflow

    if (duty_f <= 2 && duty_f >= 1) /*((duty <= 2 * ICR3 / 20) && (duty >= 1 * ICR3 / 20)) ||*/
    {
        //OCR3A = duty;
        //printf("OCR3A: %d\n", OCR3A);
        OCR3A = duty_f * ICR3 / 20;
        //printf("OCR3A: %d\n", OCR3A);
    }  
}

/*
void set_duty_cycle(float percentage)
{
    if (percentage <= 100 && percentage >= 0)
    {
        OCR3A = ((percentage / 100.0) * (1.0 / 20.0) + (1.0 / 20.0)) * ICR3;
    }   
}
*/

void pwm_init()
{
    cli();

    // PE3 output. --> pin5 atmega/shield
    //DDRB   |= (1 << DDB5);
    DDRE   |= (1 << DDE3);
    TCCR3A = (1 << COM3A1);
    
    /*Mode 14 - Fast PWM*/
   // TCCR3A |= (1 << WGM11);
   // TCCR3B |= (1 << WGM13) | (1 << WGM12);
   TCCR3A |= (1 << WGM31);
   TCCR3B |= (1 << WGM33) | (1 << WGM32);

    /*Prescale, 8*/
    TCCR3B |= (1 << CS31);

    //ICR3 = 19999;
    ICR3 = 39999;

    //set duty
    //OCR3A = 3000;
    //sei();

    set_angle(0);
}

/*
Set duty cycle: ICRn

P.155: Set OCnA/OCnB/OCnC on compare match, 
clear OCnA/OCnB/OCnC at BOTTOM (inverting mode)


*/

