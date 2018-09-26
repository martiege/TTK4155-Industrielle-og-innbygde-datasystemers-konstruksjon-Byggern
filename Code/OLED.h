#ifndef OLED_H
#define OLED_H

#include <stdio.h>

void OLED_init();

void OLED_reset();

void OLED_fill();

void OLED_home();

void OLED_goto_line(uint8_t line);

void OLED_goto_column(uint8_t column);

void OLED_clear_line(uint8_t line);

void OLED_pos(uint8_t row, uint8_t column);

void OLED_put_char(char c);

void OLED_print(char* string);


#endif