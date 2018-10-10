#ifndef DEFINES_H
#define DEFINES_H

//neste gang: kjøre UART på 128 og se

/******** ATMEGA *********/
#ifdef __AVR_ATmega162__

    /* generic */
    #define F_CPU 4915200UL

    /*UART*/
    //ser ut som de flest er like! evt endre 0

    /*SPI*/





/******** IO BOARD ********/
#elif __AVR_ATmega128__

    /* generic */
    #define F_CPU 16000000UL

    /*UART*/
    //ser ut som de flest er like! evt endre 0



#endif

/******** COMMON *********/
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

/**************************/
#endif