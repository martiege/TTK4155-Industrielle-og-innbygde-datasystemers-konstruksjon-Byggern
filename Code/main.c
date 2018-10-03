#define F_CPU 4915200UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
#include "SRAM_test.h"
#include "ADC.h"
#include "user_input.h"
#include "OLED.h"
#include "memory_map.h"
#include "menu.h"
#include <avr/pgmspace.h>
//#include "SPI.h"

int main()
{
    /*Init start*/
    USART_Init(MYUBRR);

    MCUCR |= (1 << SRE);
    SFIOR |= (1 << XMM2);

    SRAM_test();
    OLED_init();
    printf("Starting...\n");
    SPI_MasterInit();
    /*init end*/

    while(1)
    {
        printf("Shalalala\n");
        SPI_MasterTransmit('a');
        printf("HurraHUrra\n");
        
        //_delay_ms(1000);

    }

    printf("Stopping...\n");

}

