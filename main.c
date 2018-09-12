#include <avr/io.h>

//#define F_CPU 1000000UL
#define F_CPU 4915200UL
#include <util/delay.h>
#include "UART.h"
#include "SRAM_test.h"
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1


int main()
{
    USART_Init(MYUBRR);
    MCUCR |= (1<<SRE);
    SFIOR |= (1 << XMM2);

    SRAM_test();

    printf("testing\n");
}
