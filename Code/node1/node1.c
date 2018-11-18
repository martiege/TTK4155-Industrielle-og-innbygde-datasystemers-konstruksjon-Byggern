#include "node1.h"
#include "OLED.h"
#include "../lib/defines.h"
#include "../lib/UART.h"
#include "../lib/SPI.h"
#include "../lib/MCP.h"
#include "../lib/CAN.h"
#include "../lib/input_com.h"


const char *main_menu[8] = 
{
    "Play game", 
    "Settings", 
    "", 
    "", 
    "", 
    "", 
    "", 
    ""
};

const char *settings_menu[8] = 
{
    "Set contrast", 
    "Set font size", 
    "", 
    "", 
    "", 
    "", 
    "", 
    ""
};

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
    
}