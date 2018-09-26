#ifndef OLED_H
#define OLED_H


void OLED_init();

void OLED_reset();

void OLED_fill();

void OLED_home();

void OLED_goto_line(int line);

void OLED_goto_column(int column);

void OLED_clear_line(int line);

void OLED_pos(int row, int column);

void OLED_print(char* string);


#endif