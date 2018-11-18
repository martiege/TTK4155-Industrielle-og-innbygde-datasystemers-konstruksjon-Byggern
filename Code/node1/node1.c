#include "node1.h"
#include "OLED.h"
#include "../lib/defines.h"
#include "../lib/UART.h"
#include "../lib/SPI.h"
#include "../lib/MCP.h"
#include "../lib/CAN.h"
#include "../lib/input_com.h"


#include "menu.h"

const char *_menu[8] = 
{
    "", 
    "", 
    "", 
    "", 
    "", 
    "", 
    "", 
    ""
};

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

const char *contrast_menu[8] = 
{ 
    "Contrast: 32,   12.5%%", 
    "Contrast: 64,   25.0%%", 
    "Contrast: 96,   37.5%%", 
    "Contrast: 128,  50.0%%", 
    "Contrast: 160,  62.5%%", 
    "Contrast: 192,  75.0%%", 
    "Contrast: 224,  87.5%%", 
    "Contrast: 255, 100.0%%"
};

const char *font_size_menu[8] = 
{
    "Font size: 4", 
    "Font size: 5", 
    "Font size: 8", 
    "Font size: ", 
    "Font size: ", 
    "Font size: ", 
    "Font size: ", 
    "Font size: "
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
    while (1)
    {
        switch (menu(contrast_menu, 0, 8))
        {
            case 0:
                OLED_set_contrast();
                break;
            case 1:
                OLED_set_contrast();
                break;
            case 2:
                OLED_set_contrast();
                break;
            case 3:
                OLED_set_contrast();
                break;
            case 4:
                OLED_set_contrast();
                break;
            case 5:
                OLED_set_contrast();
                break;
            case 6:
                OLED_set_contrast();
                break;
            case 7:
                OLED_set_contrast();
                break;
        }
    }
}