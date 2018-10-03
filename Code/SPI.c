#include "SPI.h"
#include <avr/io.h>


void SPI_MasterInit()
{
    /*Set MOSI, SCK, and slave select output*/
    DDRB |= (1 << PB5) | (1 << PB7) | (1 << PB4);
    /*Set MISO input*/
    DDRB &= ~(1 << PB6);
    /*Enable SPI, Master, set clock rate fck/16*/
    SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0); 
}