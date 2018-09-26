#include "OLED.h"
#include "memory_map.h"
#include "fonts.h"

CURSOR cur = {0, 0};

void OLED_init()
{
    memory_write_oled_command(0xae); // display off
    memory_write_oled_command(0xa1); // segment remap
    memory_write_oled_command(0xda); // common pads hardware: alternative
    memory_write_oled_command(0x12); 
    memory_write_oled_command(0xc8); // common output scan direction: com63~com0
    memory_write_oled_command(0xa8); // multiplex ration mode: 63
    memory_write_oled_command(0x3f);
    memory_write_oled_command(0xd5); // display divide ratio/osc. freq. mode
    memory_write_oled_command(0x80); 
    memory_write_oled_command(0x81); // contrast control
    memory_write_oled_command(0x50);
    memory_write_oled_command(0xd9); // set precharge period
    memory_write_oled_command(0x21);
    memory_write_oled_command(0x20); // set memory addressing mode
    memory_write_oled_command(0x02); 
    memory_write_oled_command(0xdb); // VCOM deselect level mode
    memory_write_oled_command(0x30);
    memory_write_oled_command(0xad); // master configuration 
    memory_write_oled_command(0x00);
    memory_write_oled_command(0xa4); // out follows RAM content
    memory_write_oled_command(0xa6); // set normal display
    memory_write_oled_command(0xaf); // display on
}

void OLED_reset()
{
    memory_write_oled_command(0xB0);
    memory_write_oled_command(0x00);
    memory_write_oled_command(0x10);
    for (int i = 0; i < 8; ++i)
    {
        OLED_clear_line(i);
    }
}

void OLED_fill()
{
    OLED_home();

    for (int i = 0; i < 8; ++i)
    {   
        memory_write_oled_command(0xB0 | i);
        memory_write_oled_command(0x00);
        memory_write_oled_command(0x10);
        for (int j = 0; j < 128; ++j)
        {
            memory_write_oled_data(0xFF);
        }
    }
}

void OLED_home()
{
    memory_write_oled_command(0xB0);
    memory_write_oled_command(0x00);
    memory_write_oled_command(0x10);
}

void OLED_goto_line(uint8_t line)
{
    memory_write_oled_command(0xB0 | line);
}

void OLED_goto_column(uint8_t column)
{
    memory_write_oled_command(0x00 | ((column & 0x0F) >> 0));
    memory_write_oled_command(0x10 | ((column & 0xF0) >> 4));
}

void OLED_clear_line(uint8_t line)
{
    memory_write_oled_command(0xB0 | line);
    memory_write_oled_command(0x00);
    memory_write_oled_command(0x10);
    for (int j = 0; j < 128; ++j)
    {
        memory_write_oled_data(0x00);
    }
}

void OLED_pos(uint8_t row, uint8_t column)
{
    OLED_goto_line(row);
    OLED_goto_column(column);
}

void OLED_put_char(char c)
{
    for (int i = 0; i < 5; ++i)
    {
        ++cur.COL;
        memory_write_oled_data(pgm_read_byte(&font5[c - ' '][i])); //må lese fra progmem
    }
}

void OLED_print(const char* string)
{
    if (string != NULL)
    {
        char c = *string;
        int i = 0;
        
        while (c != '\0')
        {
            if (c != '\n')
            {
                OLED_put_char(c);
            }
            else
            {
                cur.PAGE = (cur.PAGE + 1) % 8;
                cur.COL  = 0;
                OLED_pos(cur.PAGE, cur.COL);
            }
            
            c = string[++i];
        }
    }
}