#include "../lib/defines.h"
#include "OLED.h"
#include "user_input.h"
#include <util/delay.h>
#include "menu.h"


void menu_print(const char **menu, int length, int cursorpos)
{
    OLED_home();
    for(int i = 0; i < length ; i++)
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
        OLED_print(" \n");
       
    }
    if(length < 8){
        for(int i = length ; i < 8 ; i++)
        {
            OLED_print(" \n");
        }
    }
}

int menu(const char **menu, int length)
{
    int pos = 0;
    while (!user_input_joystick_button())
    {
        menu_print(menu, length, pos);
        Direction dir = user_input_joystick_direction();
        if(dir == UP)
        {
            if (--pos < 0)
            {
                pos = 7;
            } 
            _delay_ms(700);
        }
        else if (dir == DOWN)
        {
            if (++pos > 7)
            {
                pos = 0;
            }
            _delay_ms(700);
        }
        else
        {
            _delay_ms(100);
        }
    }

    return pos;
}

