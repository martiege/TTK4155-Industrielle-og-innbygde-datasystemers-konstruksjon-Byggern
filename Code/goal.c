#include "goal.h"
#include <avr/io.h>

// R = 330 kOhm

void goal_init()
{
    // Enable
    ADCSRA = (1 << ADEN);

    // ADC0
    ADMUX = (1 << REFS0);

    // prescaler
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t goal_status()
{
    // start conversion
    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC));
    return (ADCH << 8) | ADCL;
}