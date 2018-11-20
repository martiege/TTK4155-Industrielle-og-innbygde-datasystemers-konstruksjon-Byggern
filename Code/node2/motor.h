#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

/****************************************
Motor module 

Implements functions to use the motorbox. 

Utilizes the pins as described in by 
the motorbox datasheet and the shield
schematics for Node 2. 

The functions implemented are:

	motor_init()
		
		Initializes the pins used to 
		interface with the motorbox. 
		
	motor_encoder_read()
		
		Reads the current value stored
		in the motor encoder. No need
		to reset the encoder, as the 
		range used is so small. 
		
	motor_reset()
	
		Resets the motor encoder. 
		
	motor_set_speed(int16_t speed, 
					int16_t min)
		
		Sets the motor speed to the value
		speed, with a minimum speed set
		to min. 
		
	motor_set_dir(uint8_t dir)
	
		Sets the motor direction to
		dir. 
	
****************************************/

static uint8_t motor_speed;

void motor_init();

int16_t motor_encoder_read();

void motor_reset();

void motor_set_speed(int16_t speed, int16_t min);

void motor_set_dir(uint8_t dir);


#endif