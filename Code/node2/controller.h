#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>

/*
PID controller for position

Implements a discrete controller
for controlling the game position. 

As specified in AVR221.

*/

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