#ifndef TIMER_H
#define TIMER_H

void timer_init();

void timer_set_period(uint16_t ms);

void timer_start();

void timer_stop();

#endif