#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>


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
} CONTROLLER_DATA;

static CONTROLLER_DATA ctrl;
//static int16_t motor_speed;


void controller_init(int16_t ctrl_K_p, int16_t ctrl_K_i, int16_t ctrl_K_d);

void controller_set_reference(int16_t ref);

void reset_integrator();


void controller_set_sampling_time(uint16_t ms);

void controller_start();

void controller_stop();

int16_t controller_get_reference();

void controller_update();

//int16_t controller_get_motor_speed() { return motor_speed; };

#endif