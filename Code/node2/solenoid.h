#ifndef SOLENOID_H
#define SOLENOID_H

#include <stdint.h>

void solenoid_init();

void solenoid_shoot();

uint8_t solenoid_get_shot();

void solenoid_clear_shot();

#endif