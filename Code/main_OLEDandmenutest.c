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
    USART_Init(MYUBRR);

    MCUCR |= (1 << SRE);
    SFIOR |= (1 << XMM2);

    SRAM_test();

    OLED_init();

    printf("Starting...\n");

    
    OLED_reset();

   // OLED_home();
    
    const char* m[8] = {"hei0", "hei1", "hei2", "hei3", "hei4", "hei5", "hei6", "hei7"};
    for(int i = 0; i < 8 ; i++)
    {
        printf("%s\n", m[i]);
       
    }
    int pos = menu(m,8);

    printf("%d",pos);
    int i = 0;
    
    
    while(1)
    {
        
        
        _delay_ms(1000);

        
        
        _delay_ms(1000);
        /*
        _delay_ms(1000);

        OLED_fill();
        
        _delay_ms(1000);

        OLED_clear_line(2);
        OLED_clear_line(4);
        */
    }

    printf("Stopping...\n");

}

