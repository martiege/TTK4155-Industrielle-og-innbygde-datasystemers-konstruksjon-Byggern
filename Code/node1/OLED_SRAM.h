#ifndef OLED_SRAM_H
#define OLED_SRAM_H

#include <stdint.h>

/****************************************
OLED SRAM module

Implements useful functions 
for using the OLED with SRAM. 

The functions implemented are:
	
	OLED_SRAM_init()
	
		Initializes the area of SRAM 
		used to buffer the OLED and 
		the timer used to update the 
		OLED screen. 
		
	OLED_reset()
	
		Resets the area of SRAM 
		used to buffer the OLED.
		
	OLED_fill()
	
		Fills the area of SRAM 
		used to buffer the OLED.
		
	OLED_clear_line(uint8_t line)
	
		Clears the line given by the 
		parameter line.
		
	OLED_SRAM_pixel(uint8_t x, uint8_t y, 
					uint8_t clear)
	
		Modifies the OLED pixel at
		coordinates x and y. Sets the
		pixel if clear is 1, clears 
		if it is 0. 
		
	OLED_SRAM_draw_line(uint8_t x0, 
			uint8_t y0, uint8_t x1, 
			uint8_t y1, uint8_t clear)
	
		Draws a line from (x0, y0) to
		(x1, y0). Sets or clears this
		line based on the variable 
		clear.
		
	OLED_SRAM_draw_circle(uint8_t x0, 
			uint8_t y0, uint8_t radius, 
			uint8_t clear, uint8_t fill)
			
		Draws a circle based in (x0, y0), 
		with a radius. Clears the circle
		if the clear variable is 0, 1 to
		set the circle. Fills the circle
		if fill is 1, just the 
		perimeter.
		
	OLED_SRAM_update()
	
		Writes the contents of the SRAM
		to the OLED screen. 

****************************************/

void OLED_SRAM_init();

void OLED_SRAM_reset();

void OLED_SRAM_fill();

void OLED_SRAM_clear_line(uint8_t line);

void OLED_SRAM_write(uint8_t page, uint8_t col, uint8_t data);

uint8_t OLED_SRAM_read(uint8_t page, uint8_t col);

void OLED_SRAM_pixel(uint8_t x, uint8_t y, uint8_t clear);

void OLED_SRAM_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t clear);

void OLED_SRAM_draw_circle(uint8_t x0, uint8_t y0, uint8_t radius, uint8_t clear, uint8_t fill);

void OLED_SRAM_update();


#endif