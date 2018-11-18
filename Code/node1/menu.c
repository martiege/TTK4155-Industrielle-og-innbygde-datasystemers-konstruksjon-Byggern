#include "../lib/defines.h"
#include "OLED.h"
#include "user_input.h"
#include <util/delay.h>
#include "menu.h"


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


int menu(const char **menu, int start, int length)
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

