#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

static uint8_t motor_speed;

void motor_init();

int16_t motor_encoder_read();

void motor_reset();

void motor_set_speed(int16_t speed, int16_t min);

void motor_set_dir(uint8_t dir);


#endif