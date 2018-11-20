#ifndef OLED_H
#define OLED_H

#include <stdio.h>
#include <stdint.h>

/****************************************
OLED module

Implements useful functions for the OLED. 

Also able to switch between writing 
directly to the OLED or buffering to the
SRAM through the private variable 
use_new_OLED. 

Implements a CURSOR struct to keep track 
of where on the OLED the cursor currently
is. 

The functions implemented are:
	
	OLED_init()
	
		Initializes the OLED screen, 
		as stated in the datasheet. 
		
	OLED_reset()
	
		Resets the OLED and clears the 
		screen. 
		
	OLED_fill()
	
		Fills the OLED screen, opposite 
		of the clearing the screen. 
		
	OLED_home()
	
		Sets the cursor to the top left 
		of the OLED screen. 
		
	OLED_goto_line(uint8_t line)
	
		Moves the cursor to the page
		given by the parameter line. 
		
	OLED_goto_column(uint8_t column)
	
		Moves the cursor to the column
		given by the parameter line.
		
	OLED_clear_line(uint8_t line)
	
		Clears the line given by the 
		parameter line.
		
	OLED_pos(uint8_t row, uint8_t column)
	
		Sets the cursor page to the 
		parameter row, and the cursor
		column to the parameter column.
		
	OLED_set_font_size(uint8_t size)
		
		Sets the current font size to 
		the parameter size, loaded from
		the module font.h. Can be set to
		4, 5 or 8. 
		
	OLED_set_contrast(uint8_t contrast)
	
		Sets the contrast to the value
		of the parameter contrast. 
		
	OLED_put_char(char c)
	
		Writes the character c to the 
		OLED screen. 
		
	OLED_put_int(int number)
	
		Writes the integer number to 
		the OLED screen.
		
	OLED_print(const char* string)
	
		Writes the string to the OLED
		string. 

****************************************/

typedef struct CURSOR
{
    int PAGE;
    int COL; 
} CURSOR;

void OLED_init();

void OLED_reset();

void OLED_fill();

void OLED_home();

void OLED_goto_line(uint8_t line);

void OLED_goto_column(uint8_t column);

void OLED_clear_line(uint8_t line);

void OLED_pos(uint8_t row, uint8_t column);

void OLED_set_font_size(uint8_t size);

void OLED_set_contrast(uint8_t contrast);

void OLED_put_char(char c);

void OLED_put_int(int number);

void OLED_print(const char* string);


#endif