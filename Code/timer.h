#ifndef TIMER_H
#define TIMER_H

/*16 bit timer*/

void timer_init();

void set_duty_cycle(float percentage);

void set_angle(int16_t angle);

void timer_start();

void timer_end();

#endif