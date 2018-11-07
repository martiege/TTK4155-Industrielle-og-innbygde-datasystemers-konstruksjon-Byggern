#ifndef PWM_H
#define PWM_H

#include <stdint.h>


/*16 bit timer*/

void pwm_init();

void pwm_set_angle(int8_t angle);

#endif