#include "ADC_internal.h"
#include <avr/io.h>

// R = 330 kOhm
//bruk  AVCC, ikke AREF
void ADC_internal_init()
{
    // Enable
    ADCSRA = (1 << ADEN);

    // ADC0 and using AVCC with external capacitor at AREF pin
    ADMUX = (1 << REFS0);

    // prescaler
    //ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ADC_internal_status()
{
    // start conversion
    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC));
    return (ADCH << 8) | ADCL;
}