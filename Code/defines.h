#ifndef DEFINES_H
#define DEFINES_H

#include <avr/io.h>


/******** ATMEGA *********/
#ifdef __AVR_ATmega162__

    /* generic */
    #define F_CPU 4915200UL

    /*SPI & MCP*/
    #define SPI_MOSI PB5
    #define SPI_MISO PB6
    #define SPI_SS PB4
    #define SPI_SCK PB7

    /*CAN*/
    #define INTRREG GICR
    #define INTRSEL INT0

    #define INTRSC  ISC11
    #define INTRSET MCUCR
    #define INTRVAL 1


/******** IO BOARD ********/
#elif __AVR_ATmega2560__

    /* generic */
    #define F_CPU 16000000UL

    /*SPI*/
    #define SPI_MOSI PB2
    #define SPI_MISO PB3
    #define SPI_SS PB7
    #define SPI_SCK PB1
    
    /*CAN*/
    #define INTRREG EIMSK
    #define INTRSEL INT2

    #define INTRSC  ISC01    
    #define INTRSET EICRB 
    #define INTRVAL 1

#endif

/******** COMMON *********/
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

/**************************/
#endif