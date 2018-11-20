#ifndef GOAL_H
#define GOAL_H

#include <stdint.h>

/*
Goal module

Implements ability to look for 
goals. Uses the timer module.

*/

void goal_init();

uint8_t goal_get_goals();

#endif