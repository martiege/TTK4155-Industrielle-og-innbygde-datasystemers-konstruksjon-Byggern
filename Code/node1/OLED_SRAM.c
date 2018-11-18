#include "OLED_SRAM.h"
#include "memory_map.h"
#include "../lib/timer.h"


void OLED_SRAM_init()
{
	OLED_SRAM_reset();
	
	timer_init(1, OLED_SRAM_update);
	timer_set_period(100, 1); 
	timer_start(1);
}


void OLED_SRAM_reset()
{
	for (uint8_t i = 0; i < 8; ++i)
	{
		for (uint8_t j = 0; j < 128; ++j)
		{
			OLED_SRAM_write(i, j, 0x00);
		}
	}
}


void OLED_SRAM_fill()
{
	for (uint8_t i = 0; i < 8; ++i)
	{
		for (uint8_t j = 0; i < 128; ++j)
		{
			OLED_SRAM_write(i, j, 0xFF);
		}
	}
}


void OLED_SRAM_clear_line(uint8_t line)
{
	for (uint8_t i = 0; i < 128; ++i)
	{
		OLED_SRAM_write(line, i, 0x00);
	}
}


void OLED_SRAM_write(uint8_t page, uint8_t col, uint8_t data)
{
	memory_write_sram_data( (uint16_t)page * 128UL + (uint16_t)col, data);
}


uint8_t OLED_SRAM_read(uint8_t page, uint8_t col)
{
	return memory_read_sram_data( (uint16_t)page * 128 + (uint16_t)col);
}


void OLED_SRAM_pixel(uint8_t x, uint8_t y, uint8_t clear)
{
	uint8_t address    = 16 * y + x; // 128 * y / 8 = 16 * y
	uint8_t set_mask   = (1 << (y % 8));
	uint8_t clear_mask = ~set_mask;
	if (clear)
	{
		memory_write_sram_data(address, memory_read_sram_data(address) & clear_mask );
	}
	else
	{
		memory_write_sram_data(address, memory_read_sram_data(address) | set_mask ) ;
	}
}


void OLED_SRAM_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t clear)
{
	float deltax   = x1 - x0;
	float deltay   = y1 - y0;
	float deltaerr = deltay / deltax;
	
	// absolute value
	if (deltaerr < 0)
	{
		deltaerr = -deltaerr;
	}
	
	// sign
	uint8_t sign = 0;
	if (deltay < 0)
	{
		sign = -1;
	}
	if (deltay > 0)
	{
		sign = 1;
	}
	
	float error = 0.0;
	uint8_t y = y0;
	for (uint8_t x = x0; x < x1; ++x)
	{
		OLED_SRAM_pixel(x, y, clear);
		error += deltaerr;
		if (error >= 0.5) 
		{
			y = y + sign;
			error -= 1;
		}
	}
}


void OLED_SRAM_draw_circle(uint8_t x0, uint8_t y0, uint8_t radius, uint8_t clear, uint8_t fill)
{
	uint8_t x   = radius - 1;
	uint8_t y   = 0;
	uint8_t dx  = 1;
	uint8_t dy  = 1;
	uint8_t err = dx - (radius << 1);
	
	while (x >= y)
	{
		if (fill)
		{
			OLED_SRAM_draw_line(x0 + x, y0 + y, x0 + x, y0 - y, clear);
			
			OLED_SRAM_draw_line(x0 + y, y0 + x, x0 + y, y0 - x, clear);
			
			OLED_SRAM_draw_line(x0 - y, y0 + x, x0 - y, y0 - x, clear);
			
			OLED_SRAM_draw_line(x0 - x, y0 + y, x0 - x, y0 - y, clear);
		}
		else
		{
			OLED_SRAM_pixel(x0 + x, y0 + y, clear);
			OLED_SRAM_pixel(x0 + x, y0 - y, clear);
			
			OLED_SRAM_pixel(x0 + y, y0 + x, clear);
			OLED_SRAM_pixel(x0 + y, y0 - x, clear);
			
			OLED_SRAM_pixel(x0 - y, y0 + x, clear);
			OLED_SRAM_pixel(x0 - y, y0 - x, clear);
			
			OLED_SRAM_pixel(x0 - x, y0 + y, clear);
			OLED_SRAM_pixel(x0 - x, y0 - y, clear);
			
		}
		
		if (err <= 0)
		{
			y++;
			err += dy;
			dy  += 2;
		}
		
		if (err > 0)
		{
			x--;
			dx  += 2;
			err += dx - (radius << 1);
		}
	}
}


void OLED_SRAM_update()
{
	for (uint8_t i = 0; i < 8; ++i)
	{
		memory_write_oled_command(0xB0 | i);
		for (uint8_t j = 0; j < 128; ++j) 
		{
			memory_write_oled_data( OLED_SRAM_read(i, j) );
		}
	}
}