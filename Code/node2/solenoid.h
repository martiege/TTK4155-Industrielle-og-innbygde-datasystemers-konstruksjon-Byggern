#ifndef SOLENOID_H
#define SOLENOID_H

#include <stdint.h>

/*****************************
Solenoid module

Implements the ability to
use the solenoid to 
shoot. 

The functions implemented are:
	
	solenoid_init()
	
		Initializes the GPIO
		pin used to controll 
		the solenoid. 
		
	solenoid_shoot()
	
		Activate the solenoid,
		delay for 75 
		milliseconds and then
		deactivate it. Creates
		a pulse / shot. 
		
	solenoid_get_shot()
	
		Returns 1 if the 
		solenoid has just
		shot. Used to stop
		several shots in a 
		row. 
		
	solenoid_clear_shot()
	
		Clears the boolean, 
		allows for the module 
		to fire again. 

*****************************/

void solenoid_init();

void solenoid_shoot();

uint8_t solenoid_get_shot();

void solenoid_clear_shot();

#endif