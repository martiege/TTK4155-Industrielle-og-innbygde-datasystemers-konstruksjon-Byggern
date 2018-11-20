#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>

/******************************************
PID controller for position

Implements a discrete controller
for controlling the game position. 

Implements the struct 
CONTROLLER_DATA, which contains the 
information and state for the 
controller. 

Implemented as specified in AVR221.


The functions implemented are:

	controller_init(int16_t ctrl_K_p, 
					int16_t ctrl_K_i, 
					int16_t ctrl_K_d)
					
		Initializes the controller
		with the PID constants 
		ctrl_K_p, ctrl_K_i and 
		ctrl_K_i. 
		
	controller_set_reference(int16_t ref)
	
		Sets the reference value of the 
		controller. 
		
	controller_set_min_speed(int16_t spd)
	
		Sets the minimum speed allowed the
		motor. 
		
	controller_reset_integrator()
	
		Resets the integrator by clearing
		the sum of errors. 
		
	controller_set_sampling_time(uint16_t ms)
	
		Sets the sampling time of the
		controller. No longer in use, 
		as the controller is updated
		form the node2 module. 
		
	void controller_start()
	
		Starts the controller. No longer 
		in use, as the controller is 
		updated	form the node2 module. 
		
	controller_stop()
		
		Stops the controller. No longer 
		in use, as the controller is 
		updated	form the node2 module. 
		
	controller_get_reference()
	
		Returns the current reference 
		value used by the controller. 
		
	controller_update()
	
		Updates the controller. 
		
******************************************/

typedef struct CONTROLLER_DATA
{
	int16_t r;
	int16_t y;
	int32_t sumE;
	int16_t K_p;
	int16_t K_i;
	int16_t K_d;
	int16_t maxE;
	int32_t maxSumE;
	int16_t speed;
} CONTROLLER_DATA;

static CONTROLLER_DATA ctrl;


void controller_init(int16_t ctrl_K_p, int16_t ctrl_K_i, int16_t ctrl_K_d);

void controller_set_reference(int16_t ref);

void controller_set_min_speed(int16_t spd);

void reset_integrator();


void controller_set_sampling_time(uint16_t ms);

void controller_start();

void controller_stop();

int16_t controller_get_reference();

void controller_update();

#endif