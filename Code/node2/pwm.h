#ifndef PWM_H
#define PWM_H

#include <stdint.h>


/************************************
Pulse Width Modulation (PWM) module

Implements a PWM module to send 
signals to the servo motor to 
set the angle. Only signals with
width <= 2 and width >= 1 are
allowed, which steer the angle
between +/- 90 degrees. 

The functions implemented are:

	pwm_init()
	
		Initializes the timer, 
		and sets the angle to 0. 
		
	pwm_set_angle(int8_t angle)
	
		Sets the width of the PWM
		signal to the value 
		corresponding to the value
		angle. 

************************************/

void pwm_init();

void pwm_set_angle(int8_t angle);

void pwm_set_frequency(float frequency);

void pwm_stop_frequency();

void pwm_start_frequency();

#endif