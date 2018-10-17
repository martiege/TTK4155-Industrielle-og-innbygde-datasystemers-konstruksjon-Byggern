#ifndef DEFINES_H
#define DEFINES_H

#include <avr/io.h>


/******** ATMEGA *********/
#ifdef __AVR_ATmega162__

    /* generic */
    #define F_CPU 4915200UL

    /*UART*/
    #define USSEL URSEL0

    /*SPI*/





/******** IO BOARD ********/
#elif __AVR_ATmega2560__

    /* generic */
    #define F_CPU 16000000UL

    /*UART*/
    #define USSEL UMSEL00


#endif

/******** COMMON *********/
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

/**************************/
#endif