#include "ADC_internal.h"
#include <avr/io.h>

void ADC_internal_init()
{
    ADCSRB = 0;
    // ADC0 and using AVCC with external capacitor at AREF pin
    ADMUX = (1 << REFS0);

    // Enable
    ADCSRA = (1 << ADEN);
}

uint16_t ADC_internal_status()
{
    // start conversion
    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC));
    return ADC;
}