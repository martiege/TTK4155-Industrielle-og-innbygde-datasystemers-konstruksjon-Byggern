#ifndef PWM_H
#define PWM_H

#include <stdint.h>


/*16 bit timer*/

void pwm_init();

void set_angle(int16_t angle);

#endif