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
#include "user_input.h"

static uint8_t number_of_lives = 20;

void decrease_lives() { number_of_lives--; }
uint8_t get_number_of_lives() { return number_of_lives; }
void set_number_of_lives(uint8_t n_lives) { number_of_lives = n_lives; }

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
    while (1)
    {
        printf("node1\n");
        _delay_ms(100);
        menu_main();
    }
}