#ifndef TIMER_H
#define TIMER_H


void timer_init(uint8_t id, void (* function)() );

void timer_set_period(uint16_t ms, uint8_t id);

void timer_start(uint8_t id);

void timer_stop(uint8_t id);

#endif