#include "node1.h"
#include "OLED.h"
#include "../lib/defines.h"
#include "../lib/UART.h"
#include "../lib/SPI.h"
#include "../lib/MCP.h"
#include "../lib/CAN.h"
#include "../lib/input_com.h"

#include <util/delay.h>

#include "menu.h"
#include "user_input.h" //ta vekk

static uint8_t number_of_lives = 100;

void decrease_lives() { number_of_lives--; }


void node1_init()
{
    UART_Init(MYUBRR);
    MCUCR |= (1 << SRE);

    SPI_MasterInit();
    MCP_reset();
    CAN_init();

    input_com_init();

    SFIOR |= (1 << XMM2);
    OLED_init();
}


void node1_main()
{
    /*
    CAN_message m;
	m.id = BLUETOOTH_MSG;
	m.length = 1;
	m.data[0] = 15;
	while (1)
	{ 
        printf("node1\n");
		printf("ID: %d\n\n", m.id);
		CAN_send(&m);
		_delay_ms(200);
	}
    
    CAN_message m;
    m.id = 0;
	m.length = 1;
	m.data[0] = 15;
    */
    while (1)
    {
        printf("node1\n");
        //CAN_receive(&m);
        //printf("ID: %d\n\n", m.id);
        _delay_ms(100);
        //node1_settings_menu();
        node1_main_menu();
    }
}