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

void SPI_MasterTransmit(char cData)
{
    //PORTB &= ~(1 << PB4); 
    /*Start transmission*/
    SPDR = cData;
    /*Wait for transmission complete*/
    while(!(SPSR & (1 << SPIF)));

    return SPDR;

    //PORTB |= (1 << PB4); 
}





/*SPI Interrupt Enable bit (SPIE) in the SPCR Register*/