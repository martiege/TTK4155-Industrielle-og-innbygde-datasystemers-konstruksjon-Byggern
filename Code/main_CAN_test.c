#include "defines.h"


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
#include "CAN.h"
#include "MCP2515.h"
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
    CAN_init();
    /*init end*/
    uint8_t *d = { 2 };
    uint8_t *e = { 3 };

    CAN_message m;
    m.id = 5;
    m.length = 1;
    m.data = d;

    CAN_message n;

    CAN_send(&m);
    //m.id = 2;
    

    while(1)
    {
        //MCP_reset();
        _delay_ms(5);
        CAN_receive(&n);
        printf("ID: %d\n", n.id);

        _delay_ms(500);
        
        if (MCP_read(MCP_CANINTF) & 1)
        {
            printf("rec\n");
        }
        //m.id = 1;
        CAN_send(&m);
        //m.id = 2;

        _delay_ms(10);
    }

    printf("Stopping...\n");

}

