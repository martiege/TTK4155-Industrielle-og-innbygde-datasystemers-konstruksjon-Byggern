#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
#include "SRAM_test.h"

#define F_CPU 4915200UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1


int main()
{
    USART_Init(MYUBRR);
    MCUCR |= (1<<SRE);
    SRAM_test();
   
}
