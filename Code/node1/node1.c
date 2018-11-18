#include "node1.h"
#include "OLED.h"
#include "../lib/defines.h"
#include "../lib/UART.h"
#include "../lib/SPI.h"
#include "../lib/MCP.h"
#include "../lib/CAN.h"
#include "../lib/input_com.h"


#include "menu.h"

void node1_contrast_menu();
void node1_font_size_menu();
void node1_settings_menu();
void node1_game_settings_menu();


/* //Standard menu
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
};*/

const char *main_menu[8] = 
{
    //"TITLE",
    "Play game", 
    "System settings", 
    "Game settings", 
    "", 
    "", 
    "", 
    ""
};

const int main_menu_start =  0;
const int main_menu_length = 3;

void node1_main_menu()
{
    switch(menu(main_menu, main_menu_start, main_menu_length))
    {
        case 0:
            //play game
            break;
        case 1:
            node1_settings_menu();
            break;
        case 2:
            node1_game_settings_menu();
            break;
        default:
            break;
    }
}

const char *settings_menu[8] = 
{
    "SYSTEM SETTINGS",
    "Set contrast", 
    "Set font size", 
    "Back", 
    "", 
    "", 
    "", 
    ""
};

const int settings_menu_start =  1;
const int settings_menu_length = 3;

void node1_settings_menu()
{
    switch(menu(settings_menu, settings_menu_start, settings_menu_length))
    {
        case 1:
            node1_contrast_menu();
            break;
        case 2:
            node1_font_size_menu();
            break;
        case 3:
            // Back
        default:
            break;
    }
}


const char *game_settings_menu[8] = 
{
    "GAME SETTINGS",
    "Controllers", 
    "Difficulty", 
    "Back", 
    "", 
    "", 
    "", 
    ""
};

const int game_settings_menu_start =  1;
const int game_settings_menu_length = 3;

void node1_game_settings_menu()
{
    switch(menu(game_settings_menu, game_settings_menu_start, game_settings_menu_length))
    {
        case 1:
            //stuff
            //break;
        case 2:
            //stuff
            //break;
        case 3:
            // Back
        default:
            break;
    }
}

const char *contrast_menu[8] = 
{ 
    "CHOOSE CONTRAST",
    "25.0 \%", 
    "50.0 \%", 
    "75.0 \%", 
    "100.0 \%",
    "Back",
    "",
    ""
};

const int contrast_menu_start =  1;
const int contrast_menu_length = 5;

void node1_contrast_menu()
{
    switch (menu(contrast_menu, contrast_menu_start, contrast_menu_length))
        {
            case 1:
                // 25 %
                OLED_set_contrast(64);
                break;
            case 2:
                // 50 %
                OLED_set_contrast(128);
                break;
            case 3:
                // 75 %
                OLED_set_contrast(192);
                break;
            case 4:
                // 100 %
                OLED_set_contrast(255);
                break;
            case 5:
                //BACK
            default:
                break;
        }
}


const char *font_size_menu[8] = 
{
    "CHOOSE FONT SIZE",
    "Size 4", 
    "Size 5", 
    "Size 8", 
    "Back", 
    "", 
    "", 
    ""
};

const int font_size_menu_start =  1;
const int font_size_menu_length = 4;

void node1_font_size_menu()
{
    switch (menu(font_size_menu, font_size_menu_start, font_size_menu_length))
    {
        case 1:
            OLED_set_font_size(4);
            break;
        case 2:
            OLED_set_font_size(5);
            break;
        case 3:
            OLED_set_font_size(8);
            
            break;
        case 4:
            // Back
        default:
            break;
    }
}


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
        //node1_settings_menu();
        node1_main_menu();

    }
}