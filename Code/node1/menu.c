#include "../lib/defines.h"
#include "OLED.h"
#include "user_input.h"
#include <util/delay.h>
#include "menu.h"
#include "node1.h"
#include "../lib/CAN.h"
#include "../lib/input_com.h"

void menu_contrast_menu();
void menu_font_size_menu();
void menu_settings_menu();
void menu_game_settings_menu();
void menu_controller_settings_menu();
void menu_difficulty_settings_menu();
void menu_ingame_menu();

void menu_print(const char **menu, int start, int length, int cursorpos)
{
    OLED_home();
    for(int i = 0; i < 8; i++)
    {
        OLED_print(menu[i]);
        if(i == cursorpos)
        {
            OLED_pos(i, 110);
            OLED_put_char('*');
        }
        else
        {
            OLED_pos(i, 110);
            OLED_put_char(' ');
        }
        OLED_pos(i + 1, 0);
    }
}


int menu_select(const char **menu, int start, int length)
{
    int pos = start;
    while (!user_input_joystick_button())
    {
        menu_print(menu, start, length, pos);
        Direction dir = user_input_joystick_direction();
        //user_input_joystick_print_direction(dir);
        if(dir == UP)
        {
            if (--pos < start)
            {
                pos = start + length - 1;
            } 
            _delay_ms(200);
        }
        else if (dir == DOWN)
        {
            if (++pos > (start + length - 1))
            {
                pos = start;
            }
            _delay_ms(200);
        }
        else
        {
            _delay_ms(100);
        }
        /*return to main menu*/
        if (user_input_leftbutton())
        {
            OLED_reset();
            menu_main();
        } 
    }

    _delay_ms(300);
    OLED_reset();
    OLED_pos(pos, 0);
    OLED_print(menu[pos]);
    OLED_pos(pos, 110);
    OLED_put_char('v');
    _delay_ms(500);
    OLED_reset();

    return pos;
}

void menu_welcome()
{
    OLED_reset();
    OLED_pos(3, 40);
    OLED_set_font_size(8);
    OLED_print("WELCOME");
    _delay_ms(1500);
    OLED_set_font_size(5);
    OLED_reset();
}

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

void menu_main()
{
    while (1)
    {
        switch(menu_select(main_menu, main_menu_start, main_menu_length))
        {
            case 0:
                //play game
                menu_ingame_menu();
                break;
            case 1:
                menu_settings_menu();
                break;
            case 2:
                menu_game_settings_menu();
                break;
            default:
                break;
        }
    }
}


void menu_ingame_menu()
{
    OLED_reset();
    OLED_home();
    OLED_print("Press left button to end \ngame");

    int chose_to_end = 0;
    
    while (get_number_of_lives()) //bytt ut 1 med number_of_lives
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

        OLED_put_int(get_number_of_lives());
    }
    if (!chose_to_end)
    {
        OLED_reset();
        OLED_print("\n\n   GAME OVER :(");
        _delay_ms(3000);
    }
    OLED_reset();
    set_number_of_lives(20); //reset lives
    
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

void menu_settings_menu()
{
    while(1)
    {
        switch(menu_select(settings_menu, settings_menu_start, settings_menu_length))
        {
            case 1:
                menu_contrast_menu();
                break;
            case 2:
                menu_font_size_menu();
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

void menu_game_settings_menu()
{
    while (1)
    {
        switch(menu_select(game_settings_menu, game_settings_menu_start, game_settings_menu_length))
        {
            case 1:
                menu_controller_settings_menu();
                break;
            case 2:
                menu_difficulty_settings_menu();
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
    "Bluetooth + joy", 
    "Back", 
    "", 
    ""
};

const int controller_settings_menu_start =  1;
const int controller_settings_menu_length = 5;

void menu_controller_settings_menu()
{
    CAN_message m;
    m.id = CONTROLLER_SETTINGS;
    m.length = 1;
    while (1)
    {
        int _position = menu_select(controller_settings_menu, controller_settings_menu_start, controller_settings_menu_length);
        switch(_position)
        {
            case 1:
            case 2:
            case 3:
            case 4:
                m.data[0] = _position - 1;
                CAN_send(&m);
                return;
            case 5:
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
    "Easy", 
    "Harder", 
    "Superduper hard", 
    "Back", 
    "", 
    "", 
    ""
};

const int difficulty_settings_menu_start =  1;
const int difficulty_settings_menu_length = 4;

void menu_difficulty_settings_menu()
{
    while (1)
    {
        int _position = menu_select(difficulty_settings_menu, difficulty_settings_menu_start, difficulty_settings_menu_length);
        switch(_position)
        {
            case 1:
                set_number_of_lives(20);
                return;
            case 2:
                set_number_of_lives(10);
                return;
            case 3:
                set_number_of_lives(5);
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

void menu_contrast_menu()
{
    while (1)
    {
        switch (menu_select(contrast_menu, contrast_menu_start, contrast_menu_length))
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

void menu_font_size_menu()
{
    while (1)
    {
        switch (menu_select(font_size_menu, font_size_menu_start, font_size_menu_length))
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