#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

void motor_init();

int16_t motor_encoder_read();

void motor_set_speed(int8_t speed);

void motor_set_dir(uint8_t dir);

#endif