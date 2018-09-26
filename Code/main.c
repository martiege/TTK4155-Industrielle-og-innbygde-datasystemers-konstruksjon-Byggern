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

int main()
{
    USART_Init(MYUBRR);

    MCUCR |= (1 << SRE);
    SFIOR |= (1 << XMM2);

    SRAM_test();

    OLED_init();

    printf("Starting...\n");
    
    //OLED_goto_line(0);
    //OLED_goto_column(0);
    /*
    //addr mode
    memory_write_oled_command(0x20);
    memory_write_oled_command(0);
    //set start & end addr
    memory_write_oled_command(0x21);
    memory_write_oled_command(0);    
    memory_write_oled_command(128);
    */

    // OLED_goto_line(0);

    
    OLED_reset();

    //OLED_home();
    OLED_pos(7,10);


    int i = 0;

    OLED_put_char('b');
    

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

