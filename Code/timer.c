#include "timer.h"


void timer_init()
{
    TCCR1A = 0;
    TCCR1B = (1 << WGM12);
    
    //top value
    timer_set_period(100);

    //interrupt
    //OCF1A

    //funksjonspeker til interrupten: goal_interruptfunc
}

void timer_set_period(uint16_t ms)
{
    OCR1A = ms*0.001*F_CPU / (2*256) - 1;
}

void timer_start()
{
    TCNT1 = 0;
    /*Prescale, 256*/
    TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
}

void timer_stop()
{
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
}

//ISR(TIMER1_vect){}