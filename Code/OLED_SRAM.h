#ifndef OLED_SRAM_H
#define OLED_SRAM_H

#include <stdint.h>


void OLED_SRAM_init();

void OLED_SRAM_reset();

void OLED_SRAM_fill();

void OLED_SRAM_clear_line(uint8_t line);

void OLED_SRAM_write(uint8_t page, uint8_t col, uint8_t data);

uint8_t OLED_SRAM_read(uint8_t page, uint8_t col);

void OLED_SRAM_pixel(uint8_t x, uint8_t y, uint8_t clear);

void OLED_SRAM_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y0, uint8_t clear);

void OLED_SRAM_draw_circle(uint8_t x0, uint8_t y0, uint8_t radius, uint8_t clear, uint8_t fill);

void OLED_SRAM_update();


#endif