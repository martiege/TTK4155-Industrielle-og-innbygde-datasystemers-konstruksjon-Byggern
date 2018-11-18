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


void node1_contrast_menu();
void node1_font_size_menu();
void node1_settings_menu();
void node1_game_settings_menu();
void node1_controller_settings_menu();
void node1_ingame_menu();

static uint8_t number_of_lives = 100;

void decrease_lives() { number_of_lives--; }


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
    while (1)
    {
        switch(menu(main_menu, main_menu_start, main_menu_length))
        {
            case 0:
                //play game
                node1_ingame_menu();
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
}


void node1_ingame_menu()
{
    OLED_reset();
    OLED_home();
    OLED_print("Press left button to end \ngame");

    int chose_to_end = 0;
    
    while (number_of_lives) //bytt ut 1 med number_of_lives
    {
        input_com_send();
        _delay_ms(100);
        if (user_input_leftbutton())
        {
            chose_to_end = 1;
            break;
        } 
        OLED_pos(2, 0);
        OLED_clear_line(2);
        OLED_print("Number of lives: ");

        //Hackery to print int
        char *lives;
        *--lives = 0;
        uint8_t copy = number_of_lives;
        if(!copy) *--lives = 0;
        for(; copy ; copy/=10) *--lives = '0' + copy%10;
        
        OLED_print(lives);
    }
    if (!chose_to_end)
    {
        OLED_reset();
        OLED_print("\n\n   GAME OVER :(");
    }
    OLED_reset();    
    
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
    while(1)
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
                return;
            default:
                break;
        }
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
    while (1)
    {
        switch(menu(game_settings_menu, game_settings_menu_start, game_settings_menu_length))
        {
            case 1:
                node1_controller_settings_menu();
                break;
            case 2:
                //stuff
                break;
            case 3:
                // Back
                return;
            default:
                break;
        }
    }
}

const char *controller_settings_menu[8] = 
{
    "CONTROLLERS", 
    "Joystick", 
    "Sliders", 
    "R slider + joy", 
    "Back", 
    "", 
    "", 
    ""
};

const int controller_settings_menu_start =  1;
const int controller_settings_menu_length = 4;

void node1_controller_settings_menu()
{
    CAN_message m;
    m.id = CONTROLLER_SETTINGS;
    m.length = 1;
    while (1)
    {
        int _position = menu(controller_settings_menu, controller_settings_menu_start, controller_settings_menu_length);
        switch(_position)
        {
            case 1:
            case 2:
            case 3:
                m.data[0] = _position - 1;
                CAN_send(&m);
                return;
            case 4:
                return;
                // Back
            default:
                break;
        }
    }
}


const char *difficulty_settings_menu[8] = 
{
    "DIFFICULTY", 
    "Level 1", 
    "Level 2", 
    "Level 3", 
    "Back", 
    "", 
    "", 
    ""
};

const int difficulty_settings_menu_start =  1;
const int difficulty_settings_menu_length = 4;

void node1_difficulty_settings_menu()
{
    while (1)
    {
        int _position = menu(difficulty_settings_menu, difficulty_settings_menu_start, difficulty_settings_menu_length);
        switch(_position)
        {
            case 1:
                number_of_lives = 20;
                return;
            case 2:
                number_of_lives = 10;
                return;
            case 3:
                number_of_lives = 5;
                return;
            case 4:
                return;
                // Back
            default:
                break;
        }
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
    while (1)
    {
        switch (menu(contrast_menu, contrast_menu_start, contrast_menu_length))
        {
            case 1:
                // 25 %
                OLED_set_contrast(64);
                return;
            case 2:
                // 50 %
                OLED_set_contrast(128);
                return;
            case 3:
                // 75 %
                OLED_set_contrast(192);
                return;
            case 4:
                // 100 %
                OLED_set_contrast(255);
                return;
            case 5:
                return;
                //BACK
            default:
                break;
        }
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
    while (1)
    {
        switch (menu(font_size_menu, font_size_menu_start, font_size_menu_length))
        {
            case 1:
                OLED_set_font_size(4);
                return;
            case 2:
                OLED_set_font_size(5);
                return;
            case 3:
                OLED_set_font_size(8);
                return;
            case 4:
                return;
                // Back
            default:
                break;
        }
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