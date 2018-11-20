#ifndef GOAL_H
#define GOAL_H

#include <stdint.h>

/*******************************
Goal module

Implements ability to look for 
goals. Uses the timer module.

Uses a private variable to keep 
count of the number of goals, 
and a boolean variable to
ensure that the same goal is 
not counted several times. 

The functions implemented are:

	goal_init()
	
		Initializes the goal 
		module and corresponding
		timer.
		
	goal_get_goals()
	
		Get the current number
		of goals. 

*******************************/

void goal_init();

uint8_t goal_get_goals();

#endif