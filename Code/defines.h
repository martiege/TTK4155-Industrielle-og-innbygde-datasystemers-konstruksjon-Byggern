#ifndef DEFINES_H
#define DEFINES_H

#include <avr/io.h>


/******** NODE 1 *********/
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

	/* TIMER */
	/* TIMER 1 */
	#define TIMER1_vector TIMER1_COMPA_vect
	#define TIMER1_CTRLA TCCR1A
	#define TIMER1_CTRLB TCCR1B
	#define TIMER1_TOP OCR1A
	#define TIMER1_REG TCNT1
	
	
	/* TIMER 2 */
	#define TIMER2_vector TIMER3_COMPA_vect
	#define TIMER2_CTRLA TCCR3A
	#define TIMER2_CTRLB TCCR3B
	#define TIMER2_TOP OCR3A
	#define TIMER2_REG TCNT3
	
	/* controller */
	#define SCALING_FACTOR 128
	#define MAX_INT INT16_MAX
	#define MAX_LONG INT32_MAX
	#define MAX_I_TERM (MAX_LONG / 2)

/******** NODE 2 *********/
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
	
	/* TIMER */
	/* TIMER 1 */
	#define TIMER1_vector TIMER1_COMPA_vect
	#define TIMER1_CTRLA TCCR1A
	#define TIMER1_CTRLB TCCR1B
	#define TIMER1_TOP OCR1A
	#define TIMER1_REG TCNT1
	
	
	/* TIMER 2 */
	#define TIMER2_vector TIMER4_COMPA_vect
	#define TIMER2_CTRLA TCCR4A
	#define TIMER2_CTRLB TCCR4B
	#define TIMER2_TOP OCR4A
	#define TIMER2_REG TCNT4
	

#endif

/******** COMMON *********/
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

/**************************/
#endif