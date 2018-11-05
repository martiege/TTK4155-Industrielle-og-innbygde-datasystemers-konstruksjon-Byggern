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
}

static volatile CONTROLLER_DATA ctrl;


void controller_init(int16_t ctrl_K_p, int16_t ctrl_K_i, int16_t ctrl_K_d);

void controller_set_reference(uint8_t ref);

void reset_integrator();


void controller_set_sampling_time(uint16_t ms);

void controller_start();

void controller_stop();


void controller_update();


#endif