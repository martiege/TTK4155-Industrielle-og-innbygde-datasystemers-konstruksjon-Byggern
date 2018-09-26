#include "OLED.h"
#include "memory_map.h"


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
    memory_write_oled_command(0xB0);
    memory_write_oled_command(0x00);
    memory_write_oled_command(0x10);
    for (int i = 0; i < 8; ++i)
    {   
        memory_write_oled_command(0xB0 | i);
        memory_write_oled_command(0x00);
        memory_write_oled_command(0x10);
        for (int j = 0; j < 128; ++j)
        {
            memory_write_oled_data(0xff);
        }
    }
}

void OLED_home()
{

}

void OLED_goto_line(int line)
{
    memory_write_oled_command(0x20);
    memory_write_oled_command(1);

    memory_write_oled_command(0x40 + line);
}

void OLED_goto_column(int column)
{
    memory_write_oled_command(0x20);
    memory_write_oled_command(0);

    memory_write_oled_command(0x21);
    
    memory_write_oled_command(column);    
    memory_write_oled_command(column);
    
}

void OLED_clear_line(int line)
{
    memory_write_oled_command(0xB0 | line);
    memory_write_oled_command(0x00);
    memory_write_oled_command(0x10);
    for (int j = 0; j < 128; ++j)
    {
        memory_write_oled_data(0x00);
    }
}

void OLED_pos(int row, int column)
{

}

void OLED_print(char* string)
{

}